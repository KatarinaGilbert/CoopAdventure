#include "CollectableKeyHolder.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

// Sets default values
ACollectableKeyHolder::ACollectableKeyHolder()
{
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	SetReplicateMovement(true);

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(RootComp);

	KeyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KeyMesh"));
	KeyMesh->SetupAttachment(RootComp);
	KeyMesh->SetIsReplicated(true);
	KeyMesh->SetCollisionProfileName(FName("OverlapAllDynamic"));

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComp);
	Mesh->SetIsReplicated(true);
	Mesh->SetCollisionProfileName(FName("BlockAllDynamic"));

	KeyRotationSpeed = 100.f;
}

void ACollectableKeyHolder::BeginPlay()
{
	Super::BeginPlay();

	KeyMesh->SetVisibility(false);
	
}

void ACollectableKeyHolder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	KeyMesh->AddRelativeRotation(FRotator(0.f, KeyRotationSpeed * DeltaTime, 0.f));

}

void ACollectableKeyHolder::ActivateKeyMesh()
{
	KeyMesh->SetVisibility(true);
}

