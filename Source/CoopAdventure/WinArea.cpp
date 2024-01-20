

#include "WinArea.h"
#include "CoopAdventureCharacter.h"
#include "Kismet/GameplayStatics.h"

AWinArea::AWinArea()
{
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	SetReplicateMovement(true);

	WinAreaBox = CreateDefaultSubobject<UBoxComponent>(TEXT("WinAreaBox"));
	SetRootComponent(WinAreaBox);

	WinCondition = false;
}

void AWinArea::BeginPlay()
{
	Super::BeginPlay();

	//if (HasAuthority()) {
	//	GetWorld()->GetTimerManager().SetTimer(TestTimer, this, &AWinArea::MulticastTester, 2.0f, false);
	//}

	if (HasAuthority()) {
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Server"));
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, TEXT("Client"));
	}
	
}

void AWinArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority()) {
		if (!WinCondition) {
			TArray<AActor*> OverlappingActors;
			//AActor* TriggerActor = 0;
			WinAreaBox->GetOverlappingActors(OverlappingActors, ACoopAdventureCharacter::StaticClass());

			//int PlayerCount = GetWorld()->GetNumPlayerControllers();
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("PlayerCount: %d"), PlayerCount));
			//this is a test

			//!!!Can change this to == PlayerCount later, but I would prefer to update a "PlayerCount" from the MultiplayerSessionSubsystem later and update a global variable for WinArea whenever that changes
			WinCondition = (OverlappingActors.Num() == 2);

			if (WinCondition) {
				UE_LOG(LogTemp, Display, TEXT("Win!"));

				MulticastRPCWin();
			}
		}
	}
}

void AWinArea::MulticastRPCWin_Implementation()
{
	OnWinCondition.Broadcast();
}

/*
void AWinArea::MulticastTester_Implementation()
{
	if (HasAuthority()) {
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Server: MulticastRPCExplode_Implementation"));
		GetWorld()->GetTimerManager().SetTimer(TestTimer, this, &AWinArea::MulticastTester, 2.0f, false);
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Client: MulticastRPCExplode_Implementation"));
	}
}
*/