// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Food.generated.h"

class ACoopAdventureCharacter;

UCLASS()
class COOPADVENTURE_API AFood : public AItem
{
	GENERATED_BODY()
public:
	AFood();

protected:
	UPROPERTY(EditAnywhere)
	int FoodValue;


public:
	virtual void Use(ACoopAdventureCharacter* Character) override;
};
