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

void MyDebugUtils::DrawRadius(UWorld* world, FVector& center, float radius, const FColor& Color)
{
	DrawDebugCircle(world, center, radius, 32, Color);
}
