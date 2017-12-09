#pragma once
#include "Entity.h"

class Rectangle;

class Vector2;

class EntityPlayer : public Entity
{
public:
	EntityPlayer(std::string spriteID) : Entity(spriteID) {};

	~EntityPlayer();

	void Update(float deltaTime) override final;

	eSide getSide() const override final {return eSide::ePlayer; }

	void CheckCollision(Visualisation &vis, Entity &other) override final;

	void GetenemyRect(const Rectangle &other);

	void LoadRectangle(Visualisation &vis);

private:
	Vector2 vect;
	
	Vector2 nextPos;

	Rectangle tempRect;

	Rectangle m_playerRect;

	Rectangle m_enemyRect;

	int PrevTime = 0;

	int numFramesX{ 4 };
	int numFramesY{ 1 };
};

