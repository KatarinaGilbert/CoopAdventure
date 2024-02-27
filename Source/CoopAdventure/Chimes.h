// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Chimes.generated.h"

class ACoopAdventureCharacter;

/**
 * 
 */
UCLASS()
class COOPADVENTURE_API AChimes : public AItem
{
	GENERATED_BODY()
	
public:
	AChimes();

	virtual void Use(ACoopAdventureCharacter* Character, bool IsInShop = false) override;

};
