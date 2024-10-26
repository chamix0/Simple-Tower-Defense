// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "Widgets/CommonActivatableWidgetContainer.h"
#include "BaseWidget.generated.h"

class UHudWidget;
/**
 * 
 */
UCLASS()
class SIMPLETOWERDEFENSE_API UBaseWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()
	
	UPROPERTY(meta=(BindWidget))
	UCommonActivatableWidgetStack* m_baseStack;

	
public:
	/// Add widget to the stack
	/// @param widget UCommonActivatableWidget*
	UFUNCTION(BlueprintCallable)
	virtual UCommonActivatableWidget* PushWidget(TSubclassOf<UCommonActivatableWidget> widget);

	/// Remove a widget from the stack
	/// @param widget
	UFUNCTION(BlueprintCallable)
	virtual void RemoveWidget(UCommonActivatableWidget* widget);
	bool IsUpperMostWidget(UCommonActivatableWidget* widget);

	UHudWidget* GetHudWidget();
};
