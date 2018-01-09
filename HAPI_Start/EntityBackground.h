#pragma once
#include "Entity.h"
class EntityBackground : public Entity
{
public:
	EntityBackground(std::string spriteID) : Entity(spriteID) { tempPos = GetPosition(), NoAlpha = true; };
	~EntityBackground();

	void Update(World &world, Visualisation &vis) override final;

	eSide getSide() const override final { return eSide::eNeutral; }

private:
	Vector2 tempPos;
};

