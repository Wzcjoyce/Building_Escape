// Copyright Zuocheng Wang 2021

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h" //For AActor
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);
	float TotalMassOfActors() const;
	void FindAudioComponent();
	void FindPresurePlate();

	bool OpenDoorSound = false;
	bool CloseDoorSound = true;

private:

	UPROPERTY(EditAnyWhere)
	float OpenAngle = 90.f;
	float InitialYaw;

	//UPROPERTY(EditAnyWhere); // add this line can allow us to edit this varaible in unreal after compile
	float CurrentYaw;

	UPROPERTY(EditAnyWhere)
	ATriggerVolume* PressurePlate;

	UPROPERTY(EditAnyWhere)
	AActor* ActorThatOpens;

	float DoorLastOpened = 0.f;

	UPROPERTY(EditAnyWhere)
	float DoorLastDelay = .5f;

	UPROPERTY(EditAnyWhere)
	float DoorOpenSpeed = .8f;

	UPROPERTY(EditAnyWhere)
	float DoorCloseSpeed = 2.f;

	UPROPERTY(EditAnyWhere)
	float MassToOpenDoor = 60.f;

	UPROPERTY()
	UAudioComponent* AudioComponent = nullptr;
		
};