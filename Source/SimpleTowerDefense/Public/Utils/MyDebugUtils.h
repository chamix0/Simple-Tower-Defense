#pragma once
namespace MyDebugUtils
{
	void Print(const FString& Message, const FColor& Color = FColor::Yellow);
	void DrawRadius(UWorld* world, FVector& center, float radius, const FColor& Color);
}
