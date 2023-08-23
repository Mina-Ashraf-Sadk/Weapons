// Fill out your copyright notice in the Description page of Project Settings.


#include "MyMasterGun.h"
#include "MyProject4Character.h"

#define PrintString(x) GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::White,x)
// Sets default values
AMyMasterGun::AMyMasterGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));

}

void AMyMasterGun::StartShooting() 
{
	
	PrintString("Base");
}

void AMyMasterGun::StopShooting() 
{
}

void AMyMasterGun::StartAiming() 
{
}

void AMyMasterGun::StopAiming() 
{
}

void AMyMasterGun::StartReload() 
{
	
}

void AMyMasterGun::StartSpeicalAction()  
{
}

void AMyMasterGun::AttachToOwner()
{
	MeshComp->SetHiddenInGame(false);
	AttachToComponent(Owner->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, WeaponInfo.SocketName);
	Owner->PlayerAnimInstance->SetActiveAnimation(WeaponInfo.AnimationState, Owner->PlayerCan);
	Owner->PlayerActionState->bIsEquiped = true;
	
}



