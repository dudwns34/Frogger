/*
  Games Development with C++ GAV1031-N
  Frog ICA start project 
  
  Set up to use the SFML 2.5.1 64-bit API
    SFML documentation: https://www.sfml-dev.org/learn.php
*/

// SFML header file for graphics, there are also ones for Audio, Window, System and Network
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"

int main()
{	
	bool playGame{ true };
	Game* myGame = new Game;
	do
	{
		myGame->ChangeState(playGame);
	} while (playGame);		
	delete myGame;
    return 0;
}