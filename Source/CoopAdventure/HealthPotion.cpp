// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPotion.h"
#include "CoopAdventureCharacter.h"

AHealthPotion::AHealthPotion()
{
	HealthValue = 10;
}

void AHealthPotion::Use(ACoopAdventureCharacter* Character, bool IsInShop)
{
	Super::Use(Character, IsInShop);

	if (Character && !IsInShop) {
		Character->AddHealth(HealthValue);
	}
}
