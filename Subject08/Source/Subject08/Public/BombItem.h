// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "BombItem.generated.h"

/**
 * 
 */
UCLASS()
class SUBJECT08_API ABombItem : public ABaseItem
{
	GENERATED_BODY()

public:
	ABombItem();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
	USphereComponent* ExplosionCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
	UDecalComponent* ExplosionRangeDecal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trap")
	float ExplosionDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trap")
	float ExplosionRadius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trap")
	int ExplosionDamage;

	FTimerHandle ExplosionTimerHandle;
	FTimerHandle DecalUpdateTimerHandle;

	UPROPERTY()
	UMaterialInstanceDynamic* DecalMaterialInstance;

	virtual void ActivateItem(AActor* Activator) override;

	void UpdateDecal();

	void Explode();
};
