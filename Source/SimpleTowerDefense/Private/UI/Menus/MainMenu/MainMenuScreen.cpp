// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menus/MainMenu/MainMenuScreen.h"

#include "UI/Basics/SimpleButtonWidget.h"
#include "Utils/GameUtils.h"


void UMainMenuScreen::NativeOnInitialized()
{
	Super::NativeOnInitialized();


	//add buttons to array
	AddButton(Button_PlayGame);
	AddButton(Button_QuitToDeskTop);

	//button on click callbacks
	Button_PlayGame->OnButtonSelected.BindDynamic(this, &ThisClass::PlayGameButtonAction);
	Button_PlayGame->Show();
	Button_QuitToDeskTop->OnButtonSelected.BindDynamic(this, &ThisClass::QuitButtonAction);
	Button_QuitToDeskTop->Show();
	
}

void UMainMenuScreen::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	//fade the start screen
	m_PreScreenOverlay->SetRenderOpacity(FMath::FInterpTo(m_PreScreenOverlay->GetRenderOpacity(),
	                                                      m_onPreTittleScreen ? 1 : 0, InDeltaTime, 10));
}

void UMainMenuScreen::NativeOnActivated()
{
	Super::NativeOnActivated();
	m_PreScreenOverlay->SetRenderOpacity(m_onPreTittleScreen ? 1 : 0);
}

void UMainMenuScreen::HandleReturnAction()
{
	if (!m_BaseWidget->IsUpperMostWidget(this))
	{
		return;
	}

	if (!m_onPreTittleScreen)
	{
		m_onPreTittleScreen = true;
		return;
	}

	// Super::HandleReturnAction();

	// if (m_BaseWidget != nullptr)
	// {
		// m_BaseWidget->PushWidget(QuitToDesktopWidgetClass);
	// }
}

void UMainMenuScreen::HandleSelectAction()
{
	if (!m_BaseWidget->IsUpperMostWidget(this))
	{
		return;
	}
	//remove pre main menu screen
	if (m_onPreTittleScreen)
	{
		m_onPreTittleScreen = false;
		return;
	}

	Super::HandleSelectAction();
}

void UMainMenuScreen::HandleNextAction()
{
	if (m_onPreTittleScreen)
	{
		return;
	}
	Super::HandleNextAction();
}

void UMainMenuScreen::HandlePrevAction()
{
	if (m_onPreTittleScreen)
	{
		return;
	}

	Super::HandlePrevAction();
}

void UMainMenuScreen::PlayGameButtonAction()
{
	//load level if it exists

	GameUtils::LoadLevel(GetWorld());
}


// void UMainMenuScreen::SettingsButtonAction()
// {
// 	if (m_BaseWidget != nullptr)
// 	{
// 		m_BaseWidget->PushWidget(SettingsWidgetClass);
// 	}
// 	// call change screen event
// 	OnChangeScreen();
// }

// void UMainMenuScreen::SaveDataButtonAction()
// {
// 	if (m_BaseWidget != nullptr)
// 	{
// 		m_BaseWidget->PushWidget(ManageSaveDataWidgetClass);
// 	}
// 	// call change screen event
// 	OnChangeScreen();
// }

// void UMainMenuScreen::CreditsButtonAction()
// {
// 	if (m_BaseWidget != nullptr)
// 	{
// 		m_BaseWidget->PushWidget(CreditsWidgetClass);
// 	}
// 	// call change screen event
// 	OnChangeScreen();
// }

void UMainMenuScreen::QuitButtonAction()
{
	// if (m_BaseWidget != nullptr)
	// {
	// 	m_BaseWidget->PushWidget(QuitToDesktopWidgetClass);
	// }
}
