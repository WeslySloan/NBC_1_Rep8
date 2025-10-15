// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "ConfuseItem.generated.h"

/**
 * 
 */
UCLASS()
class SUBJECT08_API AConfuseItem : public ABaseItem
{
	GENERATED_BODY()

public:
	AConfuseItem();

protected:
	virtual void ActivateItem(AActor* Activator) override;

	void ResetConfusion();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float ConfusionDuration;

	FTimerHandle ConfusionTimerHandle;

	UPROPERTY()
	TObjectPtr<class AMyCharacter> TargetCharacter;
	
};
