#pragma once
#include "Entity.h"

class Rectangle;

class EntityPlayer : public Entity
{
public:
	EntityPlayer(std::string spriteID) : Entity(spriteID) {};

	~EntityPlayer();

	void Update(float deltaTime) override final;

	eSide getSide() const override final {return eSide::ePlayer; }

	void CheckCollision() override final;

	void GetenemyRect(const Rectangle &other);

private:
	Vector2 vect;
	
	Rectangle tempRect;

	Rectangle m_playerRect;

	int PrevTime = 0;

	int numFramesX{ 4 };
	int numFramesY{ 1 };
};

