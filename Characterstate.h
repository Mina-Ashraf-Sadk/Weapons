// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Characterstate.generated.h"

//this component provides the owner class with : -boolean variables that can be used as an action state tracker -and also controls the character movement speed 

class AMyProject4Character;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT4_API UCharacterstate : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterstate();


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Sprint State")
	bool bIsSprinting;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "jump State")
		bool bisjumping;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Idle State")
		bool bIsIdle;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Equip State")
		bool bIsEquiped;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Aiming State")
		bool bIsAiming;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cover State")
		bool bIsInCover;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cover State")
		bool bIsReloading;

	
	
	//Gives Ownership to the created inventory object
	void InitialiizeOwner(AMyProject4Character* Player) { Owner = Player; };
	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void RegulateMovement();
	AMyProject4Character* Owner = 0;
};
