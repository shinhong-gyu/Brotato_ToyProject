// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HG_GameBaseMode.generated.h"

/**
 *
 */
UCLASS()
class BROTATO_TOYPROJECT_API AHG_GameBaseMode : public AGameModeBase
{
	GENERATED_BODY()

	AHG_GameBaseMode();
private:
	int32 WaveCount = 1;

	float WaveTime = 20.0f;

	UPROPERTY(EditDefaultsOnly)
	float SpawnInterval = 5.0f;

	UPROPERTY(EditDefaultsOnly)
	int32 MaxEnemyCount = 50;

	int32 CurrentEnemyCount = 0;

	class ATestPawn* Player;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AHG_MasterEnemy> EnemyClass; 

	int32 SpawnEnemyCount = 5;
public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void SpawnWarning();

	void SpawnEnemy();


	int32 GetWaveCount() const;

	void UpdateWaveTime();

	void WaveCleared();

	bool bIsWaveStarted = false;

	TArray<FVector> SpawnLoc;
};
