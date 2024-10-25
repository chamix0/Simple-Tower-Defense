#include "Utils/MyDebugUtils.h"

void MyDebugUtils::Print(const FString& Message, const FColor& Color)
{
#if WITH_EDITOR
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 4.f, Color, Message);
	}
#endif
}
