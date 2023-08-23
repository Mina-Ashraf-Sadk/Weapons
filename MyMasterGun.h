// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyMasterGun.generated.h"


enum class AnimationActiveState : uint8;
class AMyProject4Character;


USTRUCT(BlueprintType)
struct FWeaponInfo
{
	GENERATED_BODY()
public:
	// Variables to transfer to the character
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
		FName SocketName = FName();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
		float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
		float Ammo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
		float Mag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
		float MaxMagCapacity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
		float FireRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
		float GunRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
		float GunRecoil;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
		UAnimMontage* ShootFeedBack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
		UAnimMontage* ReloadAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
		UAnimMontage* MontageToPlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
		USkeletalMesh* SkeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	AnimationActiveState AnimationState;

	bool operator==(const FWeaponInfo& Other) const
	{
		return SocketName == Other.SocketName;
	}


};



UCLASS()
class MYPROJECT4_API AMyMasterGun : public AActor
{
	GENERATED_BODY()

	
public:	
	// Sets default values for this actor's properties
	AMyMasterGun();

	//Gives Ownership to the Weapon
	void InitialiizeOwner(AMyProject4Character* Player) { Owner = Player; };
	
	UFUNCTION(BlueprintCallable)
	virtual void StartShooting();

	UFUNCTION(BlueprintCallable)
	virtual void StopShooting() ;

	UFUNCTION(BlueprintCallable)
	virtual void StartAiming() ;

	UFUNCTION(BlueprintCallable)
	virtual void StopAiming() ;

	UFUNCTION(BlueprintCallable)
	virtual void StartReload() ;

	UFUNCTION(BlueprintCallable)
	virtual void StartSpeicalAction();

	void AttachToOwner();
	
	virtual bool operator==(const AMyMasterGun& Other) const
	{
		return WeaponInfo == Other.WeaponInfo;
	}

	//Skeletal mesh to represent the weapon in the world
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USkeletalMeshComponent* MeshComp;
	//Weapon info
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FWeaponInfo WeaponInfo;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	AMyProject4Character* Owner;
};
