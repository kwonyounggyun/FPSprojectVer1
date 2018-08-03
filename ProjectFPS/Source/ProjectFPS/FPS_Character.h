// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/InputComponent.h"
#include "Engine.h"
#include "FPS_Character.generated.h"


#define FORWARD 8
#define BACKWARD 4
#define LEFT 2
#define RIGHT 1


UCLASS()
class PROJECTFPS_API AFPS_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPS_Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



public:
	int32 m_Direction, m_Forward, m_RightLeft;
	bool m_Jump, m_sit, m_Run, m_Reload, m_Rolling;

public:
	void MoveForward(float mount);
	void MoveRightLeft(float mount);
	void JumpAction();
	void RunPressAction();
	void RunReleaseAction();
	void RollingAction();
	void SitAction();
	void ReloadAction();
};
