// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ObserverPattern/Observer.h"
#include "DayNightWidget.generated.h"

class UTowerWorldManager;
/**
 * 
 */
UCLASS()
class SIMPLETOWERDEFENSE_API UDayNightWidget : public UUserWidget, public Observer
{
	GENERATED_BODY()

protected:
	//tower world entity
	UPROPERTY()
	UTowerWorldManager* m_TowerWorldManager = nullptr;
	//colors
	UPROPERTY(EditAnywhere)
	FLinearColor m_dayColor = FColor::White;
	UPROPERTY(EditAnywhere)
	FLinearColor m_nightColor = FColor::Black;
	FLinearColor m_currentColor;
	FLinearColor m_currentOppositeColor;
	FLinearColor m_targetColor;
	FLinearColor m_targetOppositeColor;

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativeOnInitialized() override;
	virtual void update(const UTowerEvent event) override;

public:
	/// show widget on viewport
	UFUNCTION()
	virtual void Show();
	///hide widget on viewport
	UFUNCTION()
	virtual void Hide();

	void SetDayColor(FLinearColor Color);
	void SetNightColor(FLinearColor Color);

};
