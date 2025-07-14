#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER

#include <algorithm>

#include "Play.h"

#include "MainGame.h"
#include "Constants.h"
#include "GameObjectType.h"
#include "Agent8.h"
#include "Fan.h"
#include "Tools.h"
#include "Coins.h"
#include "Lasers.h"
#include "DestroyObjects.h"
#include "PlayerControls.h"

// The entry point for a PlayBuffer program
void MainGameEntry(PLAY_IGNORE_COMMAND_LINE)
{
	Play::CreateManager(DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE);
	Play::CentreAllSpriteOrigins();
	Play::LoadBackground("Data\\Backgrounds\\background.png");
	Play::StartAudioLoop("music");
	Play::CreateGameObject(TYPE_AGENT8, { 115, 600 }, 50, "agent8");

	gameState = new GameState();

	playerControls = new PlayerControls(gameState);
	agent8 = new Agent8(gameState, playerControls);
	fan = new Fan();
	tools = new Tools(gameState); 
	coins = new Coins(gameState);
	lasers = new Lasers(gameState);
}

// Called by PlayBuffer every frame (60 times a second!)
bool MainGameUpdate(float elapsedTime)
{
	Play::DrawBackground();

	agent8->Update();
	fan->Update();
	tools->Update();
	coins->Update();
	lasers->Update();
	destroyObjects->UpdateDestroyed();

	Play::DrawFontText("32px", "ARROW KEYS TO MOVE UP AND DOWN AND SPACE TO FIRE", { DISPLAY_WIDTH / 2, 40 }, Play::CENTRE);
	Play::DrawFontText("72px", "SCORE: " + std::to_string(gameState->score), { DISPLAY_WIDTH / 2, DISPLAY_HEIGHT - 80 }, Play::CENTRE);

	agent8->Draw();
	fan->Draw();
	tools->Draw();
	coins->Draw();
	lasers->Draw();

	Play::PresentDrawingBuffer();

	return Play::KeyDown(KEY_ESCAPE);
}

int MainGameExit(void)
{
	Play::DestroyManager();
	return PLAY_OK;
}