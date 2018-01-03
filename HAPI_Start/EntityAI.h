#pragma once
#include "Entity.h"
class EntityAI :
	public Entity
{
public:
	EntityAI(std::string spriteID) : Entity(spriteID) {};
	~EntityAI();

	void BackToPatrol();

	void Update(Visualisation &vis, float dt) override final;

	void CheckForPlayer(Visualisation & vis, Entity & other);

	eSide getSide() const override final { return eSide::eEnemy; }

	void CheckCollision(Visualisation &vis, Entity &other) override final;

private:
	int patrol{ 1 };
	bool alert{ false };
	int attack{ 0 };
	
};

