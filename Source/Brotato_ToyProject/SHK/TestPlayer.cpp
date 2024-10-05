// Fill out your copyright notice in the Description page of Project Settings.


#include "SHK/TestPlayer.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"

// Sets default values
ATestPlayer::ATestPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATestPlayer::BeginPlay()
{
	Super::BeginPlay();

	auto* pc = Cast<APlayerController>(Controller);
	if (pc)
	{
		UEnhancedInputLocalPlayerSubsystem* subSys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer());
		if (subSys)
		{
			subSys->AddMappingContext(IMC_Player, 0);
		}
	}
	
}

// Called every frame
void ATestPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FTransform t = FTransform(GetControlRotation());
	Direction = t.TransformVector(Direction);

	AddMovementInput(Direction);
	Direction = FVector::ZeroVector;
}

// Called to bind functionality to input
void ATestPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* input = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	input->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ATestPlayer::OnMyMove);

}

void ATestPlayer::OnMyMove(const FInputActionValue& Value)
{
	FVector2D v = Value.Get<FVector2D>();
	Direction.X = v.X;
	Direction.Y = v.Y;
	Direction.Normalize();
}


