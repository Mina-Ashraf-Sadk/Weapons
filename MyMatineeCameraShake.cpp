// Fill out your copyright notice in the Description page of Project Settings.


#include "MyMatineeCameraShake.h"
#include "Math/UnrealMathUtility.h"


UMyMatineeCameraShake::UMyMatineeCameraShake()
{
	OscillationDuration = -1.f;
	OscillationBlendInTime = 0.1f;
	OscillationBlendOutTime = 0.1f;

	LocOscillation.X.Amplitude = 10.f;
	LocOscillation.X.Frequency = 50.f;

	LocOscillation.Y.Amplitude = 10.f;
	LocOscillation.Y.Frequency = 50.f;

	LocOscillation.Z.Amplitude = 10.f;
	LocOscillation.Z.Frequency = 50.f;
}

