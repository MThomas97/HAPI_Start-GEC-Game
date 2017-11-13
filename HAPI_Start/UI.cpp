#include "UI.h"



UI::UI()
{
}

void UI::KeyboardInput(const HAPI_TKeyboardData &keyData, int playerPosX, int playerPosY, int elapsedTime, int prevTime)
{

	
		prevTime = elapsedTime;
		float playerSpeed = 5;

		//Moves sprite with WASD keys
		if (keyData.scanCode['W'])
			playerPosY-= playerSpeed;

		if (keyData.scanCode['S'])
			playerPosY+= playerSpeed;

		if (keyData.scanCode['A'])
			playerPosX-= playerSpeed;

		if (keyData.scanCode['D'])
			playerPosX+ playerSpeed;

		
		tempPosX += playerPosX;
		playerPosX = tempPosX;
		
	//FIX THIS
}
