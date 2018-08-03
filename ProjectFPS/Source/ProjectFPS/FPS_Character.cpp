// Fill out your copyright notice in the Description page of Project Settings.

#include "FPS_Character.h"


// Sets default values
AFPS_Character::AFPS_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	GetMesh()->SetHiddenInGame(true, true);

}

// Called when the game starts or when spawned
void AFPS_Character::BeginPlay()
{
	Super::BeginPlay();


	m_Direction = 0;
	m_Forward = 0;
	m_RightLeft = 0;
	m_Jump = false;
	m_Rolling = false;
	m_sit = false;
	m_Run = false;
	m_Reload = false;

	GetMesh()->HideBoneByName("upperarm_l", EPhysBodyOp::PBO_None);

	for (int32 index = 1; GetMesh()->BoneVisibilityStates.Num(); ++index)
	{
		GetMesh()->BoneVisibilityStates[index] = EBoneVisibilityStatus::BVS_ExplicitlyHidden;
	}
	//GetMesh()->BoneVisibilityStates[GetMesh()->GetBoneIndex("spine_01")] = EBoneVisibilityStatus::BVS_ExplicitlyHidden;
	GetMesh()->BoneVisibilityStates[GetMesh()->GetBoneIndex("hand_l")] = EBoneVisibilityStatus::BVS_Visible;
	GetMesh()->RebuildVisibilityArray();
	
}

// Called every frame
void AFPS_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	m_Direction = m_Forward + m_RightLeft;
}

// Called to bind functionality to input
void AFPS_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Forward", this, &AFPS_Character::MoveForward);
	PlayerInputComponent->BindAxis("RightLeft", this, &AFPS_Character::MoveRightLeft);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPS_Character::JumpAction);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AFPS_Character::RunPressAction);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &AFPS_Character::RunReleaseAction);
	PlayerInputComponent->BindAction("Rolling", IE_Pressed, this, &AFPS_Character::RollingAction);
	PlayerInputComponent->BindAction("Sit", IE_Pressed, this, &AFPS_Character::SitAction);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &AFPS_Character::ReloadAction);
}

void AFPS_Character::MoveForward(float mount)
{
	if (mount > 0)
	{
		m_Forward = FORWARD;
	}
	else if (mount < 0)
	{
		m_Forward = BACKWARD;
	}
	else
	{
		m_Forward = 0;
	}
}

void AFPS_Character::MoveRightLeft(float mount)
{
	if (mount > 0)
	{
		m_RightLeft = LEFT;
	}
	else if (mount < 0)
	{
		m_RightLeft = RIGHT;
	}
	else
	{
		m_RightLeft = 0;
	}
}

void AFPS_Character::JumpAction()
{
	if (!m_Jump)
	{
		m_Jump = true;         //애니메이션 끝나면 true로 전환
	}
}

void AFPS_Character::RunPressAction()
{
	m_Run = true;
}

void AFPS_Character::RunReleaseAction()
{
	m_Run = false;
}

void AFPS_Character::RollingAction()
{
	if (!m_Rolling)
		m_Rolling = true;    //애니메이션 끝나면 true로 전환
}

void AFPS_Character::SitAction()
{
	if (m_sit)
	{
		m_sit = false;
	}
	else
	{
		m_sit = true;
	}

}

void AFPS_Character::ReloadAction()
{
	if (!m_Reload)
	{
		m_Reload = true;
	}
}

