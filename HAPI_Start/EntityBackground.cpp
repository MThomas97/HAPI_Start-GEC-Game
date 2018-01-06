#include "EntityBackground.h"
#include "Visualisation.h"

EntityBackground::~EntityBackground()
{
}

void EntityBackground::CheckCollision(Visualisation &vis, Entity &other)
{
	
}

void EntityBackground::Update(World &world, Visualisation &vis)
{
	Vector2 pos{ GetPosition() };
	pos.y += 10;

	if (pos.y > 800)
		pos.y = 0;

	SetPosition(pos);
}
