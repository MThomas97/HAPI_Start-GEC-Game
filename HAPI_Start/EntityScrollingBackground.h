#pragma once
#include "Entity.h"
class EntityScrollingBackground : public Entity
{
public:
	EntityScrollingBackground(std::string spriteID) : Entity(spriteID) {NoAlpha = true; };
	~EntityScrollingBackground();

	void Update(World &world, Visualisation &vis) override final;

	eSide getSide() const override final { return eSide::eNeutral; }
};

