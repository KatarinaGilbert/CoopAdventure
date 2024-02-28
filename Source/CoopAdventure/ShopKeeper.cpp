// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopKeeper.h"
#include "Components/SkeletalMeshComponent.h"
#include "Net/UnrealNetwork.h"
#include "CoopAdventureCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Item.h"


// Sets default values
AShopKeeper::AShopKeeper()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ShopKeeperMesh = CreateDefaultSubobject <USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	RootComponent = ShopKeeperMesh;

	bReplicates = true;


}

void AShopKeeper::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AShopKeeper, Items);
	DOREPLIFETIME(AShopKeeper, Chimes);
}

// Called when the game starts or when spawned
void AShopKeeper::BeginPlay()
{
	Super::BeginPlay();
	
}

void AShopKeeper::OnRep_Items()
{
	if (ACoopAdventureCharacter* Character = Cast<ACoopAdventureCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))) {
		//if (Character->IsLocallyControlled()) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Character Chimes: %d"), Character->GetCurrentChimes()));
			Character->UpdateShop(this, Items);
			//Character->OpenShop(this, Items);
		//}
	}
}

void AShopKeeper::Interact(ACoopAdventureCharacter* Character)
{
	//for (FItemData& Item : Items) {
	//	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::White, FString::Printf(TEXT("Cost: %d"), Item.ItemCost));
	//}
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::White, FString::Printf(TEXT("Talking with ShopKeeper")));

	if (Character) {
		Character->OpenShop(this, Items);
	}
}

void AShopKeeper::TransferItem(TSubclassOf<AItem> ItemSubclass)
{
	uint8 Index = 0;
	for (FItemData& Item : Items) {
		if (Item.ItemClass == ItemSubclass) {
			--Item.StackCount;
			Chimes += Item.ItemCost;
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("New Chimes Amount: %d"), Chimes));

			if (Item.StackCount <= 0) {
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("Before Shrink InventoryItems size: %d"), Items.Num()));
				Items.RemoveAt(Index);
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("After Shrink InventoryItems size: %d"), Items.Num()));
			}
			break;
		}
		++Index;
	}

	for (FItemData& Item : Items) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("StackCount: %d"), Item.StackCount));
	}

	OnRep_Items();
}

bool AShopKeeper::CanBuyItem(int32 CurrentChimes, TSubclassOf<AItem> ItemSubclass)
{
	for (FItemData& Item : Items) {
		if (Item.ItemClass == ItemSubclass) {
			return CurrentChimes >= Item.ItemCost;
		}
	}
	return false;
}

bool AShopKeeper::BuyItem(ACoopAdventureCharacter* Character, TSubclassOf<AItem> ItemSubclass)
{
	if (Character && ItemSubclass) {
		for (FItemData& Item : Items) {
			if (Item.ItemClass == ItemSubclass) {
				if (CanBuyItem(Character->GetCurrentChimes(), ItemSubclass)) {
					if (AItem* ItemCDO = ItemSubclass.GetDefaultObject()) {

						ItemCDO->Use(Character, true);
						Character->RemoveChimes(Item.ItemCost);
						TransferItem(ItemSubclass);
						return true;
					}
				}
			}
		}
	}
	return false;
}

