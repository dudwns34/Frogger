#pragma once

// SFML header file for graphics, there are also ones for Audio, Window, System and Network
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Frog.h"
#include "Vehicle.h"
#include "RiverItem.h"
#include "Player.h"
#include "AI.h"
#include <list>

enum class EGameState
{
	eMainMenu,
	eRunGame,
	eGameOver
};

class Game
{
private:
	//these values are constant most likely
	sf::Vector2f screenSize;
	sf::Clock masterClock;

	bool areAllDead{ false };

	std::list<Frog*> FrogPlayerList;
	std::list<Vehicle*> VehicleList;
	std::list<RiverItem*> RiverItemList;

	EGameState m_currentState{ EGameState::eMainMenu };	
	
public:
	Game();
	~Game();
	void ChangeState(bool& argPlayGame);

	//Consider the enum for the different screen modes (main menu, game, game over)
	void Run(sf::RenderWindow &argWindow);	
	void DisplayMainMenu(sf::RenderWindow &argWindow);
	bool DisplayGameOver(sf::RenderWindow &argWindow);
	
	void NewPlayer(std::list<Frog*> &argFrogPlayerList, const int& playerNumber, const sf::Texture &argTexture);
	void spawnFood(Food* &argF);
	void DisplayUI(sf::RenderWindow &argWindow, const std::list<Frog*> &argFrogPlayerList);
	void Water(sf::RenderWindow& argWindow);
};




