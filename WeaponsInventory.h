// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyMasterGun.h"
#include "WeaponsInventory.generated.h"

class AMyProject4Character;


//this class stores the owned weapons objects in an array and allow the player class to set and get the equiped weapon then the character can communicate with the equipedweapon to call the fire,aim and reload functions.

//actor requirments in order to use weapons : -must have a socket with the weapon's name -must have an animation BP that uses the activeanimationstate ENUM -



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT4_API UWeaponsInventory : public UActorComponent
{
	GENERATED_BODY()
public:

	UWeaponsInventory();
	UWeaponsInventory(TArray<AMyMasterGun*> inv,AMyMasterGun* eq) : Inventory(inv) ,EquipedWeapon(eq) {}

	
	UFUNCTION(BlueprintPure)
		 AMyMasterGun* GetEquipedWeapon() ;
	
	
	UFUNCTION(BlueprintCallable)
		void EquipWeapon(int index,AMyProject4Character* Player);
	
	UFUNCTION(BlueprintCallable)
		bool AddToInventory(AMyMasterGun* W);

	

private:
	TArray<AMyMasterGun*> Inventory;
	AMyMasterGun* EquipedWeapon;
	
};




