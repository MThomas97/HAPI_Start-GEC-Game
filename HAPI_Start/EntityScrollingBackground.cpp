#include "EntityScrollingBackground.h"
#include "Visualisation.h"

EntityScrollingBackground::~EntityScrollingBackground()
{
}

void EntityScrollingBackground::CheckCollision(Visualisation &vis, Entity &other)
{
	
}

void EntityScrollingBackground::Update(World &world, Visualisation &vis, float dt)
{
	Vector2 pos{ GetPosition() };
	pos.y += 10;

	if (pos.y > 0)
	{
		pos.y = -800;
		
	}
	
	SetPosition(pos);
}