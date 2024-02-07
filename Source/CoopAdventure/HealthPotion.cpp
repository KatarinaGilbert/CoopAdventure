// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPotion.h"
#include "CoopAdventureCharacter.h"

AHealthPotion::AHealthPotion()
{
	HealthValue = 10;
}

void AHealthPotion::Use(ACoopAdventureCharacter* Character)
{
	if (Character) {
		Character->AddHealth(HealthValue);
	}
}
