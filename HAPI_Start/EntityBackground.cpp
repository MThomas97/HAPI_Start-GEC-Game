#include "EntityBackground.h"

EntityBackground::~EntityBackground()
{
}

bool EntityBackground::CheckCollision(Vector2 nextPos)
{
	return true;
}

void EntityBackground::Update(float deltaTime)
{
	m_position.y += 1 * deltaTime;

	if (m_position.y > 800)
	{
		m_position.y = tempPos.y;
	}
}
