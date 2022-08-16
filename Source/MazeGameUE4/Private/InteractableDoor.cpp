// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableDoor.h"
#include "DoorInteraction.h"

AInteractableDoor::AInteractableDoor()
{
	DoorInteraction = CreateDefaultSubobject<UDoorInteraction>(TEXT("DoorInteraction"));
}
