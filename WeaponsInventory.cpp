// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponsInventory.h"
#include "MyProject4Character.h"

#define PrintString(x) GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::White,x)


UWeaponsInventory::UWeaponsInventory()
{
	EquipedWeapon = 0;
	Inventory.Empty();
}

AMyMasterGun* UWeaponsInventory::GetEquipedWeapon()
{
	if (EquipedWeapon)
	{
		return EquipedWeapon;
	}
	else
	{
		return 0;
	}
}

void UWeaponsInventory::EquipWeapon(int index, AMyProject4Character* Player)
{
	
	if (Inventory.IsValidIndex(index) && Player)
	{
		EquipedWeapon = Inventory[index];
		EquipedWeapon->InitialiizeOwner(Player);
		EquipedWeapon->AttachToOwner();
		Player->PlayerAnimInstance->SetActiveAnimation(EquipedWeapon->WeaponInfo.AnimationState, Player->PlayerCan);
		PrintString("Equiped");

		//Player->MeshComp->SetSkeletalMesh(EquipedWeapon->WeaponInfo.SkeletalMesh;
	}
}
bool UWeaponsInventory::AddToInventory(AMyMasterGun* W)
{	
	if (Inventory.IsEmpty())
	{
		Inventory.Add(W);
		return true;
	}
	
	for (AMyMasterGun* item : Inventory)
	{
		if (!(*item == *W))
		{
			Inventory.AddUnique(W);
			return true;
		}

	}

	return false;

}
//
//bool UWeaponsInventory::AddWeaponToInventory(AMyMasterGun* Weap)
//
//{
//	if (!Inventory.Contains(Weap))
//	{
//		Inventory.AddUnique(Weap);
//		return true;
//	}
//
//	else
//	{
//		return false;
//	}
//}

