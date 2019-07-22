#include "Food.h"

Food::Food(const sf::Vector2f& argScreenPos, const bool& argIsAlive, const sf::Sprite& argSprite, const sf::Vector2f& argDimensions, const int& argValue) :
	Shape(argScreenPos, argIsAlive, argSprite, argDimensions), value(argValue)
{
}


Food::~Food()
{
}

//void Food::Render(sf::RenderWindow & argWindow)
//{		
//}

void Food::SetToNotAlive()
{	
	screenPos = { (rand() % 40) * 20.0f, (rand() % 30) * 20.0f };
	isAlive = false;
}

void Food::SetToAlive()
{
	isAlive = true;
}

int Food::GetFoodValue()
{
	return value;
}
