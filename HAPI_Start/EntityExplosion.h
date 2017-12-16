#pragma once
#include "Entity.h"
class EntityExplosion :
	public Entity
{
public:
	EntityExplosion(std::string spriteID) : Entity(spriteID) {};
	~EntityExplosion();

	void Update(Visualisation & vis, float dt) override final;

	eSide getSide() const override final { return eSide::eNeutral; }

	void CheckCollision(Visualisation &vis, Entity &other) override final;

private:
	int PrevTime = 0;
	
};

