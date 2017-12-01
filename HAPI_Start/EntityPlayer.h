#pragma once
#include "Entity.h"

class EntityPlayer : public Entity
{
public:
	EntityPlayer(std::string spriteID) : Entity(spriteID) {};

	~EntityPlayer();

	void Update(float deltaTime) override final;

	eSide getSide() const override final {return eSide::ePlayer; }

private:
	Vector2 vect;
	

	int PrevTime = 0;
};

