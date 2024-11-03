// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menus/QuitToDesktop/QuitToDesktopScreen.h"
// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menus/QuitToDesktop/QuitToDesktopScreen.h"

#include "UI/Basics/SimpleButtonWidget.h"
#include "Utils/GameUtils.h"
#include "Utils/UiUtils.h"

void UQuitToDesktopScreen::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	//add buttons to array
	AddButton(Button_Cancel);
	AddButton(Button_QuitToDesktop);

	//button on click callbacks
	Button_Cancel->OnButtonSelected.BindDynamic(this, &ThisClass::CancelButtonAction);
	Button_QuitToDesktop->OnButtonSelected.BindDynamic(this, &ThisClass::QuitToDesktopButtonAction);
}

void UQuitToDesktopScreen::NativeOnActivated()
{
	Super::NativeOnActivated();
}

void UQuitToDesktopScreen::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}


void UQuitToDesktopScreen::CancelButtonAction()
{
	HandleReturnAction();
}

void UQuitToDesktopScreen::HandleReturnAction()
{
	Super::HandleReturnAction();
}

void UQuitToDesktopScreen::QuitToDesktopButtonAction()
{
	GameUtils::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController());
}
