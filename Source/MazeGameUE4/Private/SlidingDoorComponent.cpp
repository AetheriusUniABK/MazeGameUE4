// Fill out your copyright notice in the Description page of Project Settings.


#include "SlidingDoorComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/TriggerBox.h"
#include "Engine/World.h"

// Sets default values for this component's properties
USlidingDoorComponent::USlidingDoorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USlidingDoorComponent::BeginPlay()
{
	Super::BeginPlay();
	StartPosition = GetOwner()->GetActorLocation();
	FinalPosition = GetOwner()->GetActorLocation() + DesiredTranslation;

	CurrentTranslationTime = 0.0f;
	
}


// Called every frame
void USlidingDoorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CurrentTranslationTime >= TimeToTranslate)
	{
		CurrentTranslationTime = TimeToTranslate - DeltaTime;
	}
	if (CurrentTranslationTime < 0.0f)
	{
		CurrentTranslationTime = 0.0f;
	}

	if (CurrentTranslationTime < TimeToTranslate)
	{
		// if approaching front of door
		if (TriggerBox && GetWorld()->GetFirstPlayerController())
		{
			APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
			// if player is in front of door
			if (PlayerPawn && TriggerBox->IsOverlappingActor(PlayerPawn))
			{
				CurrentTranslationTime += DeltaTime;
				const float TimeRatio = FMath::Clamp(CurrentTranslationTime / TimeToTranslate, 0.0f, 1.0f);
				const float TranslationAlpha = OpenCurve.GetRichCurveConst()->Eval(TimeRatio);
				const FVector CurrentRotation = FMath::Lerp(StartPosition, FinalPosition, TranslationAlpha);
				GetOwner()->SetActorLocation(CurrentRotation);
			}

			// if player is not close to the door
			else
			{
				CurrentTranslationTime -= DeltaTime;
				const float TimeRatio = FMath::Clamp(CurrentTranslationTime / TimeToTranslate, 0.0f, 1.0f);
				const float TranslationAlpha = OpenCurve.GetRichCurveConst()->Eval(TimeRatio);
				const FVector CurrentRotation = FMath::Lerp(StartPosition, FinalPosition, TranslationAlpha);
				GetOwner()->SetActorLocation(CurrentRotation);
			}
		}
	}
}

