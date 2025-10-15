// Fill out your copyright notice in the Description page of Project Settings.

#include "BombItem.h"
#include "Components/SphereComponent.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"



ABombItem::ABombItem()

{
	ExplosionDelay = 3.0f;
	ExplosionRadius = 500.0f;
	ExplosionDamage = 25;
	ItemType = "Trap";
	ExplosionCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ExplosionCollision"));
	ExplosionCollision->InitSphereRadius(ExplosionRadius);
	ExplosionCollision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	ExplosionCollision->SetupAttachment(Scene);
	ExplosionRangeDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("ExplosionRangeDecal"));
	ExplosionRangeDecal->SetupAttachment(Scene);
	ExplosionRangeDecal->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f));
	ExplosionRangeDecal->DecalSize = FVector(ExplosionRadius, ExplosionRadius, ExplosionRadius);

}



void ABombItem::ActivateItem(AActor* Activator)

{

	Super::ActivateItem(Activator);

	if (ExplosionRangeDecal)

	{
		DecalMaterialInstance = ExplosionRangeDecal->CreateDynamicMaterialInstance();
	}

	GetWorld()->GetTimerManager().SetTimer(
		ExplosionTimerHandle,
		this,
		&ABombItem::Explode,
		ExplosionDelay,
		false
	);

	GetWorld()->GetTimerManager().SetTimer(
		DecalUpdateTimerHandle,
		this,
		&ABombItem::UpdateDecal,
		0.01f,
		true
	);

}

void ABombItem::UpdateDecal()

{
	float ElapsedTime = GetWorld()->GetTimerManager().GetTimerElapsed(ExplosionTimerHandle);
	float FillAmount = FMath::Clamp(ElapsedTime / ExplosionDelay, 0.0f, 1.0f);

	if (DecalMaterialInstance)

	{
		DecalMaterialInstance->SetScalarParameterValue(TEXT("Fill"), FillAmount);
	}
}



void ABombItem::Explode()
{
	TArray<AActor*> OverlappingActors;
	ExplosionCollision->GetOverlappingActors(OverlappingActors);

	for (AActor* Actor : OverlappingActors)

	{
		if (Actor && Actor->ActorHasTag("Player"))
		{
			UGameplayStatics::ApplyDamage(
				Actor,
				ExplosionDamage,
				nullptr,
				this,
				UDecalComponent::StaticClass()
			);
		}
	}
	DestroyItem();

}