#pragma once
#include "Entity.h"

class Rectangle;

class Vector2;

class EntityPlayer : public Entity
{
public:
	EntityPlayer(std::string spriteID) : Entity(spriteID) {};

	~EntityPlayer();

	void Update(Visualisation &vis, float deltaTime) override final;

	eSide getSide() const override final {return eSide::ePlayer; }

	bool CheckCollision(Vector2 nextPos, Rectangle sourceRect, Rectangle destinationRect) override final;

	void GetenemyRect(const Rectangle &other);

private:
	Vector2 vect;
	
	Rectangle tempRect;

	Rectangle m_playerRect;

	Rectangle m_enemyRect;

	int PrevTime = 0;

	int numFramesX{ 4 };
	int numFramesY{ 1 };
};

