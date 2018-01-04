#include "EntityExplosion.h"
#include "Visualisation.h"
#include "World.h"

EntityExplosion::~EntityExplosion()
{
}

void EntityExplosion::CheckCollision(Visualisation &vis, Entity &other)
{
	
}

void EntityExplosion::Update(World &world, Visualisation &vis, float dt)
{
	Vector2 pos{ GetPosition() };

	if (HAPI.GetTime() - m_lastTimeUpdatedAnimation >= m_animationTime)
		{
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
			m_lastTimeUpdatedAnimation = HAPI.GetTime();
		}
	
	SetPosition(pos);
}