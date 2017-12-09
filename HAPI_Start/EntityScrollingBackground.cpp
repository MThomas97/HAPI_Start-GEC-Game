#include "EntityScrollingBackground.h"


EntityScrollingBackground::~EntityScrollingBackground()
{
}

void EntityScrollingBackground::CheckCollision(Visualisation &vis, Entity &other)
{
	
}

void EntityScrollingBackground::Update(float deltaTime)
{
	m_position.y += 1 * deltaTime;

	if (m_position.y > 0)
	{
		m_position.y = tempPos.y;
	}
}