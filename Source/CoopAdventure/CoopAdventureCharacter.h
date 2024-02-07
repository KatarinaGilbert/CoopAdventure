// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Structs.h"
#include "CoopAdventureCharacter.generated.h"

class AItem;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class ACoopAdventureCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Interact Input Action**/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** Zoom Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ZoomAction;

	float MinZoomSpeed;
	float MaxZoomSpeed;

public:
	ACoopAdventureCharacter();
	

protected:
	UFUNCTION(BlueprintNativeEvent, Category = "Stats")
	void UpdateStats(float HealthValue, float FoodValue);

	UPROPERTY(ReplicatedUsing = OnRep_InventoryItems, BlueprintReadWrite, Category = "Stats")
	TArray<FItemData> InventoryItems;

	UFUNCTION()
	void OnRep_InventoryItems();

	UFUNCTION(BlueprintImplementableEvent, Category = "Inventory")
	void AddItemToInventoryWidget(FItemData ItemData);

	UPROPERTY(ReplicatedUsing = OnRep_Stats, BlueprintReadWrite, Category = "Stats")
	float Health;

	UPROPERTY(ReplicatedUsing = OnRep_Stats, BlueprintReadWrite, Category = "Stats")
	float Fullness;
	
	UFUNCTION()
	void OnRep_Stats();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void UseItem(TSubclassOf<AItem> ItemSubclass);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_UseItem(TSubclassOf<AItem> ItemSubclass);

	void Interact(const FInputActionValue& Value);

	void Interact(FVector Start, FVector End);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_Interact(FVector Start, FVector End);

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called for movement input */
	void Zoom(const FInputActionValue& Value);
			

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	void AddInventoryItem(FItemData ItemData);

	void AddHealth(int Value);
	void IncreaseFullness(int Value);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float ZoomSpeed;
};

