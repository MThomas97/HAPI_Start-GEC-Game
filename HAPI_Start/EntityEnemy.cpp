#include "EntityEnemy.h"
#include "Visualisation.h"


EntityEnemy::~EntityEnemy()
{
}

void EntityEnemy::CheckCollision(Visualisation &vis, Entity &other)
{
	/*if (getSide() == eSide::ePlayer)
	{

	}
	m_enemyRect = Rectangle(m_position.x, m_position.y);
	m_temp = m_enemyRect;*/
	
}

void EntityEnemy::Update(Visualisation &vis, float dt)
{

	Vector2 pos{ GetPosition() };

	SetPosition(pos);
	//AI stuff

}
