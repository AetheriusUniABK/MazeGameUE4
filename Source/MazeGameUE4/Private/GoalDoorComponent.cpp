// Fill out your copyright notice in the Description page of Project Settings.


#include "GoalDoorComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/TriggerBox.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UGoalDoorComponent::UGoalDoorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

bool UGoalDoorComponent::IsOverlapping()
{
	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (PlayerPawn)
	{
		return TriggerBox->IsOverlappingActor(PlayerPawn);
	}
	return false;
}

// Called when the game starts
void UGoalDoorComponent::BeginPlay()
{
	Super::BeginPlay();
	/*StartRotation = GetOwner()->GetActorRotation();
	FinalRotation = GetOwner()->GetActorRotation() + DesiredRotation;

	CurrentRotationTime = 0.0f;
	*/
}


// Called every frame
void UGoalDoorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (IsOverlapping())
	{
		FGenericPlatformMisc::RequestExit(false);
	}
	

	/*
	
	if (CurrentRotationTime >= TimeToRotate)
	{
		CurrentRotationTime = TimeToRotate - DeltaTime;
	}
	if (CurrentRotationTime < 0.0f)
	{
		CurrentRotationTime = 0.0f;
	}

	if (CurrentRotationTime < TimeToRotate)
	{
		// if approaching front of door
		if (TriggerBox && GetWorld()->GetFirstPlayerController())
		{
			APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
			// if player is in front of door
			if (PlayerPawn && TriggerBox->IsOverlappingActor(PlayerPawn))
			{
				CurrentRotationTime += DeltaTime;
				const float TimeRatio = FMath::Clamp(CurrentRotationTime / TimeToRotate, 0.0f, 1.0f);
				const float RotationAlpha = OpenCurve.GetRichCurveConst()->Eval(TimeRatio);
				const FRotator CurrentRotation = FMath::Lerp(StartRotation, FinalRotation, RotationAlpha);
				GetOwner()->SetActorRotation(CurrentRotation);
			}

			// if player is not close to the door
			else
			{
				CurrentRotationTime -= DeltaTime;
				const float TimeRatio = FMath::Clamp(CurrentRotationTime / TimeToRotate, 0.0f, 1.0f);
				const float RotationAlpha = OpenCurve.GetRichCurveConst()->Eval(TimeRatio);
				const FRotator CurrentRotation = FMath::Lerp(StartRotation, FinalRotation, RotationAlpha);
				GetOwner()->SetActorRotation(CurrentRotation);
			}
		}
	}*/
}

