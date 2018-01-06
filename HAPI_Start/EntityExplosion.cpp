#include "EntityExplosion.h"
#include "Visualisation.h"
#include "World.h"

constexpr DWORD kTickTime{ 20 };

EntityExplosion::~EntityExplosion()
{
}

void EntityExplosion::Update(World &world, Visualisation &vis)
{
	Vector2 pos{ GetPosition() };

	if (m_alive)
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
			SetPosition(GetPos);
		}
}

void EntityExplosion::Spawn(eSide side, const Vector2 &pos, int damageAmount)
{
	GetPos = pos;
	
	m_side = eSide::eNeutral;
	SetPosition(pos);
	m_alive = true;
}
