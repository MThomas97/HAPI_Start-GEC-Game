#pragma once
#include"Vector2.h"
#include "Rectangle.h"
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

class Visualisation;

class Rectangle;

class Entity
{
public:
	Entity(std::string spriteID) : Spritename(spriteID) {};

	virtual ~Entity() = 0;

	virtual eSide getSide() const = 0;

	virtual void Update(float deltaTime) = 0;

	void Render(Visualisation &vis);

	void SetPosition(Vector2 newPos) { m_position = newPos, tempPos = newPos; }

	virtual void CheckCollision() = 0;

	//void SetFrames(Vector2 curFrame) { m_currentFrame = curFrame; }
	
	//void SetFrames1(Vector2 numFrames) { m_numFrames = numFrames; }
	
protected:
	Vector2 m_position;
	Vector2 m_nextPos;
	Vector2 tempPos;
	Rectangle m_entityRect;
	//Vector2 m_currentFrame;
	//Vector2 m_numFrames;
	int health{ 100 };
	std::string Spritename;
	bool m_alive{ true };
	float m_speed{ 0.5f };
	int curFrameX{ 0 };
	int curFrameY{ 0 };
};

