// Fill out your copyright notice in the Description page of Project Settings.


#include "SHK/HG_PaperZDCharacter.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

AHG_PaperZDCharacter::AHG_PaperZDCharacter()
{

	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArm);
}

void AHG_PaperZDCharacter::BeginPlay()
{
	Super::BeginPlay();

	TempDirection.X = -1.0f;
	TempDirection.Y = 0.0f;

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

void AHG_PaperZDCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FTransform t = FTransform(GetControlRotation());
	Direction = t.TransformVector(Direction);

	AddMovementInput(Direction);
	Direction = FVector::ZeroVector;
	
	// Tick Event에서 실행
	FVector ActorLocation = GetActorLocation();

	// X, Y 좌표를 제한 (맵 경계 설정)
	ActorLocation.X = FMath::Clamp(ActorLocation.X, -1940.0f, 1450.0f);
	ActorLocation.Y = FMath::Clamp(ActorLocation.Y, -1540.0f, 1540.0f);

	// 카메라 위치 설정
	SetActorLocation(ActorLocation);
}

void AHG_PaperZDCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* input = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	input->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AHG_PaperZDCharacter::OnMyMove);

}

void AHG_PaperZDCharacter::OnMyMove(const FInputActionValue& Value)
{
	FVector2D v = Value.Get<FVector2D>();
	Direction.X = v.X;
	Direction.Y = v.Y;
	TempDirection.X = v.X;
	TempDirection.Y = v.Y;
	Direction.Normalize();
}
