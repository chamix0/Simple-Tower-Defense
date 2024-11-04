// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Components/TextBlock.h"
#include "Managers/TowerWorldManager.h"
#include "Utils/StopWatch.h"
#include "CommonActionWidget.h"

#include "SimpleTextWidget.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLETOWERDEFENSE_API USimpleTextWidget : public UCommonUserWidget, public Observer
{
	GENERATED_BODY()

	//text block to write on
	UPROPERTY(meta = (BindWidget))
	UTextBlock* m_TextBlock = nullptr;

	//parameters
	//time until next update
	UPROPERTY(EditAnywhere)
	float timePerCharacter = 0.5f;

	//number of character to writte per update
	UPROPERTY(EditAnywhere, meta=(UIMin=0, UIMax=10))
	int charactersPerUpdate = 2;

	//values
	int currentIndex = 0;
	FString currentText = "";
	FString textBuffer;
	FStopWatch StopWatch;
	bool m_highlighted = false;
	

	//colors
	UPROPERTY(EditAnywhere)
	FLinearColor m_dayColor = FColor::White;
	UPROPERTY(EditAnywhere)
	FLinearColor m_nightColor = FColor::Black;
	FLinearColor m_currentColor;
	FLinearColor m_targetColor;


	//tower world entity
	UPROPERTY()
	UTowerWorldManager* m_TowerWorldManager = nullptr;

public:
	/// show the text
	void Show();
	/// Hide the text
	void Hide();
	/// start writting a text
	/// @param body text to write
	/// @param style style to use for all the text
	void SetText(FText body, bool highlighted = false);
	/// Write a text directly
	/// @param body text to write
	/// @param style style to use for all the text
	void SetTextDirectly(FText body, bool highlighted = false);
	/// checck if is writting a text
	/// @return 
	bool IsWrittingText();
	/// end the writting animation
	void FastForwardText();
	//set time per character
	void SetTimePerCharacter(float value);
	//set charcters per update
	void SetCharctersPerUpdate(int value);
	void SetHighlighted(bool value);
	void SetDayColor(FLinearColor Color);
	void SetNightColor(FLinearColor Color);

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	void WriteText();
	virtual void update(const UTowerEvent event) override;
};
