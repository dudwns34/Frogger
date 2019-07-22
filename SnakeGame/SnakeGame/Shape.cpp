#include "Shape.h"

Shape::Shape(const sf::Vector2f& argScreenPos, const bool& argIsAlive, const sf::Sprite& argSprite, const sf::Vector2f& argDimensions) :
	screenPos(argScreenPos), isAlive(argIsAlive), sprite(argSprite), dimensions(argDimensions)
{
}

Shape::~Shape()
{
}

sf::Vector2f Shape::GetScreenPosition()
{
	return screenPos;
}

sf::Vector2f Shape::GetDimensions()
{
	return dimensions;
}

bool Shape::CheckIfAlive()
{
	return isAlive;
}

void Shape::ChangeAliveStatus()
{
	isAlive = !isAlive;
}
