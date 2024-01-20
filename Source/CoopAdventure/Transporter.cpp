

#include "Transporter.h"
#include "PressurePlate.h"
#include "CollectableKey.h"

UTransporter::UTransporter()
{
	PrimaryComponentTick.bCanEverTick = true;

	SetIsReplicatedByDefault(true);
	MoveTime = 3.f;
	ActivatedTriggerCount = 0;

	bArePointsSet = false;

	StartPoint = FVector(0.f, 0.f, 0.f);
	EndPoint = FVector(0.f, 0.f, 0.f);
}


// Called when the game starts
void UTransporter::BeginPlay()
{
	Super::BeginPlay();

	if (bOwnerIsTriggerActor) {
		TriggerActors.Add(GetOwner());
	}

	for (AActor* TA : TriggerActors) {
		APressurePlate* PressurePlateActor = Cast<APressurePlate>(TA);
		if (PressurePlateActor) {
			PressurePlateActor->OnActivated.AddDynamic(this, &UTransporter::OnTriggerActorActivated);
			PressurePlateActor->OnDeactivated.AddDynamic(this, &UTransporter::OnTriggerActorDeactivated);
			continue;
		}
		ACollectableKey* KeyActor = Cast<ACollectableKey>(TA);
		if (KeyActor) {
			KeyActor->OnCollected.AddDynamic(this, &UTransporter::OnTriggerActorActivated);
		}
	}

	
}

// Called every frame
void UTransporter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TriggerActors.Num() > 0) {
		bAllTriggerActorsTriggered = (ActivatedTriggerCount >= TriggerActors.Num());
		if (bAllTriggerActorsTriggered) {
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("All trigger actors triggered!")));
		}
	}

	AActor* MyOwner = GetOwner();
	if (MyOwner && MyOwner->HasAuthority() && bArePointsSet) {
		FVector CurrentLocation = MyOwner->GetActorLocation();
		float Speed = FVector::Distance(StartPoint, EndPoint) / MoveTime;
		FVector TargetLocation = bAllTriggerActorsTriggered? EndPoint : StartPoint;
		if (!CurrentLocation.Equals(TargetLocation)) {
			FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
			MyOwner->SetActorLocation(NewLocation);
		}
	}

}

void UTransporter::SetPoints(FVector Point1, FVector Point2)
{
	if (Point1.Equals(Point2)) {
		return;
	}

	StartPoint = Point1;
	EndPoint = Point2;
	bArePointsSet = true;
}

void UTransporter::OnTriggerActorActivated()
{
	ActivatedTriggerCount++;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("Transporter Activated: %d"), ActivatedTriggerCount));

}

void UTransporter::OnTriggerActorDeactivated()
{
	ActivatedTriggerCount--;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("Transporter Activated: %d"), ActivatedTriggerCount));
}

