// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "SlowItem.generated.h"

/**
 * 
 */
UCLASS()
class SUBJECT08_API ASlowItem : public ABaseItem
{
	GENERATED_BODY()

	public:
	ASlowItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trap")
	float SlowMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trap")
	float SlowDuration;

	virtual void ActivateItem(AActor* Activator) override;

protected:
	void ResetSpeed();

	FTimerHandle SlowTimerHandle;

	UPROPERTY()
		TObjectPtr<class AMyCharacter> TargetCharacter;	
};
