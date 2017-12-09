#include "EntityBackground.h"

EntityBackground::~EntityBackground()
{
}

void EntityBackground::CheckCollision(Visualisation &vis, Entity &other)
{
	
}

void EntityBackground::Update(float deltaTime)
{
	m_position.y += 1 * deltaTime;

	if (m_position.y > 800)
	{
		m_position.y = tempPos.y;
	}
}
