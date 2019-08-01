#pragma once
#include "Frog.h"
#include "Food.h"
#include "Vehicle.h"

class AI : public Frog
{
private:
	int closestFoodDistance = 9999;
	int closestFoodID = 9999;

	bool isAvoidingDeath{ false };	

public:
	AI(const sf::Vector2f& argScreenPos, const bool& argIsAlive, const sf::Sprite& argSprite, const sf::Vector2f& argDimensions);
	~AI();
	void Move() override;
	void SelectClosestFood(Food &argFoodIndividual, const int& argFoodID) override;	
	virtual void MoveToClosestFood(Food* argFoodArray[5], const std::list<Frog*> &argFrogPlayerList, const float& argWaterLimit) override;
	virtual void NewSegment(const int &argFoodValue) override;
	virtual void Update(const sf::Vector2f& argScreenPos, sf::RenderWindow& argWindow, const std::list<Frog*> &argFrogPlayerList, const std::list<Vehicle*> &argVehicleList, const std::list<RiverItem*> &argRiverItemList, int &argTimeLeft) override;
};

