// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Engine.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	///how far ahead of the player can we reach in cm
	float Reach = 100.0f;
	
	UPhysicsHandleComponent* physicsHandle = nullptr;

	UInputComponent* inputComponent = nullptr;

private:
	//Ray-cast and grab whats in reach
	void Grab();

	void Release();

	//Find (assumed) attached phyics component
	void FindPhysicsHandleComponent();

	//setup (assumed) attached input component
	void SetupInputComponenet();

	//return hit for first physics body in reach 
	FHitResult GetFirstBodyInReach();

	//Return current end of reach line
	FVector GetReachLineStart();

	//Return current end of reach line
	FVector GetReachLineEnd();
};
