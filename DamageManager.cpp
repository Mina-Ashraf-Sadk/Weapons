// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageManager.h"
#include "Kismet/GameplayStatics.h"

//#include "GameFramework/Actor.h"


UDamageManager* UDamageManager::Instance = nullptr;

UDamageManager::~UDamageManager()
{

	
}

void UDamageManager::DealDamageTo(AActor* DamageDealer, int DamageAmount, FHitResult HitResult)
{
	UGameplayStatics::ApplyDamage(HitResult.GetActor(), DamageAmount, DamageDealer->GetInstigatorController(), DamageDealer,UDamageType::StaticClass());
}

UDamageManager* UDamageManager::GetInstance()
{
	if (Instance == nullptr)
	{
		Instance = new UDamageManager();
	}
	return Instance;
}
