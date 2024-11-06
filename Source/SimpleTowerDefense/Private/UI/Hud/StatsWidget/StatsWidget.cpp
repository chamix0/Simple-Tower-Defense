// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Hud/StatsWidget/StatsWidget.h"

#include "Game_Entities/Tower/Tower.h"

void UStatsWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	m_textWidget->SetColorAndOpacity(m_currentColor);
}

FString UStatsWidget::GetStatsText()
{
	FString cad;

	//Health
	cad.Append(
		"Health: " + FString::FromInt(m_TowerWorldManager->GetTower()->GetHealth()) + "/" + FString::FromInt(
			m_TowerWorldManager->GetMaxTowerHealth()) + "\n");
	//health regen
	cad.Append(
		"Health regen: " + FString::FromInt(m_TowerWorldManager->GetRegenPerDay()) + " per day\n");
	//life steal chance
	cad.Append(
		"life steal chance: " + FString::FromInt(m_TowerWorldManager->GetLifeStealChance()) + "%\n");
	//life steal amount
	cad.Append(
		"life steal amount: " + FString::FromInt(m_TowerWorldManager->GetLifeStealAmount()) + "\n");
	//range
	cad.Append(
		"Range: " + FString::SanitizeFloat(m_TowerWorldManager->GetTowerRange(), 2) + "\n");
	//shoots per secons
	cad.Append(
		"Shoots per second: " + FString::SanitizeFloat(m_TowerWorldManager->GetShootsPerSecond(), 2) + "\n");
	//base damage
	cad.Append(
		"Base damage: " + FString::SanitizeFloat(m_TowerWorldManager->GetDamage(), 2) + "\n");
	//bullet speed
	cad.Append(
		"Bullets speed: " + FString::SanitizeFloat(m_TowerWorldManager->GetBulletsSpeed(), 2) + "\n");
	//critical chance
	cad.Append(
		"critical chance: " + FString::SanitizeFloat(m_TowerWorldManager->GetCriticalChance(), 2) + "%\n");
	//critical multiplier
	cad.Append(
		"critical multiplier: " + FString::SanitizeFloat(m_TowerWorldManager->GetCriticalMultiplier(), 2) + "\n");
	//simultaneous targets
	cad.Append(
	"targets: " + FString::FromInt(m_TowerWorldManager->GetTower()->GetNumTargets()) + "\n");
	//daily points
	cad.Append(
	"daily points: " + FString::FromInt(m_TowerWorldManager->GetDailyPoints()) + "\n");
	//kill point multiplier
	cad.Append(
	"kill point multiplier: " + FString::SanitizeFloat(m_TowerWorldManager->GetKillPointMultiplier(),2) + "\n");
	//max game speed
	cad.Append(
	"Max game speed: " + FString::SanitizeFloat(m_TowerWorldManager->GetMaxTimeScale(),2) + "\n");
	
	return cad;
}

void UStatsWidget::update(const UTowerEvent event)
{
	Super::update(event);
	m_textWidget->SetText(FText::FromString(GetStatsText()));
}
