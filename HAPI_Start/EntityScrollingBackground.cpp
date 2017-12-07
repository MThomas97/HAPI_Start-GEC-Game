#include "EntityScrollingBackground.h"


EntityScrollingBackground::~EntityScrollingBackground()
{
}

bool EntityScrollingBackground::CheckCollision(Vector2 nextPos, Rectangle sourceRect, Rectangle destinationRect)
{
	return true;
}

void EntityScrollingBackground::Update(Visualisation &vis, float deltaTime)
{
	m_position.y += 1 * deltaTime;

	if (m_position.y > 0)
	{
		m_position.y = tempPos.y;
	}
}