// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameState.h"
#include "Kismet/GameplayStatics.h"
#include "SpawnVolume.h"
#include "CoinItem.h"

AMyGameState::AMyGameState()
{
	Score = 0;
	SpawnedCoinCount = 0;
	CollectedCoinCount = 0;
	CurrentLevelIndex = 0;
	MaxLevels = 3;

	CurrentWave = 1;
	MaxWaves = 3;
	WaveTimeLimits.Add(30.0f);
	WaveTimeLimits.Add(25.0f);
	WaveTimeLimits.Add(20.0f);
}

void AMyGameState::BeginPlay()
{
	Super::BeginPlay();

	StartWave();
}

int32 AMyGameState::GetScore() const
{
	return Score;
}

void AMyGameState::AddScore(int32 Amount)
{
	Score += Amount;
	UE_LOG(LogTemp, Warning, TEXT("Score: %d"), Score);
}

void AMyGameState::StartWave()
{
	SpawnedCoinCount = 0;
	CollectedCoinCount = 0;

	TArray<AActor*> FoundVolumes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundVolumes);

	const int32 ItemToSpawn = 10 * CurrentWave; // Increase items per wave

	for (int32 i = 0; i < ItemToSpawn; i++)
	{
		if (FoundVolumes.Num() > 0)
		{
			ASpawnVolume* SpawnVolume = Cast<ASpawnVolume>(FoundVolumes[0]);

			if (SpawnVolume)
			{
				AActor* SpawnedActor = SpawnVolume->SpawnRandomItem();

				if (SpawnedActor && SpawnedActor->IsA(ACoinItem::StaticClass()))
				{
					SpawnedCoinCount++;
				}
			}
		}
	}

	float WaveDuration = WaveTimeLimits[CurrentWave - 1];
	GetWorldTimerManager().SetTimer(
		LevelTimerHandle,
		this,
		&AMyGameState::OnWaveTimeUp,
		WaveDuration,
		false
	);

	UE_LOG(LogTemp, Warning, TEXT("Level %d - Wave %d Start!, Spawned %d coin, Time: %.f"), CurrentLevelIndex + 1, CurrentWave, SpawnedCoinCount, WaveDuration);
}

void AMyGameState::OnWaveTimeUp()
{
	EndWave(false);
}

void AMyGameState::OnCoinCollected()
{
	CollectedCoinCount++;

	UE_LOG(LogTemp, Warning, TEXT("Coin Collected: %d / %d"), CollectedCoinCount, SpawnedCoinCount);

	if (SpawnedCoinCount > 0 && CollectedCoinCount >= SpawnedCoinCount)
	{
		EndWave(true);
	}
}

void AMyGameState::EndWave(bool bSuccess)
{
	GetWorldTimerManager().ClearTimer(LevelTimerHandle);

	if (bSuccess)
	{
		CurrentWave++;
		if (CurrentWave > MaxWaves)
		{
			NextLevel();
		}
		else
		{
			StartWave();
		}
	}
	else // Time ran out
	{
		OnGameOver();
	}
}

void AMyGameState::NextLevel()
{
	CurrentLevelIndex++;

	if (CurrentLevelIndex >= MaxLevels)
	{
		OnGameOver();
		return;
	}

	if (LevelMapNames.IsValidIndex(CurrentLevelIndex))
	{
		UGameplayStatics::OpenLevel(GetWorld(), LevelMapNames[CurrentLevelIndex]);
	}
	else
	{
		OnGameOver();
	}
}

void AMyGameState::UpdateHUD()
{
}

void AMyGameState::OnGameOver()
{
	UE_LOG(LogTemp, Warning, TEXT("GameOver..."));
}