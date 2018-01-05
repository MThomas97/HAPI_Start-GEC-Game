#include "Restart.h"



Restart::Restart()
{
}

void Restart::RestartGame()
{
	static const HAPI_TKeyboardData &keyData = HAPI.GetKeyboardData();

	/*while (HAPI.Update())
	{
		if (keyData.scanCode['S'])
		{
			World world(600, 800, "Space Shooter");
			world.run();
		}
	}*/

	
	World world(600, 800, "Space Shooter");
	world.SetRestart(false);
	world.run();

	/*if (keyData.scanCode['S'])
	{
		World world(600, 800, "Space Shooter");
		world.run();
	}*/
	
}


Restart::~Restart()
{
}
