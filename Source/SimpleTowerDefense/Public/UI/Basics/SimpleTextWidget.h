// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Components/TextBlock.h"
#include "Utils/StopWatch.h"
#include "SimpleTextWidget.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLETOWERDEFENSE_API USimpleTextWidget : public UCommonUserWidget
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

public:
	/// show the text
	void Show();
	/// Hide the text
	void Hide();
	/// start writting a text
	/// @param body text to write
	/// @param style style to use for all the text
	void SetText(FText body);
	/// Write a text directly
	/// @param body text to write
	/// @param style style to use for all the text
	void SetTextDirectly(FText body);
	/// checck if is writting a text
	/// @return 
	bool IsWrittingText();
	/// end the writting animation
	void FastForwardText();
	//set time per character
	void SetTimePerCharacter(float value);
	//set charcters per update
	void SetCharctersPerUpdate(int value);

	UFUNCTION(BlueprintImplementableEvent)
	void OnTextStartsWritting();
	UFUNCTION(BlueprintImplementableEvent)
	void OnTextEndsWritting();
	UFUNCTION(BlueprintImplementableEvent)
	void OnTextFastForward();

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	void WriteText();
};
