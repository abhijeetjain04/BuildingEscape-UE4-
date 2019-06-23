// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor_1.h"

#define OUT
// Sets default values for this component's properties
UOpenDoor_1::UOpenDoor_1()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UOpenDoor_1::BeginPlay()
{
	Super::BeginPlay();
	if (!owner)
		UE_LOG(LogTemp, Error, TEXT("missing pressure plate"));

	owner = GetOwner();

	if(!PressurePlate)
		UE_LOG(LogTemp, Error, TEXT("missing pressure plate"));
	//ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}

float UOpenDoor_1::GetTotalMassOfActorOnPlate()
{
	float TotalMass = 0.0f;

	//Find the oevrlapping actors
	TArray<AActor*> OverLappingActors;

	if (!PressurePlate)return TotalMass; //pointer protection
	PressurePlate->GetOverlappingActors(OUT OverLappingActors);

	for (const auto &i : OverLappingActors)
	{
		TotalMass += i->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("name: %s"),*i->GetName());
	}
	return TotalMass;
}

// Called every frame
void UOpenDoor_1::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// poll the trigger volume
	if (GetTotalMassOfActorOnPlate() > TriggerMass)
	{
		OnOpen.Broadcast();
		/*LastDoorOpenTime = GetWorld()->GetTimeSeconds();*/
	}
	else
	{
		OnClose.Broadcast();
	}
#pragma region OLDMETHOD_OPENACTOR
	// if the actor that openis in volume then

	/*
	if (PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorColseDelay)
	{
		CloseDoor();
	}
	*/
#pragma endregion
}
