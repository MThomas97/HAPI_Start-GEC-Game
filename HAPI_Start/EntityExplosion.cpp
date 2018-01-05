#include "EntityExplosion.h"
#include "Visualisation.h"
#include "World.h"

constexpr DWORD kClockTime{ 1000 };

EntityExplosion::~EntityExplosion()
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
				m_alive = false;
			}
			m_lastTimeUpdatedAnimation = HAPI.GetTime();
		}
	SetPosition(GetPos);
}

void EntityExplosion::Spawn(eSide side, const Vector2 &pos, int damageAmount)
{
	GetPos = pos;
	m_side = eSide::eNeutral;
	SetPosition(pos);
	m_alive = true;
}
