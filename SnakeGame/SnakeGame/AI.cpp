#include "AI.h"



AI::AI(const sf::Vector2f& argScreenPos, const bool& argIsAlive, const sf::Sprite& argSprite, const sf::Vector2f& argDimensions) :
	Frog(argScreenPos, argIsAlive, argSprite, argDimensions)
{
}


AI::~AI()
{
}

void AI::Move()
{
	switch (direction)
	{
	case EDirection::eNorth:
		//std::cout << "I'm going up" << std::endl;
		screenPos.y -= dimensions.y * 2;
		break;
	case EDirection::eEast:
		//std::cout << "I'm going right" << std::endl;
		screenPos.x += dimensions.x * 2;
		break;
	case EDirection::eSouth:
		//std::cout << "I'm going down" << std::endl;
		screenPos.y += dimensions.y * 2;
		break;
	case EDirection::eWest:
		//std::cout << "I'm going left" << std::endl;
		screenPos.x -= dimensions.x * 2;
		break;
	default:
		break;
	}
}

void AI::SelectClosestFood(Food &argFoodIndividual, const int& argFoodID)
{
	//get and compare the head location to the food location
	sf::Vector2f locationCompare = screenPos - argFoodIndividual.GetScreenPosition();
	if (locationCompare.x < 0) { locationCompare.x = -locationCompare.x; }
	if (locationCompare.y < 0) { locationCompare.y = -locationCompare.y; }

	//find the distance to the food
	int finalDistance = locationCompare.x * 2 + locationCompare.y * 2;

	//if the distance is less than the current one then set the food as
	//the closest food. Also check if the food is alive
	if (finalDistance < closestFoodDistance && argFoodIndividual.CheckIfAlive())
	{ 
		closestFoodDistance = finalDistance;
		closestFoodID = argFoodID;
	}
}

void AI::MoveToClosestFood(Food * argFoodArray[5], const std::list<Frog*> &argFrogPlayerList, const float& argWaterLimit)
{
	if (!isAvoidingDeath)
	{
		float xDistance = screenPos.x - argFoodArray[closestFoodID]->GetScreenPosition().x;
		float yDistance = screenPos.y - argFoodArray[closestFoodID]->GetScreenPosition().y;
		if (xDistance < 0) { xDistance = -xDistance; }
		if (yDistance < 0) { yDistance = -yDistance; }		
		bool canGoUp{ true };
		bool canGoRight{ true };
		bool canGoDown{ true };
		bool canGoLeft{ true };	
		
		if (xDistance > yDistance)
		{
			if (argFoodArray[closestFoodID]->GetScreenPosition().x > screenPos.x)
			{
				//RIGHT
				if (direction != EDirection::eWest && canGoRight)
				{
					direction = EDirection::eEast;
				}
				if (direction == EDirection::eEast && !canGoRight)
				{
					if (canGoDown)
					{
						direction = EDirection::eSouth;
					}
					else if (canGoUp)
					{
						direction = EDirection::eNorth;
					}
				}
			}
			else
			{
				//LEFT
				if (direction != EDirection::eEast && canGoLeft)
				{
					direction = EDirection::eWest;
				}
				if (direction == EDirection::eWest && !canGoLeft)
				{
					if (canGoDown)
					{
						direction = EDirection::eSouth;
					}
					else if (canGoUp)
					{
						direction = EDirection::eNorth;
					}
				}
			}
		}
		else
		{
			if (argFoodArray[closestFoodID]->GetScreenPosition().y > screenPos.y)
			{
				if (direction != EDirection::eNorth && canGoDown)
				{
					direction = EDirection::eSouth;
				}
				if (direction == EDirection::eSouth && !canGoDown)
				{
					if (canGoRight)
					{
						direction = EDirection::eEast;
					}
					else if (canGoLeft)
					{
						direction = EDirection::eWest;
					}
				}
			}
			else
			{
				if (direction != EDirection::eSouth && canGoUp)
				{
					direction = EDirection::eNorth;
				}
				if (direction == EDirection::eNorth && !canGoUp)
				{
					if (canGoRight)
					{
						direction = EDirection::eEast;
					}
					else if (canGoLeft)
					{
						direction = EDirection::eWest;
					}
				}
			}
		}
	}
	isAvoidingDeath = false;
}

void AI::NewSegment(const int &argFoodValue)
{
	Score += argFoodValue;
	closestFoodDistance = 9999;
}

void AI::Update(const sf::Vector2f & argScreenPos, sf::RenderWindow & argWindow, const std::list<Frog*>& argFrogPlayerList, const std::list<Vehicle*> &argVehicleList)
{
	//Checks if the Frog has gone off the screen
	if (screenPos.x < -dimensions.x || screenPos.x > argScreenPos.x - dimensions.x * 2)
	{
		isAlive = false;
	}
	if (screenPos.y < 0 || screenPos.y > argScreenPos.y - dimensions.y * 2)
	{
		isAlive = false;
	}
	//Check if the Frog is close to the edge
	//Only do it if no direction has been overriten
	if (!isAvoidingDeath)
	{
		if (screenPos.x == 20.0f)
		{
			if (rand() % 4 != 0)
			{
				std::cout << "Close to the left!" << std::endl;
				if (direction != EDirection::eNorth && direction != EDirection::eSouth)
				{
					int decideDirection = rand() % 2;
					if (decideDirection == 0)
					{
						std::cout << "Going up" << std::endl;
						direction = EDirection::eNorth;
					}
					else if(decideDirection == 1)
					{
						direction = EDirection::eSouth;
					}
				}
				isAvoidingDeath = true;
			}
		}
		if (screenPos.x == 800.0f - 20.0f)
		{
			if (rand() % 4 != 0)
			{
				std::cout << "Close to the right!" << std::endl;
				if (direction != EDirection::eNorth && direction != EDirection::eSouth)
				{
					int decideDirection = rand() % 2;
					if (decideDirection == 0)
					{
						std::cout << "Going up" << std::endl;
						direction = EDirection::eNorth;
					}
					else if(decideDirection == 1)
					{
						direction = EDirection::eSouth;
					}
				}
				isAvoidingDeath = true;
			}
		}
		if (screenPos.y == 600.0f - 20.0f)
		{
			if (rand() % 4 != 0)
			{
				std::cout << "Close to the bottom" << std::endl;
				if (direction != EDirection::eEast && direction != EDirection::eWest)
				{
					int decideDirection = rand() % 2;
					if (decideDirection == 0)
					{
						std::cout << "Going right" << std::endl;
						direction = EDirection::eEast;
					}
					else if(decideDirection == 1)
					{
						direction = EDirection::eWest;
					}
				}
				isAvoidingDeath = true;
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
				if (GetScreenPosition() == player->GetScreenPosition())
				{
					isAlive = false;											
					break;
				}				
			}
		}

	}
	if (!isAlive)
	{
		GameOver(argWindow);
	}
}
