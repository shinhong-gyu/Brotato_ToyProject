// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HG_MasterEnemy.generated.h"

UCLASS()
class BROTATO_TOYPROJECT_API AHG_MasterEnemy : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHG_MasterEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FVector Direction;

	UPROPERTY(EditDefaultsOnly)
	float Speed = 200.0f;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

	class ATestPawn* Target;
	// Appearance
	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* MeshComp;

	UPROPERTY(EditDefaultsOnly)
	class UBoxComponent* BoxComp;

	UFUNCTION()
	void OnMyBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditDefaultsOnly)
	class UHG_EnemyStatusComponent* StatusComp;
};
