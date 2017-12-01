#include "EntityBackground.h"

EntityBackground::~EntityBackground()
{
}

void EntityBackground::CheckCollision()
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
