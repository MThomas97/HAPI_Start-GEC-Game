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

	virtual void Update(Visualisation &vis) = 0;

	void Render(Visualisation &vis, float s);

	void SetPosition(Vector2 newPos) { m_oldPosition = m_position; m_position = newPos; }

	void SetBackPosition(Vector2 oldPos) { m_position = m_oldPosition; }

	Vector2 GetPosition() const { return m_position; }

	Vector2 GetOldPosition() const { return m_oldPosition; }

	virtual void CheckCollision(Visualisation &vis, Entity &other) = 0;

	//void SetFrames(Vector2 curFrame) { m_currentFrame = curFrame; }
	
	//void SetFrames1(Vector2 numFrames) { m_numFrames = numFrames; }

	bool IsEnemyOf(eSide a, eSide b);

	std::string GetSpritename() const { return Spritename; }

protected:
	//Vector2 m_position;
	//Vector2 m_nextPos;
	//Vector2 tempPos;
	//Rectangle m_entityRect;
	//Vector2 m_currentFrame;
	//Vector2 m_numFrames;
	int health{ 100 };
	std::string Spritename; //create getter? make private again
	bool m_alive{ true };
	float m_speed{ 6.0f };
	int curFrameX{ 0 };
	int curFrameY{ 0 };

//private:
	Vector2 m_position;
	Vector2 m_oldPosition;
};

