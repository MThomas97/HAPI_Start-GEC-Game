#pragma once
#include "Entity.h"
class EntityScrollingBackground : public Entity
{
public:
	EntityScrollingBackground(std::string spriteID) : Entity(spriteID) { tempPos = GetPosition(), NoAlpha = true; };
	~EntityScrollingBackground();

	void Update(World &world, Visualisation &vis, float dt) override final;

	eSide getSide() const override final { return eSide::eNeutral; }

	void CheckCollision(Visualisation &vis, Entity &other) override final;

private:
	Vector2 tempPos;
};

