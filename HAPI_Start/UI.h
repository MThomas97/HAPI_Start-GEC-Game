#pragma once
#include <HAPI_lib.h>

#if defined(DEBUG) | defined(_DEBUG)
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK,__FILE__, __LINE__)
#endif

// HAPI itself is wrapped in the HAPISPACE namespace
using namespace HAPISPACE;

class UI
{
public:
	UI();
	
	void KeyboardInput(const HAPI_TKeyboardData &keyData, int playerPosX, int playerPosY, int elapsedTime, int prevTime);

	int tempPosX = 0;
	
};

