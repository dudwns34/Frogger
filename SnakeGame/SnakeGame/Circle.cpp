#include "Circle.h"

Circle::Circle(const sf::Vector2f& argScreenPos, const sf::Color& argColour, const float& argRadius) :
	Shape(argScreenPos, argColour), radius(argRadius)
{
}

Circle::~Circle()
{
}

void Circle::Render(sf::RenderWindow& argWindow)
{
	// Create an instance of the SFML CircleShape and initialise it
	sf::CircleShape shape(radius);
	shape.setPosition(screenPos);
	// Set the shape's fill colour attribute
	shape.setFillColor(colour);
	shape.setOutlineThickness(10.f);
	shape.setOutlineColor(sf::Color(250, 150, 100));
	// draw our circle shape to the window
	argWindow.draw(shape);
}

void Circle::Update(const sf::Vector2f& argScreenPos, sf::RenderWindow& argWindow)
{
	if (screenPos.x < 0 || screenPos.x > argScreenPos.x - radius * 2)
	{
		isDead = true;
	}
	if (screenPos.y < 0 || screenPos.y > argScreenPos.y - radius * 2)
	{
		isDead = true;
	}
	if (isDead)
	{
		GameOver(argWindow);
	}
}

void Circle::GameOver(sf::RenderWindow& argWindow)
{
	std::cout << "Game Over!" << std::endl;
	argWindow.close();
}
