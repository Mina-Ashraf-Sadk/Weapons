// Fill out your copyright notice in the Description page of Project Settings.


#include "Pistol.h"
#include "MyProject4Character.h"
#define PrintString(x) GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::White,x)

void APistol::StartShooting()
{
	if (Owner->PlayerActionState->bIsAiming)
	{
		shoot();


	}
}

void APistol::StopShooting()
{
}


void APistol::StartAiming()
{
	Owner->PlayerActionState->bIsAiming = true;
	Owner->OnStartAiming();
}

void APistol::StopAiming()
{
	Owner->PlayerActionState->bIsAiming = false;
	Owner->OnStopAiming();
}



void APistol::StartReload()
{
	if (!Reloading && WeaponInfo.Ammo > 0)
	{
		Reloading = true;
		OnReloading();

	}

	else if (WeaponInfo.Ammo <= 0)
	{
		// Play a Sound
	}

}

void APistol::ReloadCalc()
{
	//amount that's gonna be taken from the ammo

	int totake = 0;

	//calculate how many ammo the mag is missing
	totake = WeaponInfo.MaxMagCapacity - WeaponInfo.Mag;

	//checks if the ammo has the amount needed
	if (WeaponInfo.Ammo >= totake)
	{
		//removes the needed amount from ammo and add it to mag
		WeaponInfo.Ammo = WeaponInfo.Ammo - totake;
		WeaponInfo.Mag = WeaponInfo.Mag + totake;
	}

	else
	{
		//if the ammo doesn't have the amount needed then put all what's left of ammo in mag 
		WeaponInfo.Mag = WeaponInfo.Mag + WeaponInfo.Ammo;
		WeaponInfo.Ammo = 0;

	}


}



void APistol::StartSpeicalAction()
{
}

void APistol::shoot()
{
	if (WeaponInfo.Mag > 0)
	{

		Owner->GetController()->GetPlayerViewPoint(Start, rot);

		FVector End = Start + (rot.Vector() * WeaponInfo.GunRange);

		Hit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_GameTraceChannel1, HitParam);
		DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 2.0f);

		if (Hit)
		{
			OnBulletHit();
			DrawDebugBox(GetWorld(), HitResult.ImpactPoint, FVector(5, 5, 5), FColor::Red, false, 2.0f);
			PrintString("hit");


		}

		WeaponInfo.Mag--;
		Owner->AddControllerPitchInput(WeaponInfo.GunRecoil);
		OnBulletShot();
		PrintString("derived");
	}
	else
	{
		StartReload();
	}
	
}

