// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyMasterGun.h"
#include "Pistol.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT4_API APistol : public AMyMasterGun
{
	GENERATED_BODY()

protected:

	virtual void StartShooting() override;
	virtual void StopShooting() override;
	virtual void StartAiming() override;
	virtual void StopAiming()  override;
	virtual void StartReload() override;
	virtual void StartSpeicalAction() override;

public:

	UFUNCTION(BlueprintImplementableEvent)
		void OnBulletShot();

	UFUNCTION(BlueprintImplementableEvent)
		void OnBulletHit();

	UFUNCTION(BlueprintImplementableEvent)
		void OnReloading();

	UFUNCTION(BlueprintCallable)
		void ReloadCalc();

	UPROPERTY(BlueprintReadOnly)
		FHitResult HitResult;

	UPROPERTY(BlueprintReadWrite)
		bool Reloading = 0;

private:

	void shoot();

	FRotator rot;
	FVector Start;

	FCollisionQueryParams HitParam;
	bool Hit = false;

};
