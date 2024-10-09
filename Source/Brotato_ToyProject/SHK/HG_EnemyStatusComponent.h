// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HG_EnemyStatusComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BROTATO_TOYPROJECT_API UHG_EnemyStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHG_EnemyStatusComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
private:
	UPROPERTY(EditDefaultsOnly)
	int32 RewardExp;

	UPROPERTY(EditDefaultsOnly)
	int32 HP;
	
	UPROPERTY(EditDefaultsOnly)
	int32 Damage;

	UPROPERTY(EditDefaultsOnly)
	int32 Speed;

	int32 CurrentWave;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void SetDamage();

	virtual void SetHP();
};
