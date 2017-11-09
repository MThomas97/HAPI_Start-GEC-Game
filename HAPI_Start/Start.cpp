#include "Start.h"
#include "Visualisation.h"
#include <HAPI_lib.h>

#if defined(DEBUG) | defined(_DEBUG)
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK,__FILE__, __LINE__)
#endif

// HAPI itself is wrapped in the HAPISPACE namespace
using namespace HAPISPACE;

void Start::Play(int width, int height, std::string name)
{
	Visualisation visual;

	if (!visual.initialise(width, height, name))
		return;

	//Sets the FPS counter on screen
	HAPI.SetShowFPS(true, 0, 0, HAPI_TColour::GREEN);
	const HAPI_TKeyboardData &keyData = HAPI.GetKeyboardData();
	const HAPI_TControllerData &controllerData = HAPI.GetControllerData(0);

	if (!visual.CreateSprite("Background", "Data\\Background.tga", 256, 256))
		return;

	if (!visual.CreateSprite("player", "Data\\playerSprite.tga", 64, 64))
		return;

	while (HAPI.Update()) //Game loop
	{	//calls functions from classes

		const HAPI_TControllerData &controllerData = HAPI.GetControllerData(0);

		visual.ClearToColour(HAPI.GetScreenPointer(), width, height, HAPI_TColour(0, 0, 0));

		visual.RenderSprite("Background", 0, 0);
		visual.RenderSprite("player", posX, posY);
		//Moves sprite with WASD keys

		if (keyData.scanCode['W'])
			posY--;


		if (keyData.scanCode['S'])
			posY++;


		if (keyData.scanCode['A'])
			posX--;


		if (keyData.scanCode['D'])
			posX++;


		if (posY < height - 200 && posX < width - 200 && posY > 200 && posX > 200)
		{
			HAPI.SetControllerRumble(0, 40000, 40000);
		}
		else
		{
			HAPI.SetControllerRumble(0, 0, 0);
		}


		if (controllerData.isAttached)
		{
			int LeftThumbX = controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X];
			int LeftThumbY = controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y];
			int Deadzone = controllerData.analogueButtons[HK_GAMEPAD_LEFT_THUMB_DEADZONE];
			
			
			if (Deadzone + 7849 < LeftThumbX)
				posX++;

			if (Deadzone + 7849 < LeftThumbY)
				posY--;

			if (Deadzone - 7849 > LeftThumbX)
				posX--;

			if (Deadzone - 7849 > LeftThumbY)
				posY++;

		}
	}
}




