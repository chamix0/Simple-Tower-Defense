#pragma once
#include "Utils/MyEnums.h"


class Observer
{
public:
	virtual void update(const UTowerEvent event);
};
