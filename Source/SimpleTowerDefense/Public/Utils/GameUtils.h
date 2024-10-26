#pragma once

namespace GameUtils
{
	void QuitGame(UWorld* world, APlayerController* PlayerController);
	void LoadMainMenu(UWorld* world);
	void LoadLevel(UWorld* world);
	void Vibrate(UWorld* world, UForceFeedbackEffect* effect);
}
