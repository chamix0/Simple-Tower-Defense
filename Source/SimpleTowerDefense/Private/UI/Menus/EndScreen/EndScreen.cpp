// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menus/EndScreen/EndScreen.h"

#include "Kismet/GameplayStatics.h"
#include "UI/Basics/SimpleButtonWidget.h"
#include "Utils/GameUtils.h"

void UEndScreen::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	//add buttons to array
	AddButton(Button_PlayAgain);
	AddButton(Button_QuitToMenu);

	//button on click callbacks
	Button_PlayAgain->OnButtonSelected.BindDynamic(this, &ThisClass::PlayAgainButtonAction);
	Button_QuitToMenu->OnButtonSelected.BindDynamic(this, &ThisClass::QuitToMenuButtonAction);

	auxInputAction->OnInputMethodChanged.AddDynamic(this, &ThisClass::OnInputMethodChanged);
}

void UEndScreen::NativeOnActivated()
{
	Super::NativeOnActivated();
	m_towerWorldManger->SetPaused(true);
	m_DaysText->SetText(
		FText::FromString("You survived " + FString::FromInt(m_towerWorldManger->GetNumDays()) + " days"));
}

void UEndScreen::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}


void UEndScreen::PlayAgainButtonAction()
{
	m_towerWorldManger->SetPaused(false);
	GameUtils::LoadLevel(GetWorld());
}

void UEndScreen::HandleReturnAction()
{
}

void UEndScreen::QuitToMenuButtonAction()
{
	GameUtils::LoadMainMenu(GetWorld());
}

void UEndScreen::OnInputMethodChanged(bool usingGamepad)
{
	if (usingGamepad)
	{
		m_blockingScreen->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		m_blockingScreen->SetVisibility(ESlateVisibility::Collapsed);
	}
}
