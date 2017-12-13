#include "EntityExplosion.h"
#include "Visualisation.h"

EntityExplosion::~EntityExplosion()
{
}

void EntityExplosion::CheckCollision(Visualisation &vis, Entity &other)
{
	
}

void EntityExplosion::Update(Visualisation &vis)
{
	float HorseElapsedTime = HAPI.GetTime() - PrevTime;

	if (PrevTime + 50 < HorseElapsedTime)
	{
		PrevTime = HorseElapsedTime;

		curFrameX++;
		
		if (curFrameX >= vis.GetNumframesX(Spritename))
		{
			curFrameX = 0;

			curFrameY += 1;
		}

		if (curFrameY >= vis.GetNumframesY(Spritename))
		{
			curFrameY = 0;
			curFrameX = 0;

		}
	}
}