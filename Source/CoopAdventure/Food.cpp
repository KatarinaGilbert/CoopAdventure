// Fill out your copyright notice in the Description page of Project Settings.


#include "Food.h"
#include "CoopAdventureCharacter.h"

AFood::AFood()
{
	FoodValue = 30;

}

void AFood::Use(ACoopAdventureCharacter* Character)
{
	if (Character) {
		Character->IncreaseFullness(FoodValue);
	}
}
