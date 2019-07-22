#pragma once
// SFML header file for graphics, there are also ones for Audio, Window, System and Network
#include <SFML/Graphics.hpp>
#include <iostream>

class Shape
{
protected:
	sf::Vector2f screenPos;;	
	bool isAlive;
	sf::Sprite sprite;
	sf::Vector2f dimensions;

public:
	Shape(const sf::Vector2f& argScreenPos, const bool& argIsAlive, const sf::Sprite& argSprite, const sf::Vector2f& argDimensions);
	~Shape();
	virtual void Render(sf::RenderWindow& argWindow) = 0;
	sf::Vector2f GetScreenPosition();
	sf::Vector2f GetDimensions();
	bool CheckIfAlive();
	void ChangeAliveStatus();
};

//for the render, you could use a template to substitute the radius/dimensions
