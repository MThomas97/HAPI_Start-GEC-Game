#include "EntityEnemy.h"



EntityEnemy::~EntityEnemy()
{
}

void EntityEnemy::CheckCollision()
{

}

void EntityEnemy::Update(float deltaTime)
{
	m_enemyRect = Rectangle(m_position.x, m_position.y);
	//AI stuff
}
