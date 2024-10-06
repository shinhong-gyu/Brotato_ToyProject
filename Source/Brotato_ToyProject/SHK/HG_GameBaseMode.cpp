// Fill out your copyright notice in the Description page of Project Settings.


#include "SHK/HG_GameBaseMode.h"
#include "TestPlayer.h"
#include "Kismet/KismetMathLibrary.h"
#include "HG_Enemy_Lv1.h"



AHG_GameBaseMode::AHG_GameBaseMode()
{
}

void AHG_GameBaseMode::BeginPlay()
{
	Super::BeginPlay();


	Player = Cast<ATestPlayer>(GetWorld()->GetFirstPlayerController()->GetCharacter());

	FTimerHandle handle;
	GetWorldTimerManager().SetTimer(handle, this, &AHG_GameBaseMode::SpawnEnemy, SpawnInterval, true);

}

void AHG_GameBaseMode::SpawnEnemy()
{
	float RandFloat;
	FVector SpawnLocation;
	FRotator SpawnRotation;
	if (CurrentEnemyCount <= MaxEnemyCount)
	{
		for (int32 i = 0; i < 5; i++)
		{
			RandFloat = FMath::FRandRange(300.0f, 1500.0f);
			SpawnLocation = UKismetMathLibrary::RandomPointInBoundingBox(Player->GetActorLocation(), FVector(RandFloat, RandFloat, 0.0f));
			SpawnLocation.X = FMath::Clamp(SpawnLocation.X, -1940.0f, 1450.0f);
			SpawnLocation.Y = FMath::Clamp(SpawnLocation.Y, -1540.0f, 1540.0f);
			SpawnRotation = FRotator::ZeroRotator;
			if (waveCount == 1)
			{
				AHG_Enemy_Lv1* SpawnedEnemy = GetWorld()->SpawnActor<AHG_Enemy_Lv1>(EnemyClass, SpawnLocation, SpawnRotation);
				if (SpawnedEnemy)
				{
					UE_LOG(LogTemp,Warning,TEXT("Lv.1"));
					CurrentEnemyCount++;
				}
			}
		}

	}
}
