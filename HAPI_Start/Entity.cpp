#include "Entity.h"


Entity::~Entity()
{
}

void Entity::Render(Visualisation *vis)
{
	vis->RenderSprite(Spritename, m_position.x, m_position.y);
}

void Entity::RenderAnimation(Visualisation *vis)
{
	vis->RenderSprite(Spritename, m_position.x, m_position.y, curFrameX, curFrameY);
}

void Entity::SetPosition(int PosX, int PosY)
{
	m_position.x = PosX;
	m_position.y = PosY;
}

void Entity::SetFrames(int currentFrameX, int currentFrameY, int numberFramesX, int numberFramesY)
{
	curFrameX = currentFrameX;
	curFrameY = currentFrameY;

	numFramesX = numberFramesX;
	numFramesY = numberFramesY;
}


