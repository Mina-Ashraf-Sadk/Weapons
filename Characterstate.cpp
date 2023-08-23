// Fill out your copyright notice in the Description page of Project Settings.


#include "Characterstate.h"
#include "MyProject4Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"

#define PrintString(x) GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::White,x)

// Sets default values for this component's properties
UCharacterstate::UCharacterstate()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	bisjumping = 0;
	bIsIdle = 0;
	bIsEquiped = 0;
	bIsAiming = 0;
	bIsInCover = 0;
	bIsSprinting = 0;
	bIsReloading = 0;
	
	// ...
}

void UCharacterstate::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	RegulateMovement();
}


void UCharacterstate::RegulateMovement()
{
	if (Owner)
	{
		if (!bIsInCover) {
			if (bIsSprinting)
			{   //Press Button
				if (bIsEquiped)
				{
					if (bIsAiming)
					{	//Equiped and Aiming Sprint
						Owner->GetCharacterMovement()->MaxWalkSpeed = 350.f;
						Owner->GetCharacterMovement()->bUseControllerDesiredRotation = true;
						Owner->GetCharacterMovement()->bOrientRotationToMovement = false;
					}
					else {
						//Equiped and Not Aiming Sprint 
						Owner->GetCharacterMovement()->MaxWalkSpeed = 600.f;
						Owner->GetCharacterMovement()->bUseControllerDesiredRotation = false;
						Owner->GetCharacterMovement()->bOrientRotationToMovement = true;
						

					}

				}
				else
				{	//Not Equiped Sprint
					Owner->GetCharacterMovement()->MaxWalkSpeed = 650.f;
					Owner->GetCharacterMovement()->bUseControllerDesiredRotation = false;
					Owner->GetCharacterMovement()->bOrientRotationToMovement = true;
					
					


				}
			}
			else {
				//Release Button
				if (bIsEquiped)
				{
					if (bIsAiming)
					{
						//Equiped and Aiming Walking
						Owner->GetCharacterMovement()->MaxWalkSpeed = 250.f;
						Owner->GetCharacterMovement()->bUseControllerDesiredRotation = true;
						Owner->GetCharacterMovement()->bOrientRotationToMovement = false;

						

					}
					else {

						//Equiped and Not Aiming Walking
						Owner->GetCharacterMovement()->MaxWalkSpeed = 300.f;
						Owner->GetCharacterMovement()->bUseControllerDesiredRotation = false;
						Owner->GetCharacterMovement()->bOrientRotationToMovement = true;
						
					}

				}
				else
				{
					//Not Equiped Walking
					Owner->GetCharacterMovement()->MaxWalkSpeed = 300.f;
					Owner->GetCharacterMovement()->bUseControllerDesiredRotation = false;
					Owner->GetCharacterMovement()->bOrientRotationToMovement = true;

					
					

				}


			}
		}
	}
}


