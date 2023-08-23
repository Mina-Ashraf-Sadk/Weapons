// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class MYPROJECT4_API UDamageManager
{
public:
	~UDamageManager();

	void DealDamageTo(AActor* DamageDealer,int DamageAmount,FHitResult HitResult);
	
	static UDamageManager* GetInstance();

private:
	
	UDamageManager() {}
	static UDamageManager* Instance;
};
