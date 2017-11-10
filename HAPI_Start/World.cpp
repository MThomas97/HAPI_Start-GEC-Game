#include "World.h"
#include "Visualisation.h"
#include <HAPI_lib.h>

#if defined(DEBUG) | defined(_DEBUG)
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK,__FILE__, __LINE__)
#endif

// HAPI itself is wrapped in the HAPISPACE namespace
using namespace HAPISPACE;

void World::Update(int width, int height, std::string name)
{
	Visualisation visual;

	if (!visual.initialise(width, height, name))
		return;

	//Sets the FPS counter on screen
	HAPI.SetShowFPS(true, 0, 0, HAPI_TColour::GREEN);
	const HAPI_TKeyboardData &keyData = HAPI.GetKeyboardData();

	if (!visual.CreateSprite("starBackground", "Data\\starBackground.png", 1))
		return;

	if (!visual.CreateSprite("player", "Data\\HorseSpriteSheetWhite.png", numFrames))
		return;

	while (HAPI.Update()) //Game loop
	{	//calls functions from classes

		const HAPI_TControllerData &controllerData = HAPI.GetControllerData(0);

		visual.ClearToColour(HAPI.GetScreenPointer(), width, height, HAPI_TColour(0, 0, 0));

		visual.RenderNoAlphaSprite("starBackground", 0, 0);
		visual.RenderNoAlphaSprite("starBackground", 254, 256);
		visual.RenderNoAlphaSprite("starBackground", 254, 0);
		visual.RenderNoAlphaSprite("starBackground", 0, 256);
		visual.RenderNoAlphaSprite("starBackground", 508, 512);
		visual.RenderNoAlphaSprite("starBackground", 508, 0);
		visual.RenderNoAlphaSprite("starBackground", 0, 512);
		visual.RenderNoAlphaSprite("starBackground", 254, 512);
		visual.RenderNoAlphaSprite("starBackground", 508, 256);
		visual.RenderNoAlphaSprite("starBackground", 0, 768);
		visual.RenderNoAlphaSprite("starBackground", 254, 768);
		visual.RenderNoAlphaSprite("starBackground", 508, 768);
		visual.RenderSprite("player", playerPosX, playerPosY, ChessFrame);

		if (ChessFrame > MaxFrame)
			ChessFrame = 0;

		ChessFrame += 1;

		//Moves sprite with WASD keys
		if (keyData.scanCode['W'])
			playerPosY--;

		if (keyData.scanCode['S'])
			playerPosY++;

		if (keyData.scanCode['A'])
			playerPosX--;

		if (keyData.scanCode['D'])
			playerPosX++;

		if (playerPosY < height - 200 && playerPosX < width - 200 && playerPosY > 200 && playerPosX > 200)
		{
			HAPI.SetControllerRumble(0, 40000, 40000);
		}
		else
		{
			HAPI.SetControllerRumble(0, 0, 0);
		}

		if (controllerData.isAttached)
		{
			//Gets the values of left thumb x, y and deadzone
			int LeftThumbX = controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X];
			int LeftThumbY = controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y];
			int Deadzone = controllerData.analogueButtons[HK_GAMEPAD_LEFT_THUMB_DEADZONE];

			if (Deadzone + 7849 < LeftThumbX)
				playerPosX++;

			if (Deadzone + 7849 < LeftThumbY)
				playerPosY--;

			if (Deadzone - 7849 > LeftThumbX)
				playerPosX--;

			if (Deadzone - 7849 > LeftThumbY)
				playerPosY++;
		}
	}
}