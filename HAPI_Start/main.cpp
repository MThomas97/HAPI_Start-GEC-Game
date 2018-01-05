/*
	HAPI Start
	----------
	This solution contains an already set up HAPI project and this main file
	
	The directory structure and main files are:

	HAPI_Start - contains the Visual Studio solution file (.sln)
		HAPI_Start - contains the Visual Studio HAPI_APP project file (.vcxproj) and source code
			HAPI - the directory with all the HAPI library files
			Data - a place to put your data files with a few sample ones provided

	Additionally in the top directory there are two batch files for creating a redistributable Demo folder
*/

// Include the HAPI header to get access to all of HAPIs interfaces
#include <HAPI_lib.h>
#include "World.h"
#include "Restart.h"


#if defined(DEBUG) | defined(_DEBUG)
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK,__FILE__, __LINE__)
#endif

// HAPI itself is wrapped in the HAPISPACE namespace
using namespace HAPISPACE;

float Restart2{ false };
int width{ 600 };
int height{ 800 };
// Every HAPI program has a HAPI_Main as an entry point
// When this function exits the program will close down

void HAPI_Main()
{

	World world(width, height, "Space Shooter");

	world.run();

	Restart RestartNow;

	RestartNow.RestartGame();

	

	//HAPI.Initialise(width, height, "Space Shooter");

	static const HAPI_TKeyboardData &keyData = HAPI.GetKeyboardData();

	//if (keyData.scanCode['A'])
	//{
	//	Restart = true;
	//}
	//else {
	//	Restart = false;
	//}
	//
	////world.run();
	//if(Restart)
		
	
}

