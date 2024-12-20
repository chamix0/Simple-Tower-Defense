// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menus/QuitToMenu/QuitToMenuScreen.h"

#include "Kismet/GameplayStatics.h"
#include "UI/Basics/SimpleButtonWidget.h"
#include "Utils/GameUtils.h"

void UQuitToMenuScreen::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	//add buttons to array
	AddButton(Button_Cancel);
	AddButton(Button_QuitToMenu);

	//button on click callbacks
	Button_Cancel->OnButtonSelected.BindDynamic(this, &ThisClass::CancelButtonAction);
	Button_QuitToMenu->OnButtonSelected.BindDynamic(this, &ThisClass::QuitToMenuButtonAction);

	// auxInputAction->OnInputMethodChanged.AddDynamic(this, &ThisClass::OnInputMethodChanged);
}

void UQuitToMenuScreen::NativeOnActivated()
{
	Super::NativeOnActivated();
}

void UQuitToMenuScreen::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}


void UQuitToMenuScreen::CancelButtonAction()
{
	HandleReturnAction();
}

void UQuitToMenuScreen::HandleReturnAction()
{
	Super::HandleReturnAction();
}

void UQuitToMenuScreen::QuitToMenuButtonAction()
{
	GameUtils::LoadMainMenu(GetWorld());
}

// void UQuitToMenuScreen::OnInputMethodChanged(bool usingGamepad)
// {
// 	if (usingGamepad)
// 	{
// 		m_blockingScreen->SetVisibility(ESlateVisibility::Visible);
// 	}else
// 	{
// 		m_blockingScreen->SetVisibility(ESlateVisibility::Collapsed);
//
// 	}
// 	
// }
