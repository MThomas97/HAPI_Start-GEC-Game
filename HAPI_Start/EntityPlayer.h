#pragma once
#include "Entity.h"
#include "World.h"

class Rectangle;

class Vector2;

class EntityPlayer : public Entity
{
public:
	EntityPlayer(std::string spriteID) : Entity(spriteID) { lives = 3, curFrameX = 1;};

	~EntityPlayer();

	void Update(World &world, Visualisation &vis) override final;

	eSide getSide() const override final {return eSide::ePlayer; }

private:

	//bool ClipToScreen{ false };
	//float LoadOnce{ true };
	float SetOnce{ true };

	DWORD lastTick{ 0 };

	

	//float playing = false;

	

};

