#pragma once
#include "Entity.h"
class EntityExplosion :
	public Entity
{
public:
	EntityExplosion(std::string spriteID) : Entity(spriteID) {};
	~EntityExplosion();

	void Update(float deltaTime) override final;

	eSide getSide() const override final { return eSide::ePlayer; }

	bool CheckCollision(Vector2 nextPos) override final;

private:
	int PrevTime = 0;
	int numFramesX{ 5 };
	int numFramesY{ 3 };
};

