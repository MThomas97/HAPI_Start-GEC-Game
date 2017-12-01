#include "EntityExplosion.h"


EntityExplosion::~EntityExplosion()
{
}

void EntityExplosion::Update(float deltaTime)
{
	float HorseElapsedTime = HAPI.GetTime() - PrevTime;

	//if (PrevTime + 50 < HorseElapsedTime)
	//{
		PrevTime = HorseElapsedTime;

		curFrameX++ * deltaTime;

		if (curFrameX >= numFramesX)
		{
			curFrameX = 0 * deltaTime;

			curFrameY += 1 * deltaTime;
		}

		if (curFrameY >= numFramesY)
		{
			curFrameY = 0 * deltaTime;
			curFrameX = 0 * deltaTime;

		}
	//}
}