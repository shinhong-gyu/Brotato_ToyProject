// Fill out your copyright notice in the Description page of Project Settings.


#include "SHK/HG_EnemyStatusComponent.h"
#include "HG_GameBaseMode.h"

// Sets default values for this component's properties
UHG_EnemyStatusComponent::UHG_EnemyStatusComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHG_EnemyStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHG_EnemyStatusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	auto* GM = Cast<AHG_GameBaseMode>(GetWorld()->GetAuthGameMode());
	CurrentWave = GM->GetWaveCount();
}

void UHG_EnemyStatusComponent::SetDamage()
{
}

void UHG_EnemyStatusComponent::SetHP()
{
}

