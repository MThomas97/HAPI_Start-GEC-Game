#include "Entity.h"
#include "Visualisation.h"
#include "Rectangle.h"
Entity::~Entity()
{
}

void Entity::Render(Visualisation &vis, float s)
{
	if (!m_alive)
		return;

	Vector2 interPos{ m_oldPosition + (m_position - m_oldPosition) * s };

	vis.RenderSprite(Spritename, (int)interPos.x, (int)interPos.y, curFrameX, curFrameY);
}

bool Entity::IsEnemyOf(eSide a, eSide b)
{
	if (a == eSide::ePlayer && b == eSide::eEnemy)
		return true;

	return false;
}




