#pragma once
#include "Visualisation.h"
#include"Vector2.h"
#include <HAPI_lib.h>

#if defined(DEBUG) | defined(_DEBUG)
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK,__FILE__, __LINE__)
#endif
// HAPI itself is wrapped in the HAPISPACE namespace
using namespace HAPISPACE;

enum class eSide
{
	ePlayer,
	eEnemy,
	eNeutral
};

class Entity
{
public:
	Entity(std::string spriteID) : Spritename(spriteID) {};

	virtual ~Entity() = 0;

	virtual eSide getSide() const = 0;

	virtual void Update() = 0;
	
protected:

	Vector2 m_position;
	int health{ 100 };
	std::string Spritename;
	//float MoveSpeed{ 3 };
	//int curFrameX{ 0 };
	//int curFrameY{ 0 };
	//float PrevTime{ 0 };
	//float ElapsedTime = HAPI.GetTime() - PrevTime;
};

