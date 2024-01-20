// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectableKey.h"
#include "Net/UnrealNetwork.h"
#include "CoopAdventureCharacter.h"

// Sets default values
ACollectableKey::ACollectableKey()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	SetReplicateMovement(true);

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(RootComp);

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	Capsule->SetupAttachment(RootComp);
	Capsule->SetIsReplicated(true);
	Capsule->SetCollisionProfileName(FName("OverlapAllDynamic"));
	Capsule->SetCapsuleHalfHeight(150.f);
	Capsule->SetCapsuleRadius(100.f);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComp);
	Mesh->SetIsReplicated(true);
	Mesh->SetCollisionProfileName(FName("OverlapAllDynamic"));

	CollectAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("CollectAudio"));
	CollectAudio->SetupAttachment(RootComp);
	CollectAudio->SetAutoActivate(false);

	RotationSpeed = 100.f;

}

// Called when the game starts or when spawned
void ACollectableKey::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACollectableKey::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Rotates the static mesh
	Mesh->AddRelativeRotation(FRotator(0.f, RotationSpeed*DeltaTime, 0.f));

	if (HasAuthority()) {
		TArray<AActor*> OverlappingActors;
		//AActor* TriggerActor = 0;
		Capsule->GetOverlappingActors(OverlappingActors, ACoopAdventureCharacter::StaticClass());

		if (OverlappingActors.Num() > 0) {
			//A player character is overlapping the capsule
			if (!bIsCollected) {
				bIsCollected = true;
				OnRep_bIsCollected();
			}
		}
	}

}

void ACollectableKey::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACollectableKey, bIsCollected);
	//
}

void ACollectableKey::OnRep_bIsCollected()
{
	if (HasAuthority()) {
		UE_LOG(LogTemp, Display, TEXT("OnRep_bIsCollected called from the server"));
		if (bIsCollected) {
			OnCollected.Broadcast();
		}
	}
	else {
		UE_LOG(LogTemp, Display, TEXT("OnRep_bIsCollected called from the client"));
	}

	Mesh->SetVisibility(!bIsCollected);

	CollectAudio->Play();

	if (bIsCollected) {
		if (KeyHolderRef) {
			KeyHolderRef->ActivateKeyMesh();
		}
	}
}
