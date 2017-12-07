#include "EntityScrollingBackground.h"


EntityScrollingBackground::~EntityScrollingBackground()
{
}

bool EntityScrollingBackground::CheckCollision(Vector2 nextPos)
{
	return true;
}

void EntityScrollingBackground::Update(float deltaTime)
{
	m_position.y += 1 * deltaTime;

	if (m_position.y > 0)
	{
		m_position.y = tempPos.y;
	}
}