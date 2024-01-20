// Fill out your copyright notice in the Description page of Project Settings.


#include "PressurePlate.h"

// Sets default values
APressurePlate::APressurePlate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	SetReplicateMovement(true);

	bActivated = false;
	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(RootComp);

	TriggerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TriggerMesh"));
	TriggerMesh->SetupAttachment(RootComp);
	TriggerMesh->SetIsReplicated(true);
	auto TriggerMeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Game/StarterContent/Shapes/Shape_Cylinder"));
	if (TriggerMeshAsset.Succeeded()) {
		TriggerMesh->SetStaticMesh(TriggerMeshAsset.Object);
		TriggerMesh->SetRelativeScale3D(FVector(3.3f, 3.3f, 0.2f));
		TriggerMesh->SetRelativeLocation(FVector(0.f, 0.f, 10.f));
	}

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComp);
	Mesh->SetIsReplicated(true);
	auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Game/Stylized_Egypt/Meshes/building/SM_building_part_08"));
	if (MeshAsset.Succeeded()) {
		Mesh->SetStaticMesh(MeshAsset.Object);
		Mesh->SetRelativeScale3D(FVector(4.f, 4.f, 0.5f));
		Mesh->SetRelativeLocation(FVector(0.f, 0.f, 7.2f));
	}

	Transporter = CreateDefaultSubobject<UTransporter>(TEXT("Transporter"));
	Transporter->MoveTime = 0.25f;
	Transporter->bOwnerIsTriggerActor = true;
}

// Called when the game starts or when spawned
void APressurePlate::BeginPlay()
{
	Super::BeginPlay();

	TriggerMesh->SetVisibility(false);
	TriggerMesh->SetCollisionProfileName(FName("OverlapAll"));

	FVector Point1 = GetActorLocation();
	FVector Point2 = Point1 + FVector(0.f, 0.f, -10.f);
	Transporter->SetPoints(Point1, Point2);
}

// Called every frame
void APressurePlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority()) {
		TArray<AActor*> OverlappingActors;
		AActor* TriggerActor = 0;
		TriggerMesh->GetOverlappingActors(OverlappingActors);

		for (int ActorIndex = 0; ActorIndex < OverlappingActors.Num(); ++ActorIndex) {
			AActor* A = OverlappingActors[ActorIndex];
			if (A->ActorHasTag("TriggerActor")) {
				TriggerActor = A;
				break;
			}
			//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::White, FString::Printf(TEXT("Name: %s"), *A->GetName()));

		}

		if (TriggerActor) {
			if (!bActivated) {
				bActivated = true;
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("Activated")));
				OnActivated.Broadcast();
			}
				
		}
		else {
			if (bActivated) {
				bActivated = false;
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("Deactivated")));
				OnDeactivated.Broadcast();
			}
		}
	}
}

