#pragma once

#include "Shape.h"

class Food : public Shape
{
private:
	int value{ 1 };
	
public:
	Food(const sf::Vector2f& argScreenPos, const bool& argIsAlive, const sf::Sprite& argSprite, const sf::Vector2f& argDimensions, const int& argValue);
	~Food();
	//void Render(sf::RenderWindow& argWindow) override;
	void SetToNotAlive();
	void SetToAlive();
	int GetFoodValue();
};

//POTENTIAL ADDITION:
//Air bubble