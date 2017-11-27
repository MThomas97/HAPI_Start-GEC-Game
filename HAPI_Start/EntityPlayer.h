#pragma once
#include "Entity.h"

class EntityPlayer : public Entity
{
public:
	EntityPlayer(std::string spriteID) : Entity(spriteID) {};

	~EntityPlayer();

	void Update() override;

	eSide getSide() const override {return eSide::ePlayer; }

	//int numFramesX { 5 };
	//int numFramesY { 3 };
	//int curFrameX { 0 };
	//int curFrameY { 0 };
	int MoveSpeed{ 2 };
private:

	const HAPI_TKeyboardData &keyData = HAPI.GetKeyboardData();
	Vector2 vect;
	int PrevTime = 0;
	int HorsePrevTime = 0;
	
};

