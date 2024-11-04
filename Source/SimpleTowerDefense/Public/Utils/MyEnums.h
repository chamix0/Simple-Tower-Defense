﻿#pragma once
#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class UTowerEvent : uint8
{
	IS_DAY,
	IS_NIGHT,
	CROSSHAIR_REACHED_TARGET,
	CROSSHAIR_REQUESTS_TARGET,
	COUNT
};
