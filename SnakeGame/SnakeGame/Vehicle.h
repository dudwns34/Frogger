#pragma once
#include "Shape.h"
#include <list>

enum class EVehicleType
{
	eTruck,
	eRacingCar,
	eStandardCar,
	eYellowCar,
	eBigWheelCar
};

class Vehicle : public Shape
{
private:
	float speed;
	EVehicleType vehicleType;

public:
	Vehicle(const sf::Vector2f& argScreenPos, const bool& argIsAlive, const sf::Sprite& argSprite, const sf::Vector2f& argDimensions, const float& argSpeed, const EVehicleType& argVehicleType);
	~Vehicle();
	virtual void Render(sf::RenderWindow& argWindow) override;
	void Move();
	void Update(const sf::Vector2f& argScreenPos);
	EVehicleType GetVehicleType();	
	void Spawn(const std::list<Vehicle*>& argVehicleList, const float& argSpawnDistance);
};
