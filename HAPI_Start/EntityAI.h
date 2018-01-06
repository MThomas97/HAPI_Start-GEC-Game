#pragma once
#include "Entity.h"
#include "World.h"
class EntityAI :
	public Entity
{
public:
	EntityAI(std::string spriteID) : Entity(spriteID) { health = 1; };
	~EntityAI();

	void Update(World &world, Visualisation &vis) override final;

	eSide getSide() const override final { return eSide::eEnemy; }

	void CheckCollision(Visualisation &vis, Entity &other) override final;

private:
	int path{ 1 };
	float ResetPosition{ false };
	float EntityDied{ false };
};

