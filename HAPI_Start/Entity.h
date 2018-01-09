#pragma once
#include "Vector2.h"
#include "Rectangle.h"
#include "World.h"
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
	eNeutral,
	eBullet
};

class Visualisation;

class World;

class Entity
{
public:
	Entity(std::string spriteID) : Spritename(spriteID) {};

	virtual ~Entity() = 0;

	virtual eSide getSide() const = 0;

	virtual void Update(World &world, Visualisation &vis) = 0; //performs updates on a specific entity

	void Render(Visualisation &vis, float s); //Renders the sprite

	void SetPosition(Vector2 newPos) { m_oldPosition = m_position; m_position = newPos; } //Sets the position of the entity

	void SetBackPosition(Vector2 oldPos) { m_position = m_oldPosition; } //Sets the position back to the old entity

	Vector2 GetPosition() const { return m_position; } //Gets the position

	Vector2 GetOldPosition() const { return m_oldPosition; } //Gets the previous position of the entity

	void AddScore(int addScore) { Score = Score + addScore; }

	int GetScore() const { return Score; }

	virtual void CheckCollision(Visualisation &vis, Entity &other); //Checks for collision against all other entities

	bool IsAlive() const { return m_alive; }

	void SetAlive(bool alive) { m_alive = alive; }

	bool IsEnemyOf(eSide a, eSide b);

	bool IsPickupOf(eSide a, eSide b);

	std::string GetSpritename() const { return Spritename; }

	int GetLives() const { return lives; }

	size_t bulletStartIndex{ 0 };

	void TakeDamage(int damageInflicted);

	void SetPaused(bool pause) { Paused = pause; }

protected:
	bool Paused{ false };
	int Score{ 0 };
	float NoAlpha{ false };
	int lives{ 3 };
	int health{ 100 };
	std::string Spritename;
	bool m_alive{ true };
	int m_speed{ 6 };
	int curFrameX{ 0 };
	int curFrameY{ 0 };
	int m_damageTaken{ 10 };

private:
	Vector2 m_position;
	Vector2 m_oldPosition;
};

