#pragma once
#include "Entity.h"
class EntityPlayerLives :
	public Entity
{
public:
	EntityPlayerLives(std::string spriteID) : Entity(spriteID) {};
	~EntityPlayerLives();

	void Update(World & world, Visualisation &vis, float dt) override final;

	eSide getSide() const override final { return eSide::eNeutral; }

	void CheckCollision(Visualisation &vis, Entity &other);


private:
	float lives3{ true };
	float lives2{ false };
	float lives1{ false };
	float lives0{ false };


};

