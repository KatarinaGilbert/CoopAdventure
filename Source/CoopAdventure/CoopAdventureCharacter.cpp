// Copyright Epic Games, Inc. All Rights Reserved.

#include "CoopAdventureCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Item.h"
#include "Chimes.h"
#include "ShopKeeper.h"
#include "Net/UnrealNetwork.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ACoopAdventureCharacter

ACoopAdventureCharacter::ACoopAdventureCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	ZoomSpeed = 10.f;
	MinZoomSpeed = 5.f;
	MaxZoomSpeed = 100.f;
	Chimes = 0;
}

void ACoopAdventureCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	if (ZoomSpeed < MinZoomSpeed) {
		ZoomSpeed = MinZoomSpeed;
	}
	else if (ZoomSpeed > MaxZoomSpeed) {
		ZoomSpeed = MaxZoomSpeed;
	}



	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void ACoopAdventureCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION(ACoopAdventureCharacter, InventoryItems, COND_OwnerOnly);
	DOREPLIFETIME(ACoopAdventureCharacter, Health);
	DOREPLIFETIME(ACoopAdventureCharacter, Fullness);
	DOREPLIFETIME(ACoopAdventureCharacter, Chimes)
}

void ACoopAdventureCharacter::OnRep_Stats()
{
	if (IsLocallyControlled()) {
		UpdateStats(Health, Fullness);
	}
}

void ACoopAdventureCharacter::OnRep_Currency()
{

	if (IsLocallyControlled()) {
		UpdateChimeAmount(Chimes);
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::White, FString::Printf(TEXT("OnRep_Currency: Current Player Chimes: %d"), Chimes));
	}
}

int32 ACoopAdventureCharacter::GetCurrentChimes() {
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::White, FString::Printf(TEXT("Current Player Chimes: %d"), Chimes));
	
	return Chimes;
}

void ACoopAdventureCharacter::RemoveChimes(int32 Cost)
{
	Chimes -= Cost;
	if (IsLocallyControlled()) {
		UpdateChimeAmount(Chimes);
	}
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::White, FString::Printf(TEXT("Current Chimes Amount: %d"), Chimes));
	//Chimes -= AmountToRemove;

	/*
	for (FItemData& Item : InventoryItems) {
		if (Item.ItemClass->StaticClass() == TSubclassOf<AChimes>()->StaticClass()) {
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::White, FString::Printf(TEXT("Removing Chimes: %d"), AmountToRemove));
			Item.StackCount -= AmountToRemove;
		}
	}
	*/
}

void ACoopAdventureCharacter::AddInventoryItem(FItemData ItemData) {
	if (HasAuthority()) {
		bool bIsNewItem = true;
		CheckIfIsCurrency(ItemData);
		if (IsCurrency) {
			bIsNewItem = false;
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::White, FString::Printf(TEXT("Updating Currency: %d"), Chimes));
			AddChimes(ItemData.StackCount);
		}
		else {
			for (FItemData& Item : InventoryItems) {
				if (Item.ItemClass == ItemData.ItemClass) {
					if (ItemData.StackCount > 1) {
						Item.StackCount += ItemData.StackCount;
					}
					else {
						++Item.StackCount;
					}
					bIsNewItem = false;
					break;
				}
			}

			if (bIsNewItem) {
				InventoryItems.Add(ItemData);
			}
			if (IsLocallyControlled()) {
				OnRep_InventoryItems();
			}
		}

		


		/*previous
		for (FItemData& Item : InventoryItems) {
			if (Item.ItemClass == ItemData.ItemClass) {
				if (ItemData.StackCount > 1) {
					Item.StackCount += ItemData.StackCount;
				}
				else {
					++Item.StackCount;
				}
				bIsNewItem = false;
				break;
			}
		}
		if (bIsNewItem && !IsCurrency) {
			InventoryItems.Add(ItemData);	
		}
		if (IsLocallyControlled()) {
			OnRep_InventoryItems();
		}
		*/
	}
}

void ACoopAdventureCharacter::OnRep_InventoryItems()
{
	if (InventoryItems.Num()) {
		AddItemAndUpdateInventoryWidget(InventoryItems[InventoryItems.Num() - 1], InventoryItems);
	}
	else {
		AddItemAndUpdateInventoryWidget(FItemData(), InventoryItems);
	}
}

void ACoopAdventureCharacter::AddHealth(int Value)
{
	Health += Value;
	if (IsLocallyControlled()) {
		UpdateStats(Health, Fullness);
	}
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::White, FString::Printf(TEXT("Added Health: %f"), Health));
}

void ACoopAdventureCharacter::IncreaseFullness(int Value)
{
	Fullness += Value;
	if (IsLocallyControlled()) {
		UpdateStats(Health, Fullness);
	}
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::White, FString::Printf(TEXT("Decreased Hunger: %f"), Fullness));
}

void ACoopAdventureCharacter::AddChimes(int Value)
{
	Chimes += Value;
	if (IsLocallyControlled()) {
		UpdateChimeAmount(Chimes);
	}
	//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::White, FString::Printf(TEXT("Current Chimes Amount: %d"), Chimes));
}

//////////////////////////////////////////////////////////////////////////
// Input

void ACoopAdventureCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Interact
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ACoopAdventureCharacter::Interact);


		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACoopAdventureCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACoopAdventureCharacter::Look);

		// Zooming
		EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &ACoopAdventureCharacter::Zoom);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ACoopAdventureCharacter::Interact(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::White, FString::Printf(TEXT("Interacting")));

	FVector Start = FollowCamera->GetComponentLocation();
	FVector End = Start + FollowCamera->GetForwardVector() * 700.f;	//!!! Might need to increase to 700.f later on because of the scrolling camera feature. Increased from 500.f

	if (HasAuthority()) {
		Interact(Start, End);
	}
	else {
		Interact(Start, End);
		Server_Interact(Start, End);
	}
}

void ACoopAdventureCharacter::Interact(FVector Start, FVector End) {
	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Visibility, Params)) {
		AShopKeeper* ShopKeeper = Cast<AShopKeeper>(HitResult.GetActor());
		if (ShopKeeper) {
			if (IsLocallyControlled()) {
				ShopKeeper->Interact(this);
			}
			return;
		}
		
		if (IInteractableInterface* Interface = Cast<IInteractableInterface>(HitResult.GetActor())) {

			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::White, FString::Printf(TEXT("Hit Actor: %s"), *HitResult.GetActor()->GetName()));
			Interface->Interact(this);
		}
	}
}

bool ACoopAdventureCharacter::Server_Interact_Validate(FVector Start, FVector End)
{
	return true;
}

void ACoopAdventureCharacter::Server_Interact_Implementation(FVector Start, FVector End)
{
	Interact(Start, End);
}

void ACoopAdventureCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ACoopAdventureCharacter::UpdateStats_Implementation(float HealthValue, float FoodValue)
{

}

void ACoopAdventureCharacter::UpdateChimeAmount_Implementation(int ChimeValue)
{

}



void ACoopAdventureCharacter::UseItem(TSubclassOf<AItem> ItemSubclass, AShopKeeper* ShopKeeper, bool IsShopItem)
{
	if (ItemSubclass) {
		if (HasAuthority()) {
			if (!ShopKeeper) {
				UseRemoveItem(ItemSubclass);
			}
			else {
				ShopKeeper->BuyItem(this, ItemSubclass);
				if (IsLocallyControlled()) {
					OnRep_InventoryItems();
				}
			}
		}
		else {
			if (ShopKeeper) {
				if (!ShopKeeper->BuyItem(this, ItemSubclass)) {
					return;
				}
			}
			if (AItem* Item = ItemSubclass.GetDefaultObject()) {
				Item->Use(this, IsShopItem);
			}
			Server_UseItem(ItemSubclass, ShopKeeper, IsShopItem);
		}


	}
}

void ACoopAdventureCharacter::UseRemoveItem(TSubclassOf<AItem> ItemSubclass) {
	uint8 Index = 0;
	for (FItemData& Item : InventoryItems) {
		if (Item.ItemClass == ItemSubclass) {
			if (AItem* ItemCDO = ItemSubclass.GetDefaultObject()) {
				ItemCDO->Use(this, false);
			}
			--Item.StackCount;
			if (Item.StackCount <= 0) {
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("Before Shrink InventoryItems size: %d"), InventoryItems.Num()));
				InventoryItems.RemoveAt(Index);
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("After Shrink InventoryItems size: %d"), InventoryItems.Num()));
			}
			break;
		}
		++Index;
	}

	if (IsLocallyControlled()) {
		OnRep_InventoryItems();
	}
}

bool ACoopAdventureCharacter::Server_UseItem_Validate(TSubclassOf<AItem> ItemSubclass, AShopKeeper* ShopKeeper, bool IsShopItem) {
	return true;
}

void ACoopAdventureCharacter::Server_UseItem_Implementation(TSubclassOf<AItem> ItemSubclass, AShopKeeper* ShopKeeper, bool IsShopItem) {
	if (IsShopItem) {
		UseItem(ItemSubclass, ShopKeeper, IsShopItem);
	}
	else {
		for (FItemData& Item : InventoryItems) {
			if (Item.ItemClass == ItemSubclass) {
				if (Item.StackCount) {
					UseItem(ItemSubclass, ShopKeeper, IsShopItem);
				}
				return;
			}
		}
	}
}


void ACoopAdventureCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ACoopAdventureCharacter::Zoom(const FInputActionValue& Value)
{
	float MinZoom = 300.f;
	float MaxZoom = 700.f;

	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::White, FString::Printf(TEXT("This is a test")));

	// input is an Axis1D
	float ZoomValue = Value.Get<float>();
	if (ZoomValue) {
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::White, FString::Printf(TEXT("ZoomValue: %f"), ZoomValue));
		//float CurrentArmLength = CameraBoom->TargetArmLength;
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::White, FString::Printf(TEXT("ZoomValue*10: %f"), ZoomValue * ZoomSpeed));
		float NewZoomVal = CameraBoom->TargetArmLength + (ZoomValue * ZoomSpeed);
		if (NewZoomVal > MinZoom && NewZoomVal < MaxZoom) {
			CameraBoom->TargetArmLength += ZoomValue * ZoomSpeed;
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::White, FString::Printf(TEXT("New CameraBoom->TargetArmLength: %f"), CameraBoom->TargetArmLength));
		}
	}
}


