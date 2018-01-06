#pragma once
#include "Entity.h"
class EntityPlayerLives :
	public Entity
{
public:
	EntityPlayerLives(std::string spriteID) : Entity(spriteID) {};
	~EntityPlayerLives();

	void Update(World & world, Visualisation &vis) override final;

	eSide getSide() const override final { return eSide::eNeutral; }

	void CheckCollision(Visualisation &vis, Entity &other);


private:
	bool lives3{ true };
	bool lives2{ false };
	bool lives1{ false };
	bool lives0{ false };
};

