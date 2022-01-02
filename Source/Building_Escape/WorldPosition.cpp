// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldPosition.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UWorldPosition::UWorldPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWorldPosition::BeginPlay()
{
	Super::BeginPlay();

	//UE_LOG(LogTemp, Display, TEXT("Just a log, nothing to see!"));
	//UE_LOG(LogTemp, Warning, TEXT("This is a warning!"));
	//UE_LOG(LogTemp, Error, TEXT("Error!"));

	//FString Log = TEXT("Hello");
	//FString * PtrLog = & Log;

	//(*PtrLog).Len();
	//PtrLog->Len();

	//UE_LOG(LogTemp, Warning, TEXT("%s"). **PtrLog);

	// Pointer to Actor object is to include #include "GameFramework/Actor.h"
	// Pointer to Actor object is to call GetOwner()
	// Pointer to Actor object is AActor*

	FString ObjectName = GetOwner()->GetName();
	//UE_LOG(LogTemp, Display, TEXT("The object name is: %s"),*ObjectName);

	//Method 1 for getting Actor location
	FString ObjectPosition = GetOwner()->GetActorLocation().ToString();

	//Method 2 for getting Actor location
	//FString ObjectPosition = GetOwner()->GetActorTransform().GetLocation().ToString();

	//UE_LOG(LogTemp, Display, TEXT("%s object's location is: %s"), *ObjectName, *ObjectPosition);
	
}


// Called every frame
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

