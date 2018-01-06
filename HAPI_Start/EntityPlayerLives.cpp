#include "EntityPlayerLives.h"


EntityPlayerLives::~EntityPlayerLives()
{
}

void EntityPlayerLives::Update(World & world, Visualisation & vis)
{
	Vector2 pos{ GetPosition() };

	if (lives1)
		curFrameY = 2;

	if (lives0)
		curFrameY = 3;

	if (lives2)
		curFrameY = 1;

	SetPosition(pos);
}

void EntityPlayerLives::CheckCollision(Visualisation &vis, Entity &other)
{
	if (other.getSide() == eSide::ePlayer)
	{
		if (other.GetLives() == 1 && other.getSide() == eSide::ePlayer)
		{
			curFrameY = 2;
		}
		if (other.GetLives() == 0 && other.getSide() == eSide::ePlayer)
		{
			curFrameY = 3;
		}

		if (other.GetLives() == 2 && lives3 == true && other.getSide() == eSide::ePlayer)
		{
			curFrameY = 1;
			lives3 = false;
		}
	}
}
