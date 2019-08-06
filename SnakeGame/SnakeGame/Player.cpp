#include "Player.h"

Player::Player(const sf::Vector2f& argScreenPos, const bool& argIsAlive, const sf::Sprite& argSprite, const sf::Vector2f& argDimensions, const sf::Color& argColour, const int& argPlayerController):
	Frog(argScreenPos, argIsAlive, argSprite, argDimensions, argColour), playerController(argPlayerController)
{
}

Player::~Player()
{
}

void Player::Move()
{	
	sf::IntRect rectSourceSprite;
	switch (playerController)
	{
	case 1:
		if (canMove)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				direction = EDirection::eNorth;
				screenPos.y -= dimensions.y;
				//do the animation				
				sprite.setRotation(0.0f);

				animationFrameLeft = 3;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				direction = EDirection::eEast;
				screenPos.x += dimensions.x;
				//do the animation
				sprite.setRotation(90.0f);
				animationFrameLeft = 3;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				direction = EDirection::eSouth;
				screenPos.y += dimensions.y;
				//do the animation
				sprite.setRotation(180.0f);
				animationFrameLeft = 3;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				direction = EDirection::eWest;
				screenPos.x -= dimensions.x;
				//do the animation
				sprite.setRotation(270.0f);
				animationFrameLeft = 3;
			}
			canMove = false;
		}		
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
			!sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			canMove = true;
		break;
	case 2:
		if (canMove)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
			{		
				direction = EDirection::eNorth;
				screenPos.y -= dimensions.y;
				//do the animation				
				sprite.setRotation(0.0f);

				animationFrameLeft = 3;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
			{
				direction = EDirection::eEast;
				screenPos.x += dimensions.x;
				//do the animation
				sprite.setRotation(90.0f);
				animationFrameLeft = 3;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
			{
				direction = EDirection::eSouth;
				screenPos.y += dimensions.y;
				//do the animation
				sprite.setRotation(180.0f);
				animationFrameLeft = 3;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
			{
				direction = EDirection::eWest;
				screenPos.x -= dimensions.x;
				//do the animation
				sprite.setRotation(270.0f);
				animationFrameLeft = 3;
			}
			canMove = false;
		}
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::I) && !sf::Keyboard::isKeyPressed(sf::Keyboard::L) &&
			!sf::Keyboard::isKeyPressed(sf::Keyboard::K) && !sf::Keyboard::isKeyPressed(sf::Keyboard::J))
			canMove = true;
		break;
	case 3:
		if (canMove)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				direction = EDirection::eNorth;
				screenPos.y -= dimensions.y;
				//do the animation				
				sprite.setRotation(0.0f);

				animationFrameLeft = 3;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				direction = EDirection::eEast;
				screenPos.x += dimensions.x;
				//do the animation
				sprite.setRotation(90.0f);
				animationFrameLeft = 3;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				direction = EDirection::eSouth;
				screenPos.y += dimensions.y;
				//do the animation
				sprite.setRotation(180.0f);
				animationFrameLeft = 3;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				direction = EDirection::eWest;
				screenPos.x -= dimensions.x;
				//do the animation
				sprite.setRotation(270.0f);
				animationFrameLeft = 3;
			}
			canMove = false;
		}
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
			!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			canMove = true;
		break;
	default:
		break;
	}			
}
