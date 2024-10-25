// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "StopWatch.generated.h"


USTRUCT()
struct FStopWatch
{
	GENERATED_BODY()

private:
	float accumulatedTime = 0;
	bool stopped = true;

public:
	FStopWatch();

	void ReceiveTick(float deltaTime);
	/// stops the stopwatch
	void Stop();
	///resets the stop watch and stops it
	void Reset();
	///starts the stopwatch if it was stopped
	void Start();


	/// check if its running
	/// @return true if is runing
	bool isRunning() const;
	/// 
	/// @return accumulated seconds
	float GetElapsedSeconds() const;
	//accumulated miliseconds
	float GetElapsedMiliSeconds() const;
	void AddElapsedTime(float val);
	void ReStart();
};
