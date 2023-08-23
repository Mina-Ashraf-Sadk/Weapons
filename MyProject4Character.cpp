// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyProject4Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"


#define PrintString(x) GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::White,x)


//////////////////////////////////////////////////////////////////////////
// AMyProject4Character (The Constractor)

AMyProject4Character::AMyProject4Character()
{
	// Enable ticking for this actor
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rate for input
	TurnRateGamepad = 50.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	NewCameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("NewCameraBoom"));
	NewCameraBoom->SetupAttachment(RootComponent);
	NewCameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	NewCameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(NewCameraBoom); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	//stores the owned weapons objects in an array and allow the player class to set and get the equiped weapon then the character can communicate with the equipedweapon to call the fire,aim,reload functions  
	PlayerInventory = CreateDefaultSubobject<UWeaponsInventory>(TEXT("Weapons_Component"));
	
	PlayerActionState = CreateDefaultSubobject<UCharacterstate>(TEXT("Action State Component"));

	if (PlayerActionState)
	{
		PlayerActionState->InitialiizeOwner(this);
	}

}

//////////////////////////////////////////////////////////////////////////
// Input

void AMyProject4Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyProject4Character::MyJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMyProject4Character::MyStopJump);

	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &AMyProject4Character::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &AMyProject4Character::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Turn Right / Left Gamepad", this, &AMyProject4Character::TurnAtRate);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &AMyProject4Character::FAiming);
	PlayerInputComponent->BindAxis("Look Up / Down Gamepad", this, &AMyProject4Character::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AMyProject4Character::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AMyProject4Character::TouchStopped);

	//Sprinting 
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AMyProject4Character::Sprinting);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AMyProject4Character::NotSprinting);

	//Taking Cover
	//PlayerInputComponent->BindAction("Cover", IE_Pressed, this, &AMyProject4Character::CoverLineTrace);

	PlayerInputComponent->BindAction("Cover move left", IE_Pressed, this, &AMyProject4Character::CoverRight);
	PlayerInputComponent->BindAction("Cover move right", IE_Pressed, this, &AMyProject4Character::CoverLeft);


}

//////////////////////////////////////////////////////////////////////////
// BeginPlay

void AMyProject4Character::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraShake(CamShake, 1.5f);
	PrintString("Begun");

	//Casting to Character animation instance 
	if (GetMesh()->GetAnimInstance())
	{
		PlayerAnimInstance = dynamic_cast<UCPP_Animation*>(GetMesh()->GetAnimInstance());

	}

	if (PlayerAnimInstance)
	{	
		PlayerAnimInstance->SetActiveAnimation(AnimationActiveState::Unarmed, PlayerCan);

	}

	
	
	
}

//////////////////////////////////////////////////////////////////////////
// Custom Functions


void AMyProject4Character::MyJump()
{
	if (PlayerCan.CanJump)
	{	
		Jump();
		PlayerActionState->bisjumping = ACharacter::bPressedJump;
	}


}

void AMyProject4Character::MyStopJump()
{
		StopJumping();
		PlayerActionState->bisjumping = ACharacter::bPressedJump;
}

void AMyProject4Character::FAiming(float val)
{
	APawn::AddControllerPitchInput(val);

	AimRotationPitch = Controller->GetControlRotation().Pitch * -1;
	 

}

void AMyProject4Character::Sprinting()
{
	if (PlayerCan.CanSprint)
	{
		PlayerActionState->bIsSprinting = true;
		
	}
}

void AMyProject4Character::NotSprinting()
{
	PlayerActionState->bIsSprinting = false;
	
	
}


