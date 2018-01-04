#pragma once
#include "Entity.h"
class EntityBackground : public Entity
{
public:
	EntityBackground(std::string spriteID) : Entity(spriteID) {};
	~EntityBackground();

	void Update(World &world, Visualisation &vis, float dt) override final;

	eSide getSide() const override final { return eSide::eNeutral; }

	void CheckCollision(Visualisation &vis, Entity &other) override final;

};

