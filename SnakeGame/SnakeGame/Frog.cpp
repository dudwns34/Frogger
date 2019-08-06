#include "Frog.h"

Frog::Frog(const sf::Vector2f& argScreenPos, const bool& argIsAlive, const sf::Sprite& argSprite, const sf::Vector2f& argDimensions, const sf::Color& argColour) :
	Shape(argScreenPos, argIsAlive, argSprite, argDimensions), Colour(argColour)
{
}

Frog::~Frog()
{
}

void Frog::Render(sf::RenderWindow& argWindow)
{
	if (isAlive)
	{
		sprite.setPosition(screenPos);
		sprite.setScale({ 2.0f, 2.0f });
		argWindow.draw(sprite);
	}
}

void Frog::Move()
{	
}

void Frog::Update(const sf::Vector2f& argScreenPos, sf::RenderWindow& argWindow, const std::list<Frog*> &argFrogPlayerList, const std::list<Vehicle*> &argVehicleList, const std::list<RiverItem*> &argRiverItemList, int &argTimeLeft)
{	
	//Checks if the Frog has gone off the screen
	if (screenPos.x < -dimensions.x || screenPos.x > argScreenPos.x - dimensions.x * 2)
	{
		LoseALife();
	}
	if (screenPos.y < 0 || screenPos.y > argScreenPos.y - dimensions.y * 2)
	{
		LoseALife();
	}
	//Checks if the Frog has collided with a vehicle
	if (isOnLand)
	{
		for (Vehicle* vehicle : argVehicleList)
		{
			if (vehicle->CheckIfAlive())
			{
				// it checks that it is within the dimensions of the vehicle
				if (screenPos.x > vehicle->GetScreenPosition().x - vehicle->GetDimensions().x / 2.0f &&
					screenPos.y > vehicle->GetScreenPosition().y - vehicle->GetDimensions().y / 2.0f &&
					screenPos.x < vehicle->GetScreenPosition().x + vehicle->GetDimensions().x / 2.0f &&
					screenPos.y < vehicle->GetScreenPosition().y + vehicle->GetDimensions().y / 2.0f)
				{					
					LoseALife();
					break;
				}
			}
		}
	}	
	else
	{
		if (!isDrowning)
		{
			//Checks if the Frog is on top of a river item
			for (RiverItem* riverItem : argRiverItemList)
			{
				if (riverItem->CheckIfAlive())
				{
					// it checks that it is within the dimensions of the river item
					if (screenPos.x > riverItem->GetScreenPosition().x - riverItem->GetDimensions().x / 2.0f &&
						screenPos.y > riverItem->GetScreenPosition().y - riverItem->GetDimensions().y / 2.0f &&
						screenPos.x < riverItem->GetScreenPosition().x + riverItem->GetDimensions().x / 2.0f &&
						screenPos.y < riverItem->GetScreenPosition().y + riverItem->GetDimensions().y / 2.0f)
					{
						screenPos.x -= riverItem->GetSpeed();
						isDrowning = false;
						break;
					}					
					else
					{
						isDrowning = true;
					}
				}
			}
		}		
	}
	//Checks if the Frog has collided with other Frog
	//loop through every Frog 
	for (Frog* player : argFrogPlayerList)
	{
		if (player != this)
		{
			//loop through every segment available
			if (player->CheckIfAlive())
			{
				//checks if it collided
				if (screenPos == player->GetScreenPosition())
				{
					LoseALife();
					break;
				}
			}
		}
	}
	if (isDrowning)
	{
		LoseALife();
		isDrowning = false;
	}	
	if (Lives == 0)
	{
		isAlive = false;
	}
	if (!isAlive)
	{
		GameOver(argWindow);
	}
	if (screenPos.y == 116.0f)
	{
		screenPos = { 400.0f, 500.0f };
		Score += argTimeLeft;
		argTimeLeft = 100;
	}
}

void Frog::LoseALife()
{
	Lives -= 1;
	if (Colour == sf::Color::Green)
		screenPos = { 200.0f, 500.0f };
	else if (Colour == sf::Color::Cyan)
		screenPos = { 400.0f, 500.0f };
	else if (Colour == sf::Color::Yellow)
		screenPos = { 600.0f, 500.0f };
}

void Frog::GameOver(sf::RenderWindow& argWindow)
{
	std::cout << "Game Over!" << std::endl;
}

void Frog::NewSegment(const int &argFoodValue)
{	
	Score += argFoodValue;
}

int Frog::GetScore()
{
	return Score;
}

int Frog::GetLives()
{
	return Lives;
}

sf::Color Frog::GetColor()
{
	return Colour;
}

void Frog::DoAnimation()
{
	if (animationFrameLeft > 0)
	{
		if (sprite.getTextureRect().left > 250)
		{
			sf::IntRect newSourceSprite = sprite.getTextureRect();
			if (sprite.getTextureRect().left == 400)
				newSourceSprite.left = 448;
			else
				newSourceSprite.left -= 24;
			sprite.setTextureRect(newSourceSprite);
		}
		else
		{
			sf::IntRect newSourceSprite = sprite.getTextureRect();
			if (sprite.getTextureRect().left == 16)
				newSourceSprite.left = 64;
			else
				newSourceSprite.left -= 24;
			sprite.setTextureRect(newSourceSprite);
		}
				
		animationFrameLeft -= 1;
	}
}

void Frog::ChangeToWaterSprite()
{
	if (screenPos.y < 308.0f && isOnLand)
	{
		sf::IntRect sourceSprite = sprite.getTextureRect();
		sourceSprite.left = 448;
		sprite.setTextureRect(sourceSprite);
		sprite.setOrigin({ 8.0f, 8.0f });
		isOnLand = false;
	}
	else if (screenPos.y >= 308.0f && !isOnLand)
	{
		sf::IntRect sourceSprite = sprite.getTextureRect();
		sourceSprite.left = 64;
		sprite.setTextureRect(sourceSprite);
		sprite.setOrigin({ 8.0f, 8.0f });
		isOnLand = true;
	}
	else if (screenPos.y <= 116.0f && !isOnLand)
	{
		sf::IntRect sourceSprite = sprite.getTextureRect();
		sourceSprite.left = 64;
		sprite.setTextureRect(sourceSprite);
		sprite.setOrigin({ 8.0f, 8.0f });
		isOnLand = true;
	}
}

void Frog::SelectClosestFood(Food &argFoodIndividual, const int& argFoodID)
{
}

void Frog::MoveToClosestFood(Food * argFoodArray[5], const std::list<Frog*> &argFrogPlayerList, const float& argWaterLimit)
{
}
