// Fill out your copyright notice in the Description page of Project Settings.


#include "SHK/TestPawn.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ATestPawn::ATestPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	PrimaryActorTick.bCanEverTick = true;
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	SetRootComponent(BoxComp);


	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);
	MeshComp->SetGenerateOverlapEvents(false);
	MeshComp->SetCollisionProfileName(TEXT("NoCollision"));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArm);

}

// Called when the game starts or when spawned
void ATestPawn::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATestPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	// �¿����, ���Ϲ���
	FVector dir = FVector(v, h, 0);
	// dir�� ���̸� 1�� �����ʹ�.
	dir.Normalize();
	// P = P0 + vt;
	FVector p0 = GetActorLocation();
	FVector velocity = dir * Speed;

	SetActorLocation(p0 + velocity * DeltaTime);

	FVector ActorLocation = GetActorLocation();

	// X, Y ��ǥ�� ���� (�� ��� ����)
	ActorLocation.X = FMath::Clamp(ActorLocation.X, -1940.0f, 1450.0f);
	ActorLocation.Y = FMath::Clamp(ActorLocation.Y, -1540.0f, 1540.0f);

	// ī�޶� ��ġ ����
	SetActorLocation(ActorLocation);
}

// Called to bind functionality to input
void ATestPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	UEnhancedInputComponent* input = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &ATestPawn::OnMyAxisHorizontal);
	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &ATestPawn::OnMyAxisVertical);
}

void ATestPawn::OnMyAxisHorizontal(float value)
{
	h = value;
}

void ATestPawn::OnMyAxisVertical(float value)
{
	v = value;
}



