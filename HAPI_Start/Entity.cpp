#include "Entity.h"


Entity::~Entity()
{
}

void Entity::Render(Visualisation *vis)
{
	vis->RenderSprite(Spritename, m_position.x, m_position.y);
}

void Entity::SetPosition(int PosX, int PosY)
{
	m_position.x = PosX;
	m_position.y = PosY;
}


