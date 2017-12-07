#pragma once
#include "Entity.h"
class EntityScrollingBackground : public Entity
{
public:
	EntityScrollingBackground(std::string spriteID) : Entity(spriteID) {};
	~EntityScrollingBackground();

	void Update(Visualisation &vis, float deltaTime) override final;

	eSide getSide() const override final { return eSide::eNeutral; }

	bool CheckCollision(Vector2 nextPos, Rectangle sourceRect, Rectangle destinationRect) override final;
};

