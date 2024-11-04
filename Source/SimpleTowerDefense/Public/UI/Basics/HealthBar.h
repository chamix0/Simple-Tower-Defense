// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Managers/TowerWorldManager.h"
#include "ObserverPattern/Observer.h"
#include "HealthBar.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLETOWERDEFENSE_API UHealthBar : public UUserWidget, public Observer
{
	GENERATED_BODY()

	UPROPERTY(meta=(BindWidget))
	UProgressBar* m_MainHealthBar = nullptr;

	//world manager
	UPROPERTY()
	UTowerWorldManager* m_towerWorldManager = nullptr;

	//colors
	UPROPERTY(EditAnywhere)
	FColor m_dayColor = FColor::White;
	UPROPERTY(EditAnywhere)
	FColor m_nightColor = FColor::Black;
	FLinearColor m_currentColor;
	FLinearColor m_targetColor;

	
public:
	void Show();
	void Hide();

	void SetValue(float currentHealth, float MaxHealth);
private:
	virtual void NativeOnInitialized() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void update(const UTowerEvent event) override;

};
