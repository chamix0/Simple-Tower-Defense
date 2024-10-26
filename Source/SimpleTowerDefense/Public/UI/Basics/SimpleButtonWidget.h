// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "SimpleTextWidget.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "SimpleButtonWidget.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_DELEGATE(FOnButtonSelected);

UCLASS()
class SIMPLETOWERDEFENSE_API USimpleButtonWidget : public UCommonUserWidget
{
	GENERATED_BODY()
	
	//sound to play
	UPROPERTY()
	UAudioComponent* audioComponent=nullptr;
	UPROPERTY(EditAnywhere)
	USoundBase* buttonSelectedAudio = nullptr;
	
	//default Text
	UPROPERTY(EditAnywhere)
	FText m_DefaultText;

	//button text
	UPROPERTY(meta = (BindWidget))
	USimpleTextWidget* m_Text = nullptr;

	//image
	UPROPERTY(meta = (BindWidget))
	UImage* m_background = nullptr;

	//associated input
	UPROPERTY(meta = (BindWidget))
	USizeBox* m_inputSizeBox = nullptr;

	//textures
	UPROPERTY(EditAnywhere)
	UTexture2D* m_normalTexture;
	UPROPERTY(EditAnywhere)
	UTexture2D* m_highlightTexture;

	//text styles
	UPROPERTY(EditAnywhere)
	FString m_normalStyle = "Default";
	UPROPERTY(EditAnywhere)
	FString m_highlightedStyle = "Default";
	UPROPERTY(EditAnywhere, meta=(UIMin=0, UIMax=1))
	float m_MaxAlpha = 1.f;

	//parameters
	float m_offset; //distance to move when shown

	UPROPERTY(EditAnywhere)
	bool m_showInputWhenHighlighted = true;

	//values
	bool m_visible = false; //the widget is being shown
	bool m_fading = false; //the widget is currently doing the fading animation
	FText m_currentText; //current text of the button



public:
	//action delegate
	FOnButtonSelected OnButtonSelected;
	

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativeOnInitialized() override;

public:
	/// show widget on viewport
	UFUNCTION(BlueprintCallable)
	void Show();

	///hide widget on viewport
	UFUNCTION(BlueprintCallable)
	void Hide();
	///hide widget on viewport
	UFUNCTION(BlueprintCallable)
	void Collapse();
	///hide widget on viewport
	void HideAnimation();
	///start fading out
	void FadeOut();

	/// text to show in button
	/// @param body
	void SetText(FText body, bool completed = false);

	/// set distance to move
	/// @param offset 
	void SetOffset(float offset);

	/// removes the text
	void ClearText();

	/// give the button default values
	void Reset();

	/// highlight or not the button
	/// @param highlighted 
	 void SetHighLight(bool highlighted);
	void SetNormalTextStyle(FString style);
	void SetHighlightTextStyle(FString style);
	void SetNormalBackground(UTexture2D* texture);
	void SetHighlightBackground(UTexture2D* texture);
	void SetMaxAlpha(float alpha);
	bool FinishedMoving();

	void PerformSelectAction();
	//Events
	UFUNCTION(BlueprintImplementableEvent)
	void OnButtonSelectedEvent();
private:
	/// fast forward text animation
	void FastForwardText();
	/// sets values for hightlight
	void SetButtonValuesforHighlight(ESlateVisibility HintVisibility, UTexture2D* texture);

};
