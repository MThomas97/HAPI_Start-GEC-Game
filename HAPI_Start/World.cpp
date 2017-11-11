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

	if (!visual.CreateSprite("starBackground", "Data\\FullStarBackground.jpg"))
		return;

	if (!visual.CreateSprite("player", "Data\\player.png"))
		return;

	if (!visual.CreateSprite("horse", "Data\\HorseSpriteSheetWhite.png", numFramesX, numFramesY))
		return;

	while (HAPI.Update()) //Game loop
	{	//calls functions from classes

		const HAPI_TControllerData &controllerData = HAPI.GetControllerData(0);

		visual.ClearToColour(HAPI.GetScreenPointer(), width, height, HAPI_TColour(0, 0, 0));

		visual.RenderNoAlphaSprite("starBackground", ScrollPosX, ScrollPosY);
		visual.RenderNoAlphaSprite("starBackground", SecondScrollPosX, SecondScrollPosY);
		/*visual.RenderNoAlphaSprite("starBackground", 254, 256);
		visual.RenderNoAlphaSprite("starBackground", 254, 0);
		visual.RenderNoAlphaSprite("starBackground", 0, 256);
		visual.RenderNoAlphaSprite("starBackground", 508, 512);
		visual.RenderNoAlphaSprite("starBackground", 508, 0);
		visual.RenderNoAlphaSprite("starBackground", 0, 512);
		visual.RenderNoAlphaSprite("starBackground", 254, 512);
		visual.RenderNoAlphaSprite("starBackground", 508, 256);
		visual.RenderNoAlphaSprite("starBackground", 0, 768);
		visual.RenderNoAlphaSprite("starBackground", 254, 768);
		visual.RenderNoAlphaSprite("starBackground", 508, 768);*/
		//visual.RenderSprite("horse", 100, 100, curFrameX, curFrameY);
		visual.RenderSprite("player", playerPosX, playerPosY);
		int prevTime = HAPI.GetTime();
		
		int elapsedTime = HAPI.GetTime() - prevTime;

		prevTime = prevTime + elapsedTime;

		ScrollPosY += 1;
		SecondScrollPosY += 1;

		if(prevTime > 1000)
		{
			prevTime = elapsedTime;

			curFrameX += 1;
			elapsedTime = 0;

			if (curFrameY >= 2)
				curFrameY = 0;

			if (curFrameX > numFramesX)
			{
				curFrameX = 0;
				curFrameY += 1;
			}
		}

		//visual.ScrollingBackground(ScrollPosX, ScrollPosY, SecondScrollPosX, SecondScrollPosY); /////////GET WORKING

		if (ScrollPosY > visual.m_screenRect.bottom)
		{
			ScrollPosY = 0;
			SecondScrollPosY = -800;
		}
		

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