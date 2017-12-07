#include "EntityEnemy.h"



EntityEnemy::~EntityEnemy()
{
}

bool EntityEnemy::CheckCollision(Vector2 nextPos, Rectangle sourceRect, Rectangle destinationRect)
{
	if (getSide() == eSide::ePlayer)
	{

	}
	m_enemyRect = Rectangle(m_position.x, m_position.y);
	m_temp = m_enemyRect;
	return true;
}

void EntityEnemy::Update(Visualisation &vis, float deltaTime)
{
	//AI stuff
}
