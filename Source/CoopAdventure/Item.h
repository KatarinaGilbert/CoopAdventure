// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.h"
#include "Structs.h"
#include "Item.generated.h"

UCLASS()
class COOPADVENTURE_API AItem : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "BaseComponents")
	UStaticMeshComponent* ItemMesh;

	UPROPERTY(EditDefaultsOnly, Category = "BaseComponents")
	FItemData ItemData;


public:	
	virtual void Interact(class ACoopAdventureCharacter* Character) override;

	virtual void Use(ACoopAdventureCharacter* Character) override;

	FItemData GetItemData() const { return ItemData; }


};