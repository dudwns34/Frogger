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
#include <fstream>

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
	sf::Clock timeClock;
	int TimeLeft{ 100 };

	bool areAllDead{ false };

	std::list<Frog*> FrogPlayerList;
	std::list<Vehicle*> VehicleList;
	std::list<RiverItem*> RiverItemList;

	EGameState m_currentState{ EGameState::eMainMenu };	
	
public:
	Game();
	~Game();
	void ChangeState(bool& argPlayGame);

	void Run(sf::RenderWindow &argWindow);
	template<class T>
	void ObjectFrameCycle(sf::RenderWindow& argWindow, std::list<T> &ObjectList);
	template<class T>
	void SpawnNewObject(int spawnDistance, std::list<T> &ObjectList);
	void InitialObjectSpawn();
	void CreatePoolOfObjects(sf::Texture& texture);

	void DisplayMainMenu(sf::RenderWindow &argWindow);
	void CreateText(sf::Text& argText, const sf::Font& argFont, const sf::String& argString, const int& argCharSize, const sf::Color& argColor, const sf::Vector2f& argPosition);
	bool DisplayGameOver(sf::RenderWindow &argWindow);
	
	void NewPlayer(std::list<Frog*> &argFrogPlayerList, const int& playerNumber, const sf::Texture &argTexture);
	void spawnFood(Food* &argF);
	void DisplayUI(sf::RenderWindow &argWindow, const std::list<Frog*> &argFrogPlayerList);
	void Water(sf::RenderWindow& argWindow);
};




