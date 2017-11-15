#pragma once
#include "Entity.h"
class EntityPlayer : public Entity
{
public:
	EntityPlayer();

	void Update() override;

	int GetPosX() { return playerPosX; }

	int GetPosY() { return playerPosY; }

	std::string GetGraphicID() const { return PlayerID; }
	int playerPosX{ 0 };
	int playerPosY{ 0 };
	float numFramesX = { 5 };
	float numFramesY = { 3 };
	float curFrameX = { 0 };
	float curFrameY = { 0 };

private:
	const std::string PlayerID{ "Data\\player.png" };
	
	const HAPI_TKeyboardData &keyData = HAPI.GetKeyboardData();
	//Gets the values of left thumb x, y and deadzone
	float PrevTime = 0;
	float HorsePrevTime = 0;
	
};

