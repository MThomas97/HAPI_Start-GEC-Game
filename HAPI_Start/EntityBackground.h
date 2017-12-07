#pragma once
#include "Entity.h"
class EntityBackground : public Entity
{
public:
	EntityBackground(std::string spriteID) : Entity(spriteID) {};
	~EntityBackground();

	void Update(Visualisation &vis, float deltaTime) override final;

	eSide getSide() const override final { return eSide::eNeutral; }

	bool CheckCollision(Vector2 nextPos, Rectangle sourceRect, Rectangle destinationRect) override final;

};

