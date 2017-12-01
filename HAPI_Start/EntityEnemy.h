#pragma once
#include "Entity.h"

class Rectangle;

class EntityEnemy : public Entity
{
public:
	EntityEnemy(std::string spriteID) : Entity(spriteID) {};
	~EntityEnemy();

	void Update(float deltaTime) override final;

	eSide getSide() const override final { return eSide::eEnemy; }

	void CheckCollision() override final;

	Rectangle m_enemyRect;
private:

};

