#pragma once
#include "Entity.h"
class EntityEnemy : public Entity
{
public:
	EntityEnemy(std::string spriteID) : Entity(spriteID) {};
	~EntityEnemy();

	void Update(float deltaTime) override final;

	eSide getSide() const override final { return eSide::eEnemy; }
};

