// Fill out your copyright notice in the Description page of Project Settings.


#include "SlowItem.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "MyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

ASlowItem::ASlowItem()
{
	SlowMultiplier = 0.5f;
	SlowDuration = 3.0f;
	ItemType = "Trap";
}

void ASlowItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);

	TargetCharacter = Cast<AMyCharacter>(Activator);
	if (TargetCharacter)
	{
		TargetCharacter->SetSpeedMultiplier(SlowMultiplier);

		GetWorld()->GetTimerManager().SetTimer(
			SlowTimerHandle,
			this,
			&ASlowItem::ResetSpeed,
			SlowDuration,
			false
		);

		if (StaticMesh)
		{
			StaticMesh->SetVisibility(false);
			StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
		if (Collision)
		{
			Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}
}

void ASlowItem::ResetSpeed()
{
	if (TargetCharacter)
	{
		TargetCharacter->SetSpeedMultiplier(1.0f);
	}

	DestroyItem();
}
