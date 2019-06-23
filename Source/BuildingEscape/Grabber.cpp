// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandleComponent();
	SetupInputComponenet();
}

///look for attached physics handle
void UGrabber::FindPhysicsHandleComponent()
{
	

	physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (physicsHandle==nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing component"), *GetOwner()->GetName());
	}

}

void UGrabber::SetupInputComponenet()
{

	inputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	///bind the input action
	if (inputComponent)
	{
		inputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		inputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!physicsHandle) return;
	//if the physics handle is attached
	if (physicsHandle->GrabbedComponent)
	{
		// move the object that we are holding
		physicsHandle->SetTargetLocation(GetReachLineEnd());
	}

}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("grab component"));

	///LINE TRACE and see if reach any actors with physics body collision channel set
	auto HitResult = GetFirstBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent(); // this gives component
	auto ActorHit = HitResult.GetActor();

	///if we hit something then attach a physics handle
	if (ActorHit)
	{
		if (!physicsHandle) return;
		//attach physics handle
		physicsHandle->GrabComponent(
			ComponentToGrab,
			NAME_None,
			ComponentToGrab->GetOwner()->GetActorLocation(),
			true);// allow rotation
	}
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("release component"));

	if (!physicsHandle) return;
	//release object
	physicsHandle->ReleaseComponent();
}

FHitResult UGrabber::GetFirstBodyInReach()
{
	///Debug viewport values
	/*UE_LOG(LogTemp, Warning, TEXT("Position: %s,Rotation: %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString());*/

	/// Draw ared trace in the world to visualise
	/*DrawDebugLine(GetWorld(), PlayerViewPointLocation, LineTraceEnd, FColor(255, 0, 0), false, 0.0f, 0.0f, 10.0f);*/ 

	///setup query parameters
	FCollisionQueryParams TraceParameter(FName(TEXT("")), false, GetOwner());

	///Line-trace (AKA ray-cast) out to reach distance
	FHitResult LineTraceHit;
	GetWorld()->LineTraceSingleByObjectType(OUT LineTraceHit, GetReachLineStart(), GetReachLineEnd()
		, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParameter);

	AActor* actorObject = LineTraceHit.GetActor();

	if (actorObject)
		UE_LOG(LogTemp, Warning, TEXT("Line trace hit: %s"), *(actorObject->GetName()));

	return LineTraceHit;
}

FVector UGrabber::GetReachLineStart()
{
	/// Get player view pint this tick
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	return PlayerViewPointLocation;
}

FVector UGrabber::GetReachLineEnd()
{
	/// Get player view pint this tick
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	return PlayerViewPointLocation + PlayerViewPointRotation.Vector()*Reach;
}

