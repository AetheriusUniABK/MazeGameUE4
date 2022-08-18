// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "GoalDoor.generated.h"

class UGoalDoorComponent;

UCLASS()
class MAZEGAMEUE4_API AGoalDoor : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	AGoalDoor();

protected:
	UPROPERTY(EditAnywhere, NoClear)
	UGoalDoorComponent* GoalDoorComponent;
};
