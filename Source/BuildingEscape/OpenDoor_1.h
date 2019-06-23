// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OpenDoor_1.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor_1 : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor_1();

/*  NOT NEEDED ANYMORE
	void OpenDoor();
	void CloseDoor();
*/
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable)
		FDoorEvent OnOpen;

	UPROPERTY(BlueprintAssignable)
		FDoorEvent OnClose;

private:
/* NOT NEEDED ANYMORE
	UPROPERTY(EditAnywhere)
	float openAngle = -90.0f;

	UPROPERTY(EditAnywhere)
	float DoorColseDelay = 1.0f;

	float LastDoorOpenTime;
*/

	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate = nullptr;
	

	UPROPERTY(EditAnywhere)
		float TriggerMass = 50.0f;

		AActor* owner = nullptr; // Owning door

		//returns total mass in KG
		float GetTotalMassOfActorOnPlate();
};
