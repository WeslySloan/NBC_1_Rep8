// Fill out your copyright notice in the Description page of Project Settings.


#include "ConfuseItem.h"
#include "MyCharacter.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

AConfuseItem::AConfuseItem()
{
	ConfusionDuration = 5.0f;
}

void AConfuseItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);

	TargetCharacter = Cast<AMyCharacter>(Activator);
	if (TargetCharacter)
	{
		TargetCharacter->SetConfused(true);

		GetWorld()->GetTimerManager().SetTimer(
			ConfusionTimerHandle,
			this,
			&AConfuseItem::ResetConfusion,
			ConfusionDuration,
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

void AConfuseItem::ResetConfusion()
{
	if (TargetCharacter)
	{
		TargetCharacter->SetConfused(false);
	}

	DestroyItem();
}
