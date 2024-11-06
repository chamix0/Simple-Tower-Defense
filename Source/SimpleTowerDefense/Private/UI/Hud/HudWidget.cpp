// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Hud/HudWidget.h"

#include "Game_Entities/Tower/Tower.h"
#include "Kismet/GameplayStatics.h"
#include "Settings/GameSettings.h"
#include "UI/GameBaseWidget.h"
#include "Utils/UiUtils.h"

void UHudWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	m_towerWorldManager = GetWorld()->GetSubsystem<UTowerWorldManager>();
	m_daysCount->SetText(FText::FromString("Days passed: 0"));
	m_pointsCount->SetText(FText::FromString("Points: 0"));
	m_pauseButton->SetText(FText::FromString("UNPAUSED"), true);
	m_ShootingPolicyButton->SetText(FText::FromString("Shooting\npolicy\nclosest"));
	m_GameSpeedButton->SetText(FText::FromString("GAME SPEED\n1"), true);

	//assign buttons 
	AddButton(m_healthBranchButton);
	AddButton(m_DamageBranchButton);
	AddButton(m_PointsBranchButton);

	//assign button actions
	m_healthBranchButton->OnButtonSelected.BindDynamic(this, &ThisClass::HealthBranchAction);
	m_DamageBranchButton->OnButtonSelected.BindDynamic(this, &ThisClass::DamageBranchAction);
	m_PointsBranchButton->OnButtonSelected.BindDynamic(this, &ThisClass::PointsBranchAction);

	//bind action to button
	m_pauseButton->OnButtonSelected.BindDynamic(this, &ThisClass::PauseAction);
	m_GameSpeedButton->OnButtonSelected.BindDynamic(this, &ThisClass::GameSpeedAction);
	m_ShootingPolicyButton->OnButtonSelected.BindDynamic(this, &ThisClass::ShootingPolicyAction);

	//hide branches
	m_healthBranch->Hide();
	m_damageBranch->Hide();
	m_pointsCount->Hide();
	//hide exit hint
	m_exitInputHint->SetRenderOpacity(0);
}

void UHudWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	//upper and lower bars
	M_UpperBox->SetRenderTranslation(FVector2D(0, FMath::FInterpTo(M_UpperBox->GetRenderTransform().Translation.Y,
	                                                               !m_upperBarVisible * upperBarTarget, InDeltaTime,
	                                                               GetDefault<UGameSettings>()->ColorChangeSpeed)));
	M_LowerBox->SetRenderTranslation(FVector2D(0, FMath::FInterpTo(M_LowerBox->GetRenderTransform().Translation.Y,
	                                                               !m_lowerBarVisible * lowerBarTarget, InDeltaTime,
	                                                               GetDefault<UGameSettings>()->ColorChangeSpeed)));
	m_HideShowUpperInputHint->SetRenderTransformAngle(FMath::FInterpTo(
		m_HideShowUpperInputHint->GetRenderTransformAngle(), m_upperBarVisible ? 180 : 0, InDeltaTime,
		GetDefault<UGameSettings>()->ColorChangeSpeed));
	m_HideShowLowerInputHint->SetRenderTransformAngle(FMath::FInterpTo(
		m_HideShowLowerInputHint->GetRenderTransformAngle(), m_lowerBarVisible ? 180 : 0, InDeltaTime,
		GetDefault<UGameSettings>()->ColorChangeSpeed));

	//exit hint
	m_exitInputHint->SetRenderOpacity(FMath::FInterpTo(m_exitInputHint->GetRenderOpacity(),
	                                                   m_towerWorldManager->GetPaused(), InDeltaTime,
	                                                   GetDefault<UGameSettings>()->ColorChangeSpeed));
}

void UHudWidget::UpdateHealth(float currentHealth, float maxHealth)
{
	m_healthBar->SetValue(currentHealth, maxHealth);
}

void UHudWidget::SetDays(int num)
{
	m_daysCount->SetText(FText::FromString("Days passed: " + FString::FromInt(num)));
}

void UHudWidget::SetPoints(int num)
{
	m_pointsCount->SetText(FText::FromString("Points: " + FString::FromInt(num)));
}

void UHudWidget::PauseAction()
{
	if (m_towerWorldManager->GetTower()->GetGameBaseWidget()->
	                         IsUpperMostWidget(this))
	{
		m_towerWorldManager->SetPaused(!m_towerWorldManager->GetPaused());

		m_pauseButton->SetText(m_towerWorldManager->GetPaused()
			                       ? FText::FromString("PAUSED")
			                       : FText::FromString("UNPAUSED"), true);
		//show exit to main menu hint
	}
}

void UHudWidget::GameSpeedAction()
{
	//update game speed
	float timeScale = UGameplayStatics::GetGlobalTimeDilation(GetWorld());
	timeScale = timeScale + GetDefault<UGameSettings>()->GameSpeedIncrement > m_towerWorldManager->GetMaxTimeScale()
		            ? 0.5f
		            : timeScale + GetDefault<UGameSettings>()->GameSpeedIncrement;
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), timeScale);
	//update text
	m_GameSpeedButton->SetText(FText::FromString("GAME SPEED\n" + FString::SanitizeFloat(timeScale, 2)));
}

