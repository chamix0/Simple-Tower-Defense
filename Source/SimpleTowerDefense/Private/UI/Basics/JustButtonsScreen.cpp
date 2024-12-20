// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Basics/JustButtonsScreen.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "UI/BaseWidget.h"
#include "UI/Basics/SimpleButtonWidget.h"
#include "Utils/UiUtils.h"


void UJustButtonsScreen::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	m_towerWorldManger = GetWorld()->GetSubsystem<UTowerWorldManager>();
	//get hud
	TArray<UUserWidget*> widgetsfound;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), widgetsfound, UBaseWidget::StaticClass());
	if (GEngine && widgetsfound.Num() >= 1)
	{
		m_BaseWidget = Cast<UBaseWidget>(widgetsfound[0]);
	}

	//reset buttons
	buttonIndex = -1;
	UpdateSelectedButton(buttonIndex);

	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameOnly());

	//input changed
	m_ActionWidget->OnInputMethodChanged.AddDynamic(this, &ThisClass::InputChanged);
	m_mouseBlockingImage->SetVisibility(ESlateVisibility::Collapsed);
}

void UJustButtonsScreen::NativeOnActivated()
{
	Super::NativeOnActivated();

	//make it visible
	SetVisibility(ESlateVisibility::Visible);

	//show buttons
	for (USimpleButtonWidget* button : m_buttons)
	{
		button->Show();
	}

	//start with the first button highlighted
	UpdateSelectedButton(buttonIndex);

	//call the activated event
	OnWidgetActivated();
}

void UJustButtonsScreen::NativeOnDeactivated()
{
	Super::NativeOnDeactivated();
	//make it inVisible
	SetVisibility(ESlateVisibility::Collapsed);
	//set button to -1
	buttonIndex = -1;
	UpdateSelectedButton(buttonIndex);
}

void UJustButtonsScreen::AddButton(USimpleButtonWidget* button)
{
	//make it non interactable with mouse
	button->SetVisibility(ESlateVisibility::HitTestInvisible);

	//add button to the list
	m_buttons.Push(button);
}

void UJustButtonsScreen::DeleteButton(int index)
{
	if (index >= m_buttons.Num())
	{
		return;
	}

	//button reference
	USimpleButtonWidget* button = m_buttons[index];

	//remove from the array
	m_buttons.RemoveAt(index);

	//delete the button
	button->RemoveFromParent();
	button = nullptr;
}

void UJustButtonsScreen::DeleteAllButtons()
{
	while (!m_buttons.IsEmpty())
	{
		DeleteButton(0);
	}
}

void UJustButtonsScreen::InputChanged(bool isGamepad)
{
	//set button to -1
	buttonIndex = -1;
	UpdateSelectedButton(buttonIndex);
	
	if (isGamepad)
	{
		m_mouseBlockingImage->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		m_mouseBlockingImage->SetVisibility(ESlateVisibility::Collapsed);
	}
}


void UJustButtonsScreen::UpdateSelectedButton(int index)
{
	UiUtils::UpdateSelectedSimpleButton(index, m_buttons);
}

void UJustButtonsScreen::HandlePrevAction()
{
	if (!m_BaseWidget->IsUpperMostWidget(this) && GetVisibility() != ESlateVisibility::Visible)
	{
		return;
	}

	//call prev button event
	if (buttonIndex > 0)
	{
		OnPrevButtonSelected();
	}


	buttonIndex = FMath::Max(buttonIndex - 1, 0);
	UpdateSelectedButton(buttonIndex);
}

void UJustButtonsScreen::HandleNextAction()
{
	if (!m_BaseWidget->IsUpperMostWidget(this) && GetVisibility() != ESlateVisibility::Visible)
	{
		return;
	}

	//call next button event
	if (buttonIndex < m_buttons.Num() - 1)
	{
		OnNextButtonSelected();
	}

	buttonIndex = FMath::Min(buttonIndex + 1, m_buttons.Num() - 1);
	UpdateSelectedButton(buttonIndex);
}

void UJustButtonsScreen::HandleSelectAction()
{
	if (!m_BaseWidget->IsUpperMostWidget(this) && GetVisibility() != ESlateVisibility::Visible)
	{
		return;
	}
	//no button selected
	if (buttonIndex < 0)
	{
		return;
	}

	if (!m_buttons.IsEmpty() && buttonIndex < m_buttons.Num())
	{
		m_buttons[buttonIndex]->PerformSelectAction();
	}
}

void UJustButtonsScreen::HandleReturnAction()
{
	bool isUpperMost = m_BaseWidget->IsUpperMostWidget(this);
	bool isVisible = GetVisibility() == ESlateVisibility::Visible;
	if (!isUpperMost || !isVisible)
	{
		return;
	}

	if (m_BaseWidget->IsUpperMostWidget(this))
	{
		DeactivateWidget();
	}
}
