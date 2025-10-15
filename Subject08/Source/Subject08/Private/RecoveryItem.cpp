// Fill out your copyright notice in the Description page of Project Settings.


#include "RecoveryItem.h"
#include "MyCharacter.h"

ARecoveryItem::ARecoveryItem()
{
	HealAmount = 15;
	ItemType = "Healing";
}

void ARecoveryItem::ActivateItem(AActor* Activator)
{
	if (Activator && Activator->ActorHasTag("Player"))
	{
		if (AMyCharacter* PlayerCharacter = Cast<AMyCharacter>(Activator))
		{
			PlayerCharacter->AddHealth(HealAmount);
		}

		DestroyItem();
	}
}
