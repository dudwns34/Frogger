#include "RiverItem.h"

RiverItem::RiverItem(const sf::Vector2f& argScreenPos, const bool& argIsAlive, const sf::Sprite& argSprite, const sf::Vector2f& argDimensions, const float& argSpeed, const ERiverItemType& argRiverItemType) :
	Shape(argScreenPos, argIsAlive, argSprite, argDimensions), speed(argSpeed), riverItemType(argRiverItemType)
{
}

RiverItem::~RiverItem()
{
}

void RiverItem::Render(sf::RenderWindow& argWindow)
{
	if (isAlive)
	{
		sprite.setPosition(screenPos);		
		argWindow.draw(sprite);
	}
}

void RiverItem::Move()
{
	screenPos.x -= speed;
}

void RiverItem::Update(const sf::Vector2f& argScreenPos)
{
	if (speed > 0)
	{
		//THESE GO TO THE LEFT
		if (screenPos.x < -dimensions.x)
		{
			isAlive = false;
			//Reposition the vehicle
			screenPos.x = argScreenPos.x;
		}
	}
	else if (speed < 0)
	{
		//THESE GO TO THE RIGHT
		if (screenPos.x > argScreenPos.x - dimensions.x)
		{
			isAlive = false;
			//Reposition the vehicle
			screenPos.x = 0.0f;
		}
	}
	
}

ERiverItemType RiverItem::GetRiverItemType()
{
	return riverItemType;
}

void RiverItem::SpawnRiverItem(const std::list<RiverItem*>& argRiverItemList, const float& argSpawnDistance)
{
	//all vehicles are spawning at the same time
	bool canSpawn{ false };
	for (RiverItem* otherRiverItem : argRiverItemList)
	{
		if (this != otherRiverItem)
		{
			if (otherRiverItem->CheckIfAlive())
			{
				if (GetRiverItemType() == otherRiverItem->GetRiverItemType())
				{
					//checks if it is not within the dimensions of the vehicle times the distance established
					if (screenPos.x <= otherRiverItem->GetScreenPosition().x - (argSpawnDistance * dimensions.x) ||
						screenPos.x >= otherRiverItem->GetScreenPosition().x + (argSpawnDistance * dimensions.x))
					{
						canSpawn = true;
					}
					//checks if it is within the dimensions of the vehicle times the distance establised
					else if (screenPos.x > otherRiverItem->GetScreenPosition().x - (argSpawnDistance * dimensions.x) &&
						screenPos.x < otherRiverItem->GetScreenPosition().x + (argSpawnDistance * dimensions.x))
					{
						canSpawn = false;
						break;
					}
				}
			}
		}
	}
	if (canSpawn)
		isAlive = !isAlive;
}
