#pragma once

class USimpleButtonWidget;
class UImage;

namespace UiUtils
{
	void UpdateSelectedSimpleButton(int index, TArray<USimpleButtonWidget*> buttons);

	void UpdateInputIcons(bool isGamepad, TArray<UImage*> imageWidgets, TArray<UTexture2D*> gamePadTextures,
						  TArray<UTexture2D*> keyboardTextures);
	int FindButtonIndex(USimpleButtonWidget* button, TArray<USimpleButtonWidget*> buttons);

}

