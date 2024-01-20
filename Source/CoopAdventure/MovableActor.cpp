#include "MovableActor.h"

AMovableActor::AMovableActor()
{
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	SetReplicateMovement(true);

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(RootComp);

	Point1 = CreateDefaultSubobject<UArrowComponent>(TEXT("Point1"));
	Point1->SetupAttachment(RootComp);
	if (Point1) {
		Point1->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	}

	Point2 = CreateDefaultSubobject<UArrowComponent>(TEXT("Point2"));
	Point2->SetupAttachment(RootComp);
	if (Point2) {
		Point2->SetRelativeLocation(FVector(0.f, 0.f, 300.f));
	}

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComp);
	Mesh->SetIsReplicated(true);

	Transporter = CreateDefaultSubobject<UTransporter>(TEXT("Transporter"));
}

void AMovableActor::BeginPlay()
{
	Super::BeginPlay();

	FVector StartPoint = GetActorLocation() + Point1->GetRelativeLocation();
	FVector EndPoint = GetActorLocation() + Point2->GetRelativeLocation();

	Transporter->SetPoints(StartPoint, EndPoint);


	
}

// Called every frame
void AMovableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

