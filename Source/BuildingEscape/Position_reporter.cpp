// Fill out your copyright notice in the Description page of Project Settings.

#include "Position_reporter.h"


// Sets default values for this component's properties
UPosition_reporter::UPosition_reporter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;	
}


// Called when the game starts
void UPosition_reporter::BeginPlay()
{
	Super::BeginPlay();
	FString name= GetOwner()->GetName();
	FString position = GetOwner()->GetTransform().GetLocation().ToString();

	UE_LOG(LogTemp, Warning, TEXT("%s location is %s"),*name,*position);	
}


// Called every frame
void UPosition_reporter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

