// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "Components/StaticMeshComponent.h"
#include "CoopAdventureCharacter.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = ItemMesh;

	bReplicates = true;
	SetReplicateMovement(true);

	ItemData.ItemClass = GetClass();
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
}

void AItem::Interact(class ACoopAdventureCharacter* Character)
{
	if (HasAuthority() && Character) {
		Character->AddInventoryItem(ItemData);
		Destroy();
	}
}

void AItem::Use(ACoopAdventureCharacter* Character)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::White, FString::Printf(TEXT("Using Item: %s"), *GetName()));
}
