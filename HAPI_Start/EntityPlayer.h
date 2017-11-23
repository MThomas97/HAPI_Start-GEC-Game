#pragma once
#include "Entity.h"
class World;

class Visualisation;

class EntityPlayer : public Entity
{
public:
	EntityPlayer(std::string spriteID) : Entity(spriteID) {};

	~EntityPlayer();

	void Update() override;

	//int GetPosX() { return playerPosX; }

	//int GetPosY() { return playerPosY; }

	eSide getSide() const override {return eSide::ePlayer; }

	//std::string GetGraphicID() const { return PlayerID; }
	int playerPosX{ 0 };
	int playerPosY{ 0 };
	int numFramesX { 5 };
	int numFramesY { 3 };
	int curFrameX { 0 };
	int curFrameY { 0 };
	int MoveSpeed { 2 };
private:
	//const std::string PlayerID{ "Data\\player.png" };
	//World *m_world{ nullptr };

	const HAPI_TKeyboardData &keyData = HAPI.GetKeyboardData();
	//Gets the values of left thumb x, y and deadzone
	float PrevTime = 0;
	float HorsePrevTime = 0;
	
};

