#include "Entity.h"
#include "Visualisation.h"
#include "Rectangle.h"
Entity::~Entity()
{
}

void Entity::Render(Visualisation &vis)
{
	vis.RenderSprite(Spritename, (int)m_position.x, (int)m_position.y, curFrameX, curFrameY);
}

bool Entity::IsEnemyOf(eSide a, eSide b)
{
	if (a == eSide::ePlayer && b == eSide::eEnemy)
		return true;

	return false;
}



