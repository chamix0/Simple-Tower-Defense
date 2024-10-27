#include "Utils/UIUtils.h"

#include "Components/Image.h"
#include "UI/Basics/SimpleButtonWidget.h"

void UiUtils::UpdateSelectedSimpleButton(int index, TArray<USimpleButtonWidget*> buttons)
{
	//if empty dont do anything
	if (buttons.IsEmpty())
	{
		return;
	}

	//highlight buttons
	for (int i = 0; i < buttons.Num(); ++i)
	{
		
		buttons[i]->SetHighLight(i == index);
	}
}



void UiUtils::UpdateInputIcons(bool isGamepad, TArray<UImage*> imageWidgets, TArray<UTexture2D*> gamePadTextures,
							   TArray<UTexture2D*> keyboardTextures)
{
	for (int i = 0; i < imageWidgets.Num(); ++i)
	{
		UTexture2D* tex = isGamepad ? gamePadTextures[i] : keyboardTextures[i];
		imageWidgets[i]->SetBrushFromTexture(tex);
	}
}

int UiUtils::FindButtonIndex(USimpleButtonWidget* button, TArray<USimpleButtonWidget*> buttons)
{
	for (int i = 0; i < buttons.Num(); ++i)
	{
		if (button == buttons[i])
		{
			return i;
		}
	}
	return -1;
}
