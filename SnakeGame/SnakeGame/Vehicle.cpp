#include "Vehicle.h"

Vehicle::Vehicle(const sf::Vector2f& argScreenPos, const bool& argIsAlive, const sf::Sprite& argSprite, const sf::Vector2f& argDimensions, const float& argSpeed, const EVehicleType& argVehicleType) :
	Shape(argScreenPos, argIsAlive, argSprite, argDimensions), speed(argSpeed), vehicleType(argVehicleType)
{	
}

Vehicle::~Vehicle()
{
}

void Vehicle::Render(sf::RenderWindow& argWindow)
{
	if (isAlive)
	{
		// Create an instance of the SFML CircleShape and initialise it
		sprite.setPosition(screenPos);
		// Set the shape's fill colour attribute

		//shape.setOutlineThickness(10.f);
		//shape.setOutlineColor(sf::Color(250, 150, 100));

		// draw our circle shape to the window
		argWindow.draw(sprite);
	}
}

void Vehicle::Move()
{
	screenPos.x -= speed;
}

void Vehicle::Update(const sf::Vector2f& argScreenPos)
{
	//Checks if the Vehicle has gone off the screen
	if (vehicleType == EVehicleType::eTruck || vehicleType == EVehicleType::eRacingCar || vehicleType == EVehicleType::eStandardCar)
	{
		//THESE GO TO THE LEFT
		if (screenPos.x < -dimensions.x)
		{
			isAlive = false;
			//Reposition the vehicle
			screenPos.x = argScreenPos.x;
		}
	}
	else if (vehicleType == EVehicleType::eBigWheelCar || vehicleType == EVehicleType::eYellowCar)
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

EVehicleType Vehicle::GetVehicleType()
{
	return vehicleType;
}

void Vehicle::Spawn(const std::list<Vehicle*>& argVehicleList, const float& argSpawnDistance)
{
	//all vehicles are spawning at the same time
	bool canSpawn{ false };
	for (Vehicle* otherVehicle : argVehicleList)
	{
		if (this != otherVehicle)
		{
			if (otherVehicle->CheckIfAlive())
			{
				if (GetVehicleType() == otherVehicle->GetVehicleType())
				{
					//checks if it is not within the dimensions of the vehicle times the distance established
					if (screenPos.x <= otherVehicle->GetScreenPosition().x - (argSpawnDistance * dimensions.x) ||
						screenPos.x >= otherVehicle->GetScreenPosition().x + (argSpawnDistance * dimensions.x))
					{	
						canSpawn = true;
					}
					//checks if it is within the dimensions of the vehicle times the distance establised
					else if (screenPos.x > otherVehicle->GetScreenPosition().x - (argSpawnDistance * dimensions.x) &&
							 screenPos.x < otherVehicle->GetScreenPosition().x + (argSpawnDistance * dimensions.x))
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