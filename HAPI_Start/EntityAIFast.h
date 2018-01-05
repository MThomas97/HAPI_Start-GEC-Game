#pragma once
#include "Entity.h"
class EntityAIFast : public Entity
{
public:
	EntityAIFast(std::string spriteID) : Entity(spriteID) {health = 1;};
	~EntityAIFast();

	void Update(World &world, Visualisation &vis, float dt) override final;

	eSide getSide() const override final { return eSide::eEnemy; }

	void CheckCollision(Visualisation &vis, Entity &other) override final;

private:
	int path{ 1 };
	float ResetPosition{ false };
	float EntityDied{ false };
	int randNum = 1;
};

