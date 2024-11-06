// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "Branches/HealthUpgradesWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/Image.h"
#include "Components/ScaleBox.h"
#include "Notifications/HudNotificationsWidget.h"
#include "UI/Basics/DayNightWidget.h"
#include "UI/Basics/HealthBar.h"
#include "UI/Basics/SimpleBackground.h"
#include "UI/Basics/SimpleButtonWidget.h"
#include "UI/Basics/SimpleTextWidget.h"
#include "UI/Menus/QuitToMenu/QuitToMenuScreen.h"
#include "HudWidget.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLETOWERDEFENSE_API UHudWidget : public UJustButtonsScreen
{
	GENERATED_BODY()
	//quit to menu screen
	UPROPERTY(EditAnywhere, meta=(DisplayName = "Widget quit to menu class"))
	TSubclassOf<UQuitToMenuScreen> QuitToMenuWidgetClass;

	//managers
	UPROPERTY()
	UTowerWorldManager* m_towerWorldManager = nullptr;

	//buttons
	UPROPERTY(meta=(BindWidget))
	USimpleButtonWidget* m_pauseButton = nullptr;
	UPROPERTY(meta=(BindWidget))
	USimpleButtonWidget* m_ShootingPolicyButton = nullptr;

	//branch buttons
	UPROPERTY(meta=(BindWidget))
	USimpleButtonWidget* m_healthBranchButton = nullptr;
	UPROPERTY(meta=(BindWidget))
	USimpleButtonWidget* m_DamageBranchButton = nullptr;
	UPROPERTY(meta=(BindWidget))
	USimpleButtonWidget* m_PointsBranchButton = nullptr;

	//branch widgets
	UPROPERTY(meta=(BindWidget))
	UHealthUpgradesWidget* m_healthBranch = nullptr;
	// UPROPERTY(meta=(BindWidget))
	// UHealthUpgradesWidget* m_healthBranch = nullptr;
	// UPROPERTY(meta=(BindWidget))
	// UHealthUpgradesWidget* m_healthBranch = nullptr;

	//indicators
	UPROPERTY(meta=(BindWidget))
	UHealthBar* m_healthBar = nullptr;
	UPROPERTY(meta=(BindWidget))
	USimpleTextWidget* m_daysCount = nullptr;
	UPROPERTY(meta=(BindWidget))
	USimpleTextWidget* m_pointsCount = nullptr;
	//notifications
	UPROPERTY(meta=(BindWidget))
	UHudNotificationsWidget* m_notificationsWidget = nullptr;
	
	//hints
	UPROPERTY(meta=(BindWidget))
	UHorizontalBox* m_exitInputHint = nullptr;
	UPROPERTY(meta=(BindWidget))
	USizeBox* m_HideShowUpperInputHint = nullptr;
	UPROPERTY(meta=(BindWidget))
	USizeBox* m_HideShowLowerInputHint = nullptr;

	UPROPERTY(meta=(BindWidget))
	USimpleBackground* m_UpperBarBackground = nullptr;
	UPROPERTY(meta=(BindWidget))
	USizeBox* M_UpperBox = nullptr;
	UPROPERTY(meta=(BindWidget))
	USizeBox* M_LowerBox = nullptr;

	//values
	UPROPERTY(EditAnywhere)
	float upperBarTarget = 0;
	bool m_upperBarVisible = true;
	UPROPERTY(EditAnywhere)
	float lowerBarTarget = 0;
	bool m_lowerBarVisible = false;

public:
	virtual void NativeOnInitialized() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	void UpdateHealth(float currentHealth, float maxHealth);
	void SetDays(int num);
	void SetPoints(int num);
	UFUNCTION(BlueprintCallable)
	void PauseAction();
	UFUNCTION(BlueprintCallable)
	void ShootingPolicyAction();
	/*show and hide bars*/
	void ShowLowerBar();
	void HideLowerBar();
	void ShowUpperBar();
	void HideUpperBar();
	UFUNCTION(BlueprintCallable)
	void ShowHideUpperBar();
	UFUNCTION(BlueprintCallable)
	void ShowHideLowerBar();
	UFUNCTION(BlueprintCallable)
	void ExitToMainMenuAction();

	//override with nothing so it doesnt affect
	virtual void HandleReturnAction() override;
	virtual void HandleNextAction() override;
	virtual void HandlePrevAction() override;
	UFUNCTION(BlueprintCallable)
	void HandleRightAction();
	UFUNCTION(BlueprintCallable)
	void HandleLeftAction();
	UFUNCTION(BlueprintCallable)
	void HandleConfirmAction();
	//branch action
	UFUNCTION()
	void HealthBranchAction();
	UFUNCTION()
	void DamageBranchAction();
	UFUNCTION()
	void PointsBranchAction();
	UFUNCTION(BlueprintCallable)
	void PushNotification(FString textToDisplay, float time);
};
