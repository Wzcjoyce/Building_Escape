// Copyright Zuocheng Wang 2021


#include "OpenDoor.h"
#include "Components/AudioComponent.h"
#include "GameFrameWork/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Components/PrimitiveComponent.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	OpenAngle += InitialYaw;

	FindPresurePlate();
	FindAudioComponent();

	// Get player actor use:    GetWorld()->GetFirstPlayerController()->GetPawn();
	// set ActorThatOpen to player actor
	//ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();



	//FRotator OpenDoor = GetOwner()->GetActorRotation();
	//OpenDoor.Yaw += 90.f;
	//FRotator OpenDoor {0.f, 90.f, 0.f};
	//GetOwner()->SetActorRotation(OpenDoor);
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//UE_LOG(LogTemp, Warning, TEXT("%s"), *GetOwner()->GetActorRotation().ToString());
	//UE_LOG(LogTemp, Warning, TEXT("Yaw is: %f"), GetOwner()->GetActorRotation().Yaw);

	// for preventing nullpointer exception we need to check if pointer is null
	/*
	if(PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		OpenDoor(DeltaTime);
		DoorLastOpened = GetWorld()->GetTimeSeconds();
	}
	else
	{
		if((GetWorld()->GetTimeSeconds() - DoorLastOpened) > DoorLastDelay)
		{
			CloseDoor(DeltaTime);
		}
	}
	*/

	if(TotalMassOfActors() > MassToOpenDoor)
	{
		OpenDoor(DeltaTime);
		DoorLastOpened = GetWorld()->GetTimeSeconds();
	}
	else
	{
		if(GetWorld()->GetTimeSeconds() - DoorLastOpened > DoorLastDelay)
		{
			CloseDoor(DeltaTime);
		}
	}

}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	//float CurrentYaw = GetOwner()->GetActorRotation().Yaw;
	//FRotator OpenDoor {0.f, OpenAngle, 0.f};
	//first method
	//OpenDoor.Yaw = FMath::Lerp(CurrentYaw, OpenAngle, DeltaTime * 0.02f);

	//second method constant animation speed 
	//OpenDoor.Yaw = FMath::FInterpConstantTo(CurrentYaw, OpenAngle, DeltaTime, 45);

	//third method smooth animation
	//OpenDoor.Yaw = FMath::FInterpTo(CurrentYaw, OpenAngle, DeltaTime, 2);
	//GetOwner()->SetActorRotation(OpenDoor);

	//Fourth method
	//CurrentYaw = FMath::Lerp(CurrentYaw, OpenAngle, 0.5f);

	//CurrentYaw = FMath::FInterpConstantTo(CurrentYaw, OpenAngle, DeltaTime, 80);;
	//FRotator DoorRotation = GetOwner()->GetActorRotation();
	//DoorRotation.Yaw = CurrentYaw;
	//GetOwner()->SetActorRotation(DoorRotation);


	CurrentYaw = FMath::Lerp(CurrentYaw, OpenAngle, DeltaTime * DoorOpenSpeed);;
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);

	CloseDoorSound = false;
	if(!AudioComponent){return;}
	if(!OpenDoorSound)
	{
		AudioComponent->Play();
		OpenDoorSound = true;
	}
}

void UOpenDoor::CloseDoor(float DeltaTime)
{

	CurrentYaw = FMath::Lerp(CurrentYaw, InitialYaw, DeltaTime * DoorCloseSpeed);;
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);

	OpenDoorSound = false;
	if(!AudioComponent){return;}
	if(!CloseDoorSound)
	{
		AudioComponent->Play();
		CloseDoorSound = true;
	}
}

float UOpenDoor::TotalMassOfActors() const
{
	float TotalMass = 0.f;

	TArray<AActor*> OverlappingActors;
	if(!PressurePlate){return TotalMass;}
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	for(AActor* Actor :  OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("%s is on the pressureplate!"), *Actor->GetName());
	}

	return TotalMass;
}

void UOpenDoor::FindAudioComponent()
{
	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();

	if(!AudioComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("%s Missing Audio Component!"), *GetOwner()->GetName());
	}
}

void UOpenDoor::FindPresurePlate()
{
	if(!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has the open door component on itm but no pressureplate set"), *GetOwner()->GetName());
	}
}

