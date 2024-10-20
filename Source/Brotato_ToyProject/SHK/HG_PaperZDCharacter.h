// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "HG_PaperZDCharacter.generated.h"

/**
 *
 */
UCLASS()
class BROTATO_TOYPROJECT_API AHG_PaperZDCharacter : public APaperZDCharacter
{
	GENERATED_BODY()

public:
	AHG_PaperZDCharacter();
protected:

	virtual void BeginPlay() override;

public:
	UPROPERTY(EditDefaultsOnly)
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditDefaultsOnly)
	class UCameraComponent* CameraComp;

	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputMappingContext* IMC_Player;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_Move;


	UFUNCTION()
	void OnMyMove(const FInputActionValue& Value);

	FVector Direction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FVector TempDirection;


};
