// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "RecoveryItem.generated.h"

/**
 * 
 */
UCLASS()
class SUBJECT08_API ARecoveryItem : public ABaseItem
{
	GENERATED_BODY()

public:
	ARecoveryItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 HealAmount;

	virtual void ActivateItem(AActor* Activator) override;
};
