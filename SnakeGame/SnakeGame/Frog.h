#pragma once
#include "Shape.h"
#include "Vehicle.h"
#include "Food.h"
#include <list>

enum class EDirection
{
	eNorth,	
	eEast,
	eSouth,
	eWest,
	//eStop
};

class Frog : public Shape
{
protected:
	int animationFrameLeft{ 0 };
	bool isOnLand{ true };
	int Score{ 0 };
	EDirection direction = EDirection::eNorth;

public:
	Frog(const sf::Vector2f& argScreenPos, const bool& argIsAlive, const sf::Sprite& argSprite, const sf::Vector2f& argDimensions);
	~Frog();
	virtual void Render(sf::RenderWindow& argWindow) override;

	virtual void Move() = 0;
	virtual void Update(const sf::Vector2f& argScreenPos, sf::RenderWindow& argWindow, const std::list<Frog*> &argFrogPlayerList, const std::list<Vehicle*> &argVehicleList);
	void GameOver(sf::RenderWindow& argWindow);
	virtual void NewSegment(const int &argFoodValue);
	int GetScore();	

	void DoAnimation();
	void ChangeToWaterSprite();

	virtual void SelectClosestFood(Food &argFoodIndividual, const int& argFoodID);
	virtual void MoveToClosestFood(Food* argFoodArray[5], const std::list<Frog*> &argFrogPlayerList, const float& argWaterLimit);

};

//Implement the new segment function in here
//Add movement function in here
