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
class AShopKeeper;
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

	UFUNCTION(BlueprintNativeEvent, Category = "Inventory")
	void UpdateChimeAmount(int Value);

	UPROPERTY(ReplicatedUsing = OnRep_InventoryItems, BlueprintReadWrite, Category = "Stats")
	TArray<FItemData> InventoryItems;


	UFUNCTION()
	void OnRep_InventoryItems();

	UFUNCTION(BlueprintImplementableEvent, Category = "Inventory")
	void AddItemAndUpdateInventoryWidget(FItemData ItemData, const TArray<FItemData>& CurrentInventory = TArray<FItemData>());

	UFUNCTION(BlueprintImplementableEvent, Category = "Inventory")
	void CheckIfIsCurrency(FItemData ItemData);

	UPROPERTY(ReplicatedUsing = OnRep_Stats, BlueprintReadWrite, Category = "Stats")
	float Health;

	UPROPERTY(ReplicatedUsing = OnRep_Stats, BlueprintReadWrite, Category = "Stats")
	float Fullness;

	UPROPERTY(ReplicatedUsing = OnRep_Currency, BlueprintReadWrite, Category = "Inventory")
	int32 Chimes;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	bool IsCurrency;
	
	UFUNCTION()
	void OnRep_Stats();

	UFUNCTION()
	void OnRep_Currency();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void UseItem(TSubclassOf<AItem> ItemSubclass, AShopKeeper* ShopKeeper, bool IsShopItem = false);

	void UseRemoveItem(TSubclassOf<AItem> ItemSubclass);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_UseItem(TSubclassOf<AItem> ItemSubclass, AShopKeeper* ShopKeeper, bool IsShopItem = false);

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

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddChimes(int Value);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	int32 GetCurrentChimes();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RemoveChimes(int32 Cost);

	UFUNCTION(BlueprintImplementableEvent, Category = "Shop")
	void OpenShop(AShopKeeper* OwningShop, const TArray<FItemData>& Items);

	UFUNCTION(BlueprintImplementableEvent, Category = "Shop")
	void UpdateShop(AShopKeeper* OwningShop, const TArray<FItemData>& Items);

	void AddInventoryItem(FItemData ItemData);

	void AddHealth(int Value);
	void IncreaseFullness(int Value);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float ZoomSpeed;
};

