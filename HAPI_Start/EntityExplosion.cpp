#include "EntityExplosion.h"


EntityExplosion::~EntityExplosion()
{
}

bool EntityExplosion::CheckCollision(Vector2 nextpos, Rectangle sourceRect, Rectangle destinationRect)
{
	return true;
}

void EntityExplosion::Update(Visualisation &vis, float deltaTime)
{
	float HorseElapsedTime = HAPI.GetTime() - PrevTime;

	if (PrevTime + 50 < HorseElapsedTime)
	{
		PrevTime = HorseElapsedTime;

		curFrameX++;

		if (curFrameX >= numFramesX)
		{
			curFrameX = 0;

			curFrameY += 1;
		}

		if (curFrameY >= numFramesY)
		{
			curFrameY = 0;
			curFrameX = 0;

		}
	}
}