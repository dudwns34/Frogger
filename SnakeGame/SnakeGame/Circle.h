#pragma once
#include "Shape.h"

class Circle : public Shape
{
private:
	float radius;

public:
	Circle(const sf::Vector2f& argScreenPos, const sf::Color& argColour, const float& argRadius);
	~Circle();
	void Render(sf::RenderWindow& argWindow) override;
	void Update(const sf::Vector2f& argScreenPos, sf::RenderWindow& argWindow) override;
	void GameOver(sf::RenderWindow& argWindow) override;

};