void UHudWidget::ShootingPolicyAction()
{
	int currentShootingPolicy = static_cast<int>(m_towerWorldManager->GetTower()->GetCurrentShootingPolicy());
	m_towerWorldManager->GetTower()->SetShootingPolicy(
		static_cast<UShootingPolicy>((currentShootingPolicy + 1) % static_cast<int>(
			UShootingPolicy::SHOOTINGPOLICY_COUNT)));

	//text
	if (m_towerWorldManager->GetTower()->GetCurrentShootingPolicy() == UShootingPolicy::WEAKEST)
	{
		m_ShootingPolicyButton->SetText(FText::FromString("Shooting\npolicy\nWeakest"));
	}
	else if (m_towerWorldManager->GetTower()->GetCurrentShootingPolicy() == UShootingPolicy::STRONGUEST)
	{
		m_ShootingPolicyButton->SetText(FText::FromString("Shooting\npolicy\nStrongest"));
	}
	else if (m_towerWorldManager->GetTower()->GetCurrentShootingPolicy() == UShootingPolicy::FURTHEST)
	{
		m_ShootingPolicyButton->SetText(FText::FromString("Shooting\npolicy\nFURTHEST"));
	}
	else if (m_towerWorldManager->GetTower()->GetCurrentShootingPolicy() == UShootingPolicy::CLOSEST)
	{
		m_ShootingPolicyButton->SetText(FText::FromString("Shooting\npolicy\nCLOSEST"));
	}
}

void UHudWidget::ShowLowerBar()
{
	m_lowerBarVisible = true;
}

void UHudWidget::HideLowerBar()
{
	m_lowerBarVisible = false;
}

void UHudWidget::ShowUpperBar()
{
	m_upperBarVisible = true;
}

void UHudWidget::HideUpperBar()
{
	m_lowerBarVisible = false;
}

void UHudWidget::ShowHideUpperBar()
{
	if (m_towerWorldManager->GetTower()->GetGameBaseWidget()->
	                         IsUpperMostWidget(this))
	{
		m_upperBarVisible = !m_upperBarVisible;
	}
}

void UHudWidget::ShowHideLowerBar()
{
	if (m_towerWorldManager->GetTower()->GetGameBaseWidget()->
	                         IsUpperMostWidget(this))
	{
		m_lowerBarVisible = !m_lowerBarVisible;
	}
}

void UHudWidget::ExitToMainMenuAction()
{
	if (m_towerWorldManager->GetPaused() && m_towerWorldManager->GetTower()->GetGameBaseWidget()->
	                                                             IsUpperMostWidget(this))
	{
		m_towerWorldManager->GetTower()->GetGameBaseWidget()->PushWidget(QuitToMenuWidgetClass);
	}
}

void UHudWidget::HandleReturnAction()
{
}

void UHudWidget::HandleNextAction()
{
	Super::HandleNextAction();
	HandleSelectAction();
}

void UHudWidget::HandlePrevAction()
{
	Super::HandlePrevAction();
	HandleSelectAction();
}

void UHudWidget::HandleRightAction()
{
	if (m_lowerBarVisible && m_towerWorldManager->GetTower()->GetGameBaseWidget()->
	                                              IsUpperMostWidget(this))
	{
		if (buttonIndex == UiUtils::FindButtonIndex(m_healthBranchButton, m_buttons))
		{
			m_healthBranch->HandlePrevAction();
		}
		else if (buttonIndex == UiUtils::FindButtonIndex(m_DamageBranchButton, m_buttons))
		{
			m_damageBranch->HandlePrevAction();
		}
		else if (buttonIndex == UiUtils::FindButtonIndex(m_PointsBranchButton, m_buttons))
		{
			m_PointsBranch->HandlePrevAction();
		}
	}
}

void UHudWidget::HandleLeftAction()
{
	if (m_lowerBarVisible && m_towerWorldManager->GetTower()->GetGameBaseWidget()->
	                                              IsUpperMostWidget(this))
	{
		if (buttonIndex == UiUtils::FindButtonIndex(m_healthBranchButton, m_buttons))
		{
			m_healthBranch->HandleNextAction();
		}
		else if (buttonIndex == UiUtils::FindButtonIndex(m_DamageBranchButton, m_buttons))
		{
			m_damageBranch->HandleNextAction();
		}
		else if (buttonIndex == UiUtils::FindButtonIndex(m_PointsBranchButton, m_buttons))
		{
			m_PointsBranch->HandleNextAction();
		}
	}
}

void UHudWidget::HandleConfirmAction()
{
	if (m_lowerBarVisible && m_towerWorldManager->GetTower()->GetGameBaseWidget()->
	                                              IsUpperMostWidget(this))
	{
		if (buttonIndex == UiUtils::FindButtonIndex(m_healthBranchButton, m_buttons))
		{
			m_healthBranch->HandleSelectAction();
		}
		else if (buttonIndex == UiUtils::FindButtonIndex(m_DamageBranchButton, m_buttons))
		{
			m_damageBranch->HandleSelectAction();
		}
		else if (buttonIndex == UiUtils::FindButtonIndex(m_PointsBranchButton, m_buttons))
		{
			m_PointsBranch->HandleSelectAction();
		}
	}
}


void UHudWidget::HealthBranchAction()
{
	m_healthBranch->Show();
	m_damageBranch->Hide();
	m_PointsBranch->Hide();

	ShowLowerBar();
}

void UHudWidget::DamageBranchAction()
{
	m_healthBranch->Hide();
	m_damageBranch->Show();
	m_PointsBranch->Hide();
	ShowLowerBar();
}

void UHudWidget::PointsBranchAction()
{
	m_healthBranch->Hide();
	m_damageBranch->Hide();
	m_PointsBranch->Show();
	ShowLowerBar();
}

void UHudWidget::PushNotification(FString textToDisplay, float time)
{
	m_notificationsWidget->PushText(textToDisplay, time);
}
