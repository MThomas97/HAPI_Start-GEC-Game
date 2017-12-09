#include "EntityEnemy.h"



EntityEnemy::~EntityEnemy()
{
}

void EntityEnemy::CheckCollision(Visualisation &vis, Entity &other)
{
	if (getSide() == eSide::ePlayer)
	{

	}
	m_enemyRect = Rectangle(m_position.x, m_position.y);
	m_temp = m_enemyRect;
	
}

void EntityEnemy::Update(float deltaTime)
{
	//AI stuff

}
