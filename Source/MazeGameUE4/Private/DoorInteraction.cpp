// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorInteraction.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/TriggerBox.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UDoorInteraction::UDoorInteraction()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoorInteraction::BeginPlay()
{
	Super::BeginPlay();
	StartRotation = GetOwner()->GetActorRotation();
	FrontTriggerFinalRotation = GetOwner()->GetActorRotation() + DesiredRotation;
	BackTriggerFinalRotation = GetOwner()->GetActorRotation() + DesiredRotation.Add(0.0f, 180.0f, 0.0f);

	CurrentRotationTime = 0.0f;

	/*DesiredRotation = FRotator(0.0f, 90.0f, 0.0f);
	DeltaRotation = DesiredRotation - GetOwner()->GetActorRotation();
	FinalRotation = GetOwner()->GetActorRotation() + DesiredRotation;*/
	//GetOwner()->SetActorRotation(DesiredRotation);
	
	
}


// Called every frame
// deltatime is frame independent
void UDoorInteraction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CurrentRotationTime >= TimeToRotate)
	{
		CurrentRotationTime = TimeToRotate-DeltaTime;
	}
	if (CurrentRotationTime < 0.0f)
	{
		CurrentRotationTime = 0.0f;
	}

	if (CurrentRotationTime < TimeToRotate)
	{
		// if approaching front of door
		//if (FrontTriggerBox && GetWorld()->GetFirstPlayerController())
		if(FrontTriggerBox || BackTriggerBox && GetWorld()->GetFirstPlayerController())
		{
			APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
			// if player is in front of door
			if (PlayerPawn && FrontTriggerBox->IsOverlappingActor(PlayerPawn))
			{
				CurrentRotationTime += DeltaTime;
				const float TimeRatio = FMath::Clamp(CurrentRotationTime / TimeToRotate, 0.0f, 1.0f);
				const float RotationAlpha = OpenCurve.GetRichCurveConst()->Eval(TimeRatio);
				//const float RotationAlpha = FMath::Clamp(CurrentRotationTime / TimeToRotate, 0.0f, 1.0f);
				const FRotator CurrentRotation = FMath::Lerp(StartRotation, FrontTriggerFinalRotation, RotationAlpha);
				GetOwner()->SetActorRotation(CurrentRotation);
				lastTrigger = 0;
			}
			/*else
			{
				CurrentRotationTime -= DeltaTime;
				const float TimeRatio = FMath::Clamp(CurrentRotationTime / TimeToRotate, 0.0f, 1.0f);
				const float RotationAlpha = OpenCurve.GetRichCurveConst()->Eval(TimeRatio);
				const FRotator CurrentRotation = FMath::Lerp(StartRotation, FrontTriggerFinalRotation, RotationAlpha);
				GetOwner()->SetActorRotation(CurrentRotation);
			}*/
			
			// if player is behind door
			else if (PlayerPawn && BackTriggerBox->IsOverlappingActor(PlayerPawn))
			{
				CurrentRotationTime += DeltaTime;
				const float TimeRatio = FMath::Clamp(CurrentRotationTime / TimeToRotate, 0.0f, 1.0f);
				const float RotationAlpha = OpenCurve.GetRichCurveConst()->Eval(TimeRatio);
				const FRotator CurrentRotation = FMath::Lerp(StartRotation, BackTriggerFinalRotation, RotationAlpha);
				GetOwner()->SetActorRotation(CurrentRotation);
				lastTrigger = 1;
			}
			// if player is not close to either side of the door
			else
			{
				CurrentRotationTime -= DeltaTime;
				const float TimeRatio = FMath::Clamp(CurrentRotationTime / TimeToRotate, 0.0f, 1.0f);
				const float RotationAlpha = OpenCurve.GetRichCurveConst()->Eval(TimeRatio);
				if (lastTrigger == 0)
				{
					const FRotator CurrentRotation = FMath::Lerp(StartRotation, FrontTriggerFinalRotation, RotationAlpha);
					GetOwner()->SetActorRotation(CurrentRotation);
				}
				else
				{
					const FRotator CurrentRotation = FMath::Lerp(StartRotation, BackTriggerFinalRotation, RotationAlpha);
					GetOwner()->SetActorRotation(CurrentRotation);
				}	
			}
		}

		
	}

	/*
	if (CurrentRotationTime < TimeToRotate)
	{
		CurrentRotationTime += DeltaTime;
		const float RotationAlpha = FMath::Clamp(CurrentRotationTime / TimeToRotate, 0.0f, 1.0f);
		const FRotator CurrentRotation = FMath::Lerp(StartRotation, FinalRotation, RotationAlpha);
		GetOwner()->SetActorRotation(CurrentRotation);
	}
	*/

	/*FRotator CurrentRotation = GetOwner()->GetActorRotation();

	if (!CurrentRotation.Equals(FinalRotation, 5.0f))
	{
		CurrentRotation += DeltaRotation*DeltaTime;
		GetOwner()->SetActorRotation(CurrentRotation);
	}*/
}

