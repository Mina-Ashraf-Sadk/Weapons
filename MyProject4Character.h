// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Character.h"
#include "MyMatineeCameraShake.h"
#include "Characterstate.h"
#include "WeaponsInventory.h"
#include "CPP_Animation.h"
//#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "MyProject4Character.generated.h"







UCLASS(config=Game)
class AMyProject4Character : public ACharacter
{
	GENERATED_BODY()

	

		void MyJump();
		void MyStopJump();
		void FAiming(float val);
		void Sprinting();
		void NotSprinting();
		void RemoveCover();
		void CoverLeft();
		void CoverRight();
	
		AnimationActiveState TempAnim;
	
		bool CHit;
		

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* NewCameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	AMyProject4Character();

	virtual void BeginPlay() override;
	

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Input)
	float TurnRateGamepad;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		double AimRotationPitch;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	FHitResult CoverCheck;

	//Idle CameraShake that takes a value inside the character blueprint
	UPROPERTY(EditAnywhere)
	TSubclassOf<UMatineeCameraShake> CamShake;
	
	UPROPERTY(EditAnywhere)
	UCPP_Animation* PlayerAnimInstance;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FCanDo PlayerCan;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon Component")
		UWeaponsInventory* PlayerInventory;

	UPROPERTY(BlueprintReadWrite, Category = "Action State Component")
		UCharacterstate* PlayerActionState;


// Functions*******************************************************************************************************
	

	/*UFUNCTION(BlueprintCallable, Category = "Shooting")
	void ReloadCalc();*/

	//UFUNCTION(BlueprintCallable, Category = "Shooting")
	//	void CoverLineTrace();

	UFUNCTION(BlueprintImplementableEvent)
		void ChangeAnimToCover();
	
	UFUNCTION(BlueprintImplementableEvent)
		void OnStartAiming();
	
	UFUNCTION(BlueprintImplementableEvent)
		void OnStopAiming();
	
	UFUNCTION(BlueprintImplementableEvent)
		void PreviousAnimState();

	UFUNCTION(BlueprintImplementableEvent)
		void Reload();


	

protected:

	FTimeline CurveTimeline;

	UPROPERTY(EditAnywhere, Category = "Camera trans")
	UCurveFloat* CurveFloat;


	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

	

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return NewCameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

