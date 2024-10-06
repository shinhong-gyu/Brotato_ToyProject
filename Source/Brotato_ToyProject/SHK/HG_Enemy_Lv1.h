// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HG_MasterEnemy.h"
#include "HG_Enemy_Lv1.generated.h"

UCLASS()
class BROTATO_TOYPROJECT_API AHG_Enemy_Lv1 : public AHG_MasterEnemy
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHG_Enemy_Lv1();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
