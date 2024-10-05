// Fill out your copyright notice in the Description page of Project Settings.


#include "SHK/HG_Enemy_Lv1.h"
#include "TestPlayer.h"

// Sets default values
AHG_Enemy_Lv1::AHG_Enemy_Lv1()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Speed = 100.0f;
}

// Called when the game starts or when spawned
void AHG_Enemy_Lv1::BeginPlay()
{
	Super::BeginPlay();

	Target = Cast<ATestPlayer>(GetWorld()->GetFirstPlayerController()->GetCharacter());
}

// Called every frame
void AHG_Enemy_Lv1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Target)
	{
		Direction = Target->GetActorLocation() - this->GetActorLocation();
		Direction.Z = 0;
		Direction.Normalize();

		SetActorLocation(GetActorLocation() + Direction * Speed * DeltaTime);
	}
}

