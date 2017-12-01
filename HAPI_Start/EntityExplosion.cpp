#include "EntityExplosion.h"


EntityExplosion::~EntityExplosion()
{
}

void EntityExplosion::CheckCollision()
{

}

void EntityExplosion::Update(float deltaTime)
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