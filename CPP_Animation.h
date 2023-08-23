// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CPP_Animation.generated.h"


UENUM(BlueprintType)
enum class AnimationActiveState : uint8
{
	Unarmed,
	Pistol,
	Rifle,
	Cover
};

USTRUCT(BlueprintType)
struct FCanDo
{
	GENERATED_BODY()
		UPROPERTY(BlueprintReadWrite)
		bool CanJump;
	UPROPERTY(BlueprintReadWrite)
		bool CanSlide;
	UPROPERTY(BlueprintReadWrite)
		bool CanAim;
	UPROPERTY(BlueprintReadWrite)
		bool CanSprint;
	UPROPERTY(BlueprintReadWrite)
		bool CanShoot;
};


UCLASS()
class MYPROJECT4_API UCPP_Animation : public UAnimInstance
{
	GENERATED_BODY()


public:

	UFUNCTION(BlueprintPure, Category = "Animation State", meta=(BlueprintThreadSafe))
		AnimationActiveState GetActiveAnimation() const 
	{
		return ActiveAnimation;
	}
	
	UFUNCTION(BlueprintCallable, Category = "Animation State")
		void SetActiveAnimation(AnimationActiveState Value,UPARAM(ref) FCanDo& Can)
	{
		ActiveAnimation = Value;

		switch (Value)
		{
		case AnimationActiveState::Unarmed:
			Can.CanAim = 0;
			Can.CanJump = 1;
			Can.CanSlide = 1;
			Can.CanSprint = 1;

			break;
		case AnimationActiveState::Rifle:
			Can.CanAim = 1;
			Can.CanJump = 1;
			Can.CanSlide = 0;
			Can.CanSprint = 1;

			break;
		case AnimationActiveState::Pistol:
			Can.CanAim = 1;
			Can.CanJump = 1;
			Can.CanSlide = 0;
			Can.CanSprint = 1;

			break;
		case AnimationActiveState::Cover:
			Can.CanAim = 1;
			Can.CanJump = 0;
			Can.CanSlide = 0;
			Can.CanSprint = 0;

			break;
		default:
			break;
		}
	}

	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bIsAiming = 0;

private:
	
	AnimationActiveState ActiveAnimation = AnimationActiveState::Unarmed;
	
};
