#include "EntityEnemy.h"
#include "Visualisation.h"


EntityEnemy::~EntityEnemy()
{
}

void EntityEnemy::CheckCollision(Visualisation &vis, Entity &other)
{
	/*if (!IsEnemyOf(getSide(), other.getSide()))
		return;*/

	Vector2 oldPos{ GetOldPosition() };

	Rectangle thisRect(vis.GetRect(Spritename));
	Rectangle otherRect(vis.GetRect(other.GetSpritename()));

	Rectangle CollisionRect(thisRect);

	float width = thisRect.width() / 10.0f; //Reduces the size of the collider rectangle width by 10%

	float height = thisRect.height() / 10.0f; //Reduces the size of the collider rectangle height by 10%

	CollisionRect.left += width;
	CollisionRect.right -= width;
	CollisionRect.top += height;
	//CollisionRect.bottom -= height;
	Rectangle EnemyCollisionRect(otherRect);

	/*int w{ thisRect.width() };

	thisRect.left += w / 10;

	thisRect.right += w / 10;

	w;

	int h{ thisRect.height() };

	thisRect.top += h / 10;

	thisRect.bottom += h / 10;*/

	EnemyCollisionRect.Translate(other.GetPosition().x, other.GetPosition().y);

	CollisionRect.Translate(GetPosition().x, GetPosition().y);


	Vector2 thisDir{ GetOldPosition() - GetPosition() };
	Vector2 otherDir{ other.GetOldPosition() = other.GetPosition() };

	float biggestLength = 1.0f / std::max(thisDir.Length(), otherDir.Length());

	thisDir = thisDir * biggestLength;
	otherDir = otherDir * biggestLength;

	Vector2 newThisPos{ GetPosition() };
	Vector2 newOtherPos{ other.GetPosition() };

	//do
	//{
	thisRect = Rectangle(thisRect);
	otherRect = Rectangle(otherRect);

	newThisPos = newThisPos + thisDir;
	newOtherPos = newOtherPos + otherDir;

	thisRect.Translate((int)newThisPos.x, (int)newThisPos.y);
	otherRect.Translate((int)newOtherPos.x, (int)newOtherPos.y);
	//} while ();

	//temp.x = m_position.x - w;

	//temp.y = m_position.y - h;

	if (thisRect.CheckCollision(otherRect))
	{

		SetBackPosition(oldPos);
		
	}
	
}

void EntityEnemy::Update(World &world, Visualisation &vis, float dt)
{

	Vector2 pos{ GetPosition() };

	//pos.y -= 1;

	SetPosition(pos);
	//AI stuff

}
