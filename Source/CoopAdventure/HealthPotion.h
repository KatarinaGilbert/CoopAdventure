// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "HealthPotion.generated.h"

class ACoopAdventureCharacter;

UCLASS()
class COOPADVENTURE_API AHealthPotion : public AItem
{
	GENERATED_BODY()
	
public:
	AHealthPotion();

protected:
	UPROPERTY(EditAnywhere)
	int HealthValue;


public:
	virtual void Use(ACoopAdventureCharacter* Character) override;

};
