#include "EntityAI.h"
#include "Visualisation.h"

EntityAI::~EntityAI()
{
}

void EntityAI::BackToPatrol()
{
	Vector2 pos{ GetPosition() };
	
	if (pos.x >= 400)
	{
		patrol = 1;
		
	}
	else if (pos.x <= 100)
	{
		patrol = 2;
		
	}
	if (pos.x >= 100 && pos.x <= 400 && patrol == 0) {
		patrol = 1;
		
	}
	
}

void EntityAI::Update(Visualisation & vis, float dt)
{
	Vector2 pos{ GetPosition() };

	//Set the start state of ai



	switch (patrol){
	case 0: 
		break;
	case 1: 
		if (pos.x <= 200)
			patrol = 2;

		pos.x -= m_speed;
		break;

	case 2: 
		if (pos.x >= 400)
		{
			patrol = 1;
			break;
		}
		pos.x += m_speed;
		break;
	case 3:
		BackToPatrol();
		break;
	}

	switch (alert) {
	case true:
		patrol = 0; //state of ai is no longer in patrol state
		break;
	
	case false:
		BackToPatrol();
		break;
	
	}

	switch (attack) {
	case 0:
		break;
	case 1:
		pos.x -= m_speed;
		break;
	case 2:
		pos.x += m_speed;
		break;

	}

	SetPosition(pos);
		 
			
		 

}

void EntityAI::CheckForPlayer(Visualisation &vis, Entity &other)
{
	

	/*if (!IsEnemyOf(getSide(), other.getSide()))
		return false;*/

	Vector2 otherDirPos{ other.GetOldPosition() - other.GetPosition() };
	Vector2 myPos{ GetPosition() };
	Vector2 otherPos{ other.GetPosition() };


	Rectangle thisRect(vis.GetRect(Spritename));
	Rectangle otherRect(vis.GetRect(other.GetSpritename()));
	Rectangle AICollisionRect(thisRect);
	Rectangle OtherCollisionRect(otherRect);

	OtherCollisionRect.Translate(other.GetPosition().x, other.GetPosition().y);

	AICollisionRect.Translate(GetPosition().x, GetPosition().y);

	if (OtherCollisionRect.right > AICollisionRect.left && OtherCollisionRect.left < AICollisionRect.right)
	{
		if (OtherCollisionRect.bottom > AICollisionRect.top && OtherCollisionRect.top < AICollisionRect.bottom)
		{
			alert = true;
			attack = 1;
		}
		/*myPos.x -=  m_speed;
		SetPosition(myPos);*/
	}
	else
	{
		alert = false;
		attack = 0;
	}

	if (OtherCollisionRect.left > AICollisionRect.right)
	{
		if (OtherCollisionRect.bottom > AICollisionRect.top && OtherCollisionRect.top < AICollisionRect.bottom)
		{
			alert = true;
			attack = 2;
		}
	}
	else {
		alert = false;
		attack = 0;
	}
		
	
	//SetPosition(myPos);
	
}

void EntityAI::CheckCollision(Visualisation &vis, Entity &other)
{
	CheckForPlayer(vis, other);
}
