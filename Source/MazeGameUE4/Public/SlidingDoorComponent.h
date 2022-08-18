// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Curves/CurveFloat.h"
#include "SlidingDoorComponent.generated.h"

class ATriggerBox;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAZEGAMEUE4_API USlidingDoorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USlidingDoorComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	FVector DesiredTranslation = FVector::ZeroVector;

	FVector StartPosition = FVector::ZeroVector;
	FVector FinalPosition = FVector::ZeroVector;

	UPROPERTY(EditAnywhere)
	float TimeToTranslate = 1.0f;

	float CurrentTranslationTime = 0.0f;

	UPROPERTY(EditAnywhere)
	ATriggerBox* TriggerBox;

	UPROPERTY(EditAnywhere)
	FRuntimeFloatCurve OpenCurve;		
};
