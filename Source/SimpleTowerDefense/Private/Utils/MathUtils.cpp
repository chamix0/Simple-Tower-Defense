#include "Utils/MathUtils.h"

float MathUtils::NormalizeBetweenValues(float value, float min, float max)
{
	return (value - min) / (max - min);
}
