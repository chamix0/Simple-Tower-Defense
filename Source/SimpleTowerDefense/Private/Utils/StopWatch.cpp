// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/StopWatch.h"

void FStopWatch::Stop()
{
	stopped = true;
}

void FStopWatch::Reset()
{
	stopped = true;
	accumulatedTime = 0.f;
}

void FStopWatch::Start()
{
	if (stopped)
	{
		stopped = false;
	}
}


bool FStopWatch::isRunning() const
{
	return !stopped;
}

float FStopWatch::GetElapsedSeconds() const
{
	return accumulatedTime;
}

float FStopWatch::GetElapsedMiliSeconds() const
{
	return GetElapsedSeconds() * 1000.f;
}

void FStopWatch::AddElapsedTime(float val)
{
	accumulatedTime += val;
}

void FStopWatch::ReStart()
{
	stopped = false;
	accumulatedTime = 0;
}

FStopWatch::FStopWatch(): accumulatedTime(0), stopped(true)
{
}


void FStopWatch::ReceiveTick(float deltaTime)
{
	if (!stopped)
	{
		accumulatedTime += deltaTime;
	}
}
