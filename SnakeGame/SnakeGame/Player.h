#pragma once
#include "Frog.h"
class Player: public Frog
{
private:
	int playerController;
	bool canMove{ true };

public:
	Player(const sf::Vector2f& argScreenPos, const bool& argIsAlive, const sf::Sprite& argSprite, const sf::Vector2f& argDimensions, const int& argPlayerController);
	~Player();
	void Move() override;
	
};