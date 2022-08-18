// Fill out your copyright notice in the Description page of Project Settings.


#include "GoalDoor.h"
#include "GoalDoorComponent.h"

AGoalDoor::AGoalDoor()
{
	GoalDoorComponent = CreateDefaultSubobject<UGoalDoorComponent>(TEXT("GoalDoor"));
}
