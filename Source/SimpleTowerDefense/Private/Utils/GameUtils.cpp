#include "Utils/GameUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

void GameUtils::QuitGame(UWorld* world, APlayerController* PlayerController)
{
	TEnumAsByte<EQuitPreference::Type> QuitPreference = EQuitPreference::Quit;
	UKismetSystemLibrary::QuitGame(world, PlayerController, QuitPreference, true);
}

void GameUtils::LoadMainMenu(UWorld* world)
{
	UGameplayStatics::OpenLevel(world, "MAP_MainMenu");
}


void GameUtils::LoadLevel(UWorld* world)
{
	UGameplayStatics::OpenLevel(world, "MAP_Game");
}

void GameUtils::Vibrate(UWorld* world, UForceFeedbackEffect* effect)
{
	//small vibration
	// if (UParanoiaUserGameSettings::GetUParanoiaUserGameSettings()->GetVibrationEnabled())
	// {
	//set parameters
	FForceFeedbackParameters Parameters;
	Parameters.bPlayWhilePaused = true;
	Parameters.bLooping = false;
	Parameters.bIgnoreTimeDilation = true;
	//play vibration
	UGameplayStatics::GetPlayerController(world, 0)->ClientPlayForceFeedback(effect, Parameters);
	// }
}
