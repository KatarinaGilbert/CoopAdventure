// Fill out your copyright notice in the Description page of Project Settings.


#include "Food.h"
#include "CoopAdventureCharacter.h"

AFood::AFood()
{
	FoodValue = 30;

}

void AFood::Use(ACoopAdventureCharacter* Character, bool IsInShop)
{
	Super::Use(Character, IsInShop);

	if (Character && !IsInShop) {
		Character->IncreaseFullness(FoodValue);
	}
}
