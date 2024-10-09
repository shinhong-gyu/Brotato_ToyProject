// Fill out your copyright notice in the Description page of Project Settings.


#include "SHK/HG_MasterEnemy.h"
#include "TestPlayer.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "HG_EnemyStatusComponent.h"

// Sets default values
AHG_MasterEnemy::AHG_MasterEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	SetRootComponent(BoxComp);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(BoxComp);

	BoxComp->OnComponentBeginOverlap.AddDynamic(this,&AHG_MasterEnemy::OnMyBoxBeginOverlap);
	BoxComp->SetGenerateOverlapEvents(true);
	BoxComp->SetCollisionProfileName(TEXT("Enemy"));

	MeshComp->SetCollisionProfileName(TEXT("NoCollision"));

	StatusComp = CreateDefaultSubobject<UHG_EnemyStatusComponent>(TEXT("StatusComp"));
}

// Called when the game starts or when spawned
void AHG_MasterEnemy::BeginPlay()
{
	Super::BeginPlay();

	Target = Cast<ATestPlayer>(GetWorld()->GetFirstPlayerController()->GetCharacter());
}

// Called every frame
void AHG_MasterEnemy::Tick(float DeltaTime)
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

void AHG_MasterEnemy::OnMyBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto* Player = Cast<ATestPlayer>(OtherActor);
	if (Player) {
		this->Destroy();
	}
}

