// Fill out your copyright notice in the Description page of Project Settings.


#include "SHK/HG_GameBaseMode.h"
#include "TestPlayer.h"
#include "Kismet/KismetMathLibrary.h"
#include "HG_Enemy_Lv1.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/Material.h"
#include "TestPawn.h"


AHG_GameBaseMode::AHG_GameBaseMode()
{
}

void AHG_GameBaseMode::BeginPlay()
{
	Super::BeginPlay();


	Player = Cast<ATestPawn>(GetWorld()->GetFirstPlayerController()->GetCharacter());

	FTimerHandle handle;
	FTimerHandle SpawnWarningHandle;

	GetWorldTimerManager().SetTimer(SpawnWarningHandle, this, &AHG_GameBaseMode::SpawnWarning, SpawnInterval, true, 2.0f);
	GetWorldTimerManager().SetTimer(handle, this, &AHG_GameBaseMode::SpawnEnemy, SpawnInterval, true, 3.0f);
}

void AHG_GameBaseMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsWaveStarted)
	{
		WaveTime -= DeltaTime;
		if (WaveTime <= 0)
		{
			WaveCleared();
		}
	}

}

void AHG_GameBaseMode::SpawnWarning()
{
	if (bIsWaveStarted)
	{
		float RandFloat;
		FVector SpawnLocation;
		SpawnLoc = TArray<FVector>();


		for (int32 i = 0; i < SpawnEnemyCount; i++)
		{
			RandFloat = FMath::FRandRange(300.0f, 1500.0f);
			SpawnLocation = UKismetMathLibrary::RandomPointInBoundingBox(Player->GetActorLocation(), FVector(RandFloat, RandFloat, 0.0f));
			SpawnLocation.X = FMath::Clamp(SpawnLocation.X, -1940.0f, 1450.0f);
			SpawnLocation.Y = FMath::Clamp(SpawnLocation.Y, -1540.0f, 1540.0f);
			SpawnLoc.Add(SpawnLocation);
		}

		UMaterial* DecalMaterial = LoadObject<UMaterial>(nullptr, TEXT("/Script/Engine.Material'/Game/SHK/Material/M_SpawnDecal.M_SpawnDecal'"));

		FRotator DecalRot = FRotator(-90.0f, 0.0f, -90.0f);
		for (int32 i = 0; i < SpawnEnemyCount; i++)
		{
			FVector TempV = SpawnLoc[i];
			TempV.Z = 0;
			UGameplayStatics::SpawnDecalAtLocation(GetWorld(), DecalMaterial, FVector(100.0f), TempV, DecalRot, 1.0f);
		}
	}
}

void AHG_GameBaseMode::SpawnEnemy()
{
	if (bIsWaveStarted)
	{
		FRotator SpawnRotation;
		float RandFloat;

		if (CurrentEnemyCount <= MaxEnemyCount)
		{
			for (int32 i = 0; i < SpawnEnemyCount; i++)
			{
				RandFloat = FMath::FRandRange(300.0f, 1500.0f);
				SpawnRotation = FRotator::ZeroRotator;
				if (WaveCount == 1)
				{
					AHG_Enemy_Lv1* SpawnedEnemy = GetWorld()->SpawnActor<AHG_Enemy_Lv1>(EnemyClass, SpawnLoc[i], SpawnRotation);
					if (SpawnedEnemy)
					{
						CurrentEnemyCount++;
					}
				}
			}
		}
	}
}

int32 AHG_GameBaseMode::GetWaveCount() const
{
	return WaveCount;
}

void AHG_GameBaseMode::UpdateWaveTime()
{
	WaveTime = FMath::Clamp(WaveTime, WaveTime + (WaveCount - 1) * 5, 60.0f);
}

void AHG_GameBaseMode::WaveCleared()
{
	WaveCount += 1;
	UpdateWaveTime();

	// 레벨이 있는 모든 적 파괴
	TArray<AActor*> OutActors;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), EnemyClass, OutActors);
	if (!OutActors.IsEmpty())
	{
		for (auto Enemy : OutActors)
		{
			Enemy->Destroy();
		}
	}

	// 레벨에 있는 모든 재화 흡수/파괴 그리고 카운팅 (다음 웨이브에 2배되는 로직때문에)

	// 레벨업한 만큼 능력치 올리는 UI 팝업 -> 선택 다했으면 상점 UI 팝업
}