/*void AMyProject4Character::ReloadCalc()
{	
	//amount that's gonna be taken from the ammo
	int totake;

	//checks if there's any ammo
	if (EquipedWeapon->Ammo > 0)
	{	
		//calculate how many ammo the mag is missing
		totake = EquipedWeapon->MaxMagCapacity - EquipedWeapon->Mag;

		//checks if the ammo has the amount needed
		if (EquipedWeapon->Ammo >= totake)
		{	
			//removes the needed amount from ammo and add it to mag
			EquipedWeapon->Ammo = EquipedWeapon->Ammo - totake;
			EquipedWeapon->Mag = EquipedWeapon->Mag + totake;
		}

		else
		{	
			//if the ammo doesn't have the amount needed then put all what's left of ammo in mag 
			EquipedWeapon->Mag = EquipedWeapon->Mag + EquipedWeapon->Ammo;
			EquipedWeapon->Ammo = 0;

		}
		
	}

	
	else 
	{
		// Play a Sound
	}
	
	
}
*/

/**
void AMyProject4Character::CoverLineTrace()
{
	//Start and End Points for the line Trace
	//GetController()->GetPlayerViewPoint(Loc, FRot);
	//Rot = GetActorRotation();
	Start = GetActorLocation();
	End = Start + (GetActorRotation().Vector() * 100);

	//LineTrace and Debug line
	FCollisionQueryParams CHitParam;
	CHit = GetWorld()->LineTraceSingleByChannel(CoverCheck, Start, End, ECC_GameTraceChannel1, CHitParam);
	DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 2.0f);

	//Hit Check
	if (CHit)
	{	//HitBox
		DrawDebugBox(GetWorld(), CoverCheck.ImpactPoint, FVector(5, 5, 5), FColor::Red, false, 2.0f);
		//check if the Surface is normal
		if (CoverCheck.Normal.Z <= 0) {
			//check if already in cover
			if (!PlayerActionState->bIsInCover)
			{
				PlayerActionState->bIsInCover = true;
				GetCharacterMovement()->SetPlaneConstraintEnabled(true);
				GetCharacterMovement()->SetPlaneConstraintNormal(CoverCheck.Normal);
				GetCharacterMovement()->bOrientRotationToMovement = false;
				GetCharacterMovement()->bUseControllerDesiredRotation = false;
				GetCharacterMovement()->MaxWalkSpeed = 300.f;
				
				FVector RightOfNormal = FVector::CrossProduct(CoverCheck.Normal,FVector::UpVector);
				SetActorRotation(RightOfNormal.Rotation());

				//SetActorRotation((FRotationMatrix(CoverCheck.Normal.Rotation()).GetScaledAxis(EAxis::Y)).Rotation());
				TempAnim = PlayerAnimInstance->GetActiveAnimation();
				PlayerAnimInstance->SetActiveAnimation(AnimationActiveState::Cover, PlayerCan);

			}

			else
			{
				RemoveCover();
			}
		}

		else
		{
			RemoveCover();
		}
	}

	else
	{
		RemoveCover();
	}



}
*/
void AMyProject4Character::RemoveCover()
{
	GetCharacterMovement()->SetPlaneConstraintEnabled(false);
	PlayerActionState->bIsInCover = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	PlayerAnimInstance->SetActiveAnimation(TempAnim, PlayerCan);

}

void AMyProject4Character::CoverLeft()
{
	if (PlayerActionState->bIsInCover)
	{	
		
		FVector RightOfNormal = FVector::CrossProduct(CoverCheck.Normal, FVector::UpVector);
		SetActorRelativeRotation(RightOfNormal.Rotation());

	}
}

void AMyProject4Character::CoverRight()
{	
	if (PlayerActionState->bIsInCover)
	{
		FVector LeftOfNormal = FVector::CrossProduct(CoverCheck.Normal * -1, FVector::UpVector);
		SetActorRelativeRotation(LeftOfNormal.Rotation());
	}
	

}


void AMyProject4Character::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void AMyProject4Character::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void AMyProject4Character::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void AMyProject4Character::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void AMyProject4Character::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f) && !PlayerActionState->bIsInCover)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AMyProject4Character::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

