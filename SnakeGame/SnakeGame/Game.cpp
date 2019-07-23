#include "Game.h"
#include <string>
#include <list>

Game::Game()
{ 
	//this can be changed later to get rid of magic numbers
	screenSize = { 800.0f, 600.0f };
	srand(static_cast<unsigned int>(time(0)));		

}

Game::~Game()
{
}

void Game::ChangeState(bool& argPlayGame)
{
	sf::RenderWindow window(sf::VideoMode((int)screenSize.x, (int)screenSize.y), "Frogger");
	switch (m_currentState)
	{
	case EGameState::eMainMenu:
		//Display menu, wait for input
		DisplayMainMenu(window);		
		break;
	case EGameState::eRunGame:
		Run(window);
		break;
	case EGameState::eGameOver:	
		argPlayGame = DisplayGameOver(window);
		break;
	default:
		break;
	}
}

void Game::Run(sf::RenderWindow &argWindow)
{
	//create a sprite
	sf::Texture texture;
	texture.loadFromFile("GeneralRip.png");
	
	masterClock.restart();
	for (int i = 0; i < 1; i++)
	{
		//Add a new player frog. One for now
		NewPlayer(FrogPlayerList, i, texture);
	}

	for (size_t i = 0; i < 40; i++)
	{
		//create all the vehicles. A pool of vehicles
		int randomType = rand() % 5;
		//create values for the sprite for the vehicles
		sf::IntRect rectSourceSprite;	//margin is 16x16
		sf::Sprite sprite(texture, rectSourceSprite);
		switch (randomType)
		{
		// these following ones will be going from right to left
		case 0:	//TRUCK	
			rectSourceSprite = sf::IntRect(66, 336, 32, 16);
			sprite = sf::Sprite(texture, rectSourceSprite);
			sprite.setScale({ 2.0f, 2.0f });
			sprite.setOrigin({ 16.0f, 8.0f });
			VehicleList.push_back(new Vehicle({ 800.0f, 372.0f }, false, sprite, { 64.0f, 32.0f }, 0.2f, EVehicleType::eTruck));
			break;
		case 1:	//RACING CAR
			rectSourceSprite = sf::IntRect(40, 336, 16, 16);
			sprite = sf::Sprite(texture, rectSourceSprite);
			sprite.setScale({ 2.0f, 2.0f });
			sprite.setOrigin({ 8.0f, 8.0f });
			VehicleList.push_back(new Vehicle({ 800.0f, 404.0f }, false, sprite, { 32.0f, 32.0f }, 0.4f, EVehicleType::eRacingCar));
			break;
		case 2:	//STANDARD CAR
			rectSourceSprite = sf::IntRect(104, 336, 16, 16);
			sprite = sf::Sprite(texture, rectSourceSprite);
			sprite.setScale({ 2.0f, 2.0f });
			sprite.setOrigin({ 8.0f, 8.0f });
			VehicleList.push_back(new Vehicle({ 800.0f, 468.0f }, false, sprite, { 32.0f, 32.0f }, 0.3f, EVehicleType::eStandardCar));
			break;
		// these following ones will be going from left to right
		case 3: //BIG WHEEL CAR
			rectSourceSprite = sf::IntRect(128, 336, 16, 16);
			sprite = sf::Sprite(texture, rectSourceSprite);
			sprite.setScale({ 2.0f, 2.0f });
			sprite.setOrigin({ 8.0f, 8.0f });
			VehicleList.push_back(new Vehicle({ 0.0f, 436.0f }, false, sprite, { 32.0f, 32.0f }, -0.2f, EVehicleType::eBigWheelCar));
			break;
		case 4: //YELLOW CAR
			rectSourceSprite = sf::IntRect(16, 336, 16, 16);
			sprite = sf::Sprite(texture, rectSourceSprite);
			sprite.setScale({ 2.0f, 2.0f });
			sprite.setOrigin({ 8.0f, 8.0f });
			VehicleList.push_back(new Vehicle({ 0.0f, 340.0f }, false, sprite, { 32.0f, 32.0f }, -0.3f, EVehicleType::eYellowCar));
			break;
		default:
			break;
		}		
	}

	//create the pool of riverItems and spawn them just like the vehicles
	for (size_t i = 0; i < 50; i++)
	{
		//create all the river items. A pool of river items
		int randomType = rand() % 2;
		int randomPosition;
		//create values for the sprite for the river items
		sf::IntRect rectSourceSprite;	//margin is 16x16
		sf::Sprite sprite(texture, rectSourceSprite);
		switch (randomType)
		{
		case 0://LOG
			rectSourceSprite = sf::IntRect(496, 304, 48, 16);
			sprite = sf::Sprite(texture, rectSourceSprite);
			sprite.setScale({ 2.0f, 2.0f });
			sprite.setOrigin({ 24.0f, 8.0f });
			randomPosition = rand() % 3;
			switch (randomPosition)
			{
			case 0:
				RiverItemList.push_back(new RiverItem({ 800.0f, 244.0f }, false, sprite, { 96.0f, 32.0f }, 0.2f, ERiverItemType::eLog));
				continue;
			case 1:
				RiverItemList.push_back(new RiverItem({ 0.0f, 212.0f }, false, sprite, { 96.0f, 32.0f }, -0.2f, ERiverItemType::eLog));
				continue;
			case 2:
				RiverItemList.push_back(new RiverItem({ 800.0f, 148.0f }, false, sprite, { 96.0f, 32.0f }, 0.2f, ERiverItemType::eLog));
				continue;
			default:
				continue;
			}			
			break;
		case 1://TURTLE
			rectSourceSprite = sf::IntRect(432, 145, 16, 16);
			sprite = sf::Sprite(texture, rectSourceSprite);
			sprite.setScale({ 2.0f, 2.0f });
			sprite.setOrigin({ 8.0f, 8.0f });
			randomPosition = rand() % 2;
			switch (randomPosition)
			{
			case 0:
				RiverItemList.push_back(new RiverItem({ 800.0f, 276.0f }, false, sprite, { 32.0f, 32.0f }, 0.2f, ERiverItemType::eTurtle));
				continue;
			case 1:
				RiverItemList.push_back(new RiverItem({ 0.0f, 180.0f }, false, sprite, { 32.0f, 32.0f }, -0.2f, ERiverItemType::eTurtle));
				continue;
			default:
				continue;
			}
			break;	
		default:
			break;
		}
	}

	//for the initial cars when run is initiated. Only one of each will be set to alive.
	bool oneTruckAlive{ false }, oneRacingAlive{ false }, oneStandardAlive{ false }, oneBigWheelAlive{ false }, oneYellowAlive{ false };
	for (Vehicle* vehicle : VehicleList)
	{
		switch (vehicle->GetVehicleType())
		{
		case EVehicleType::eTruck:
			if (!oneTruckAlive)
			{
				vehicle->ChangeAliveStatus();
				oneTruckAlive = true;
			}
			continue;
		case EVehicleType::eRacingCar:
			if (!oneRacingAlive)
			{
				vehicle->ChangeAliveStatus();
				oneRacingAlive = true;
			}
			continue;
		case EVehicleType::eStandardCar:
			if (!oneStandardAlive)
			{
				vehicle->ChangeAliveStatus();
				oneStandardAlive = true;
			}
			continue;
		case EVehicleType::eBigWheelCar:
			if (!oneBigWheelAlive)
			{
				vehicle->ChangeAliveStatus();
				oneBigWheelAlive = true;
			}
			continue;
		case EVehicleType::eYellowCar:
			if (!oneYellowAlive)
			{
				vehicle->ChangeAliveStatus();
				oneYellowAlive = true;
			}
			continue;
		default:
			continue;
		}
	}
	bool oneLogAlive{ false }, oneTurtleAlive{ false };
	for (RiverItem* riverItem : RiverItemList)
	{
		switch (riverItem->GetRiverItemType())
		{
		case ERiverItemType::eLog:
			if (!oneLogAlive)
			{
				riverItem->ChangeAliveStatus();
				oneLogAlive = true;
			}
			continue;
		case ERiverItemType::eTurtle:
			if (!oneTurtleAlive)
			{
				riverItem->ChangeAliveStatus();
				oneTurtleAlive = true;
			}
			continue;
		default:
			continue;
		}
	}
	// We can still output to the console window
	std::cout << "Frogger: Starting" << std::endl;

	// Main loop that continues until we call window.close()
	while (argWindow.isOpen())
	{
		// Handle any pending SFML events
		// These cover keyboard, mouse,joystick etc.
		sf::Event event;
		while (argWindow.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				argWindow.close();
				break;
			default:
				break;
			}
		}
		// We must clear the window each time around the loop
		argWindow.clear();		
		//Water displayed
		Water(argWindow);
		//UI Displayed
		DisplayUI(argWindow, FrogPlayerList);	
		for (RiverItem* riverItem : RiverItemList)
		{
			if (riverItem->CheckIfAlive())
			{
				riverItem->Render(argWindow);
				riverItem->Update(screenSize);
				riverItem->Move();
			}
		}
		for (Frog* player : FrogPlayerList)
		{		
			if (player->CheckIfAlive())
			{				
				player->Render(argWindow);
				player->Update(screenSize, argWindow, FrogPlayerList, VehicleList, RiverItemList);	//This checks for collisions
				player->Move();	
				player->ChangeToWaterSprite();
			}						
		}	
		for (Vehicle* vehicle : VehicleList)
		{
			if (vehicle->CheckIfAlive())
			{
				vehicle->Render(argWindow);
				vehicle->Update(screenSize);
				vehicle->Move();
			}
		}		
		// Get the window to display its contents
		argWindow.display();
		areAllDead = true;
		for (Frog* player : FrogPlayerList)
		{			
			if (player->CheckIfAlive())
			{
				areAllDead = false;
			}
		}		
		if (masterClock.getElapsedTime().asMilliseconds() > 500)
		{
			for (Frog* player : FrogPlayerList)
			{
				player->DoAnimation();
			}
			//Every half a seconds change the spawnDistance value
			int spawnDistance = rand() % 3;
			masterClock.restart();
			for (Vehicle* vehicle : VehicleList)
			{
				if (!vehicle->CheckIfAlive())
				{
					// spawn the vehicle with the random spawn distance
					switch (spawnDistance)
					{
					case 0:
						vehicle->SpawnVehicle(VehicleList, 1.0f);
						continue;
					case 1:
						vehicle->SpawnVehicle(VehicleList, 4.0f);
						continue;
					case 2:
						vehicle->SpawnVehicle(VehicleList, 8.0f);
						continue;
					default:
						continue;
					}
				}
			}
			for (RiverItem* riverItem : RiverItemList)
			{
				// spawn the river item with the random spawn distance
				if (!riverItem->CheckIfAlive())
				{
					switch (spawnDistance)
					{
					case 0:
						riverItem->SpawnRiverItem(RiverItemList, 1.0f);
						continue;
					case 1:
						riverItem->SpawnRiverItem(RiverItemList, 4.0f);
						continue;
					case 2:
						riverItem->SpawnRiverItem(RiverItemList, 8.0f);
						continue;
					default:
						continue;
					}
				}				
			}
		}			
		
		if (areAllDead)
		{
			//change the state to game over
			m_currentState = EGameState::eGameOver;				
			argWindow.clear();
			for (Vehicle* vehicle : VehicleList)
			{
				delete vehicle;
			}
			for (RiverItem* riverItem : RiverItemList)
			{
				delete riverItem;
			}
			break;
		}
	}

	std::cout << "FrogGame: Finished" << std::endl;	
}

void Game::DisplayMainMenu(sf::RenderWindow &argWindow)
{
	//Declare and load a font
	sf::Font font;	
	//it has a problem loading the text!!
	if (!font.loadFromFile("PressStart2P.ttf"))
	{
		std::cout << "Error loading the font file." << std::endl;
	}
	sf::Clock clock;
	//Create a textTitle and tip
	sf::Text textTitle, textTip;
	textTitle.setFont(font);
	textTitle.setString("FROGGER");
	textTitle.setCharacterSize(30);
	textTitle.setStyle(sf::Text::Regular);
	textTitle.setFillColor(sf::Color::Green);
	textTitle.setPosition(250.0f, 50.0f);

	textTip.setFont(font);
	textTip.setString("Press Space to select the option");
	textTip.setCharacterSize(18);
	textTip.setStyle(sf::Text::Regular);
	textTip.setFillColor(sf::Color(255, 165, 0));
	textTip.setPosition(100.0f, 500.0f);

	//create a sprite
	sf::Texture texture;
	texture.loadFromFile("GeneralRip.png");

	sf::IntRect rectSourceSprite(64, 16, 16, 16);	//margin is 16x16
	sf::Sprite sprite(texture, rectSourceSprite);
	sprite.scale(sf::Vector2f(5.0f, 5.0f));	//2.5f is a considerable size for the game
	sprite.setPosition(500.0f, 25.0f);

	// this is for sprite testing purposes
	/*sf::RectangleShape testingRectangle({ 200.0f,100.0f });
	testingRectangle.setFillColor(sf::Color::White);
	testingRectangle.setPosition({ 495.0f, 20.0f });*/

	const int noOfOptions{ 2 };	
	int optionIndex{ 0 };		
	sf::Text textOptions[noOfOptions];	
	
	
	for (int i = 0; i < noOfOptions; i++)
	{
		textOptions[i].setFont(font);
		textOptions[i].setCharacterSize(18);
		textOptions[i].setStyle(sf::Text::Regular);
		textOptions[i].setFillColor(sf::Color(255, 165, 0));
		switch (i)
		{
		case 0:
			textOptions[i].setString("Single Player");
			textOptions[i].setPosition(250.0f, 150.0f);			
			break;
		case 1:
			textOptions[i].setString("Highscore");
			textOptions[i].setPosition(250.0f, 200.0f);
			break;		
		default:
			break;
		}
		//this lets the player know which option is selected
		textOptions[optionIndex].setOutlineColor(sf::Color::White);
		textOptions[optionIndex].setOutlineThickness(2.0f);
	}

	while (argWindow.isOpen())
	{
		// Handle any pending SFML events
		// These cover keyboard, mouse,joystick etc.
		sf::Event event;
		while (argWindow.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
					//fix so that the player doesn't click any button and it closes
				{				
				case sf::Keyboard::W:					
					textOptions[optionIndex].setOutlineThickness(0.0f);
					optionIndex--;
					if (optionIndex < 0) { optionIndex = noOfOptions - 1; }
					textOptions[optionIndex].setOutlineColor(sf::Color::White);
					textOptions[optionIndex].setOutlineThickness(2.0f);
					continue;
				case sf::Keyboard::S:
					textOptions[optionIndex].setOutlineThickness(0.0f);
					optionIndex++;
					if (optionIndex > noOfOptions - 1) { optionIndex = 0; }
					textOptions[optionIndex].setOutlineColor(sf::Color::White);
					textOptions[optionIndex].setOutlineThickness(2.0f);
					continue;
				case sf::Keyboard::Space:					
					//if the player is on the button of "Play game then go straight to the game"
					if (optionIndex == 0)
					{						
						m_currentState = EGameState::eRunGame;																								
						break;
					}
					continue;
				default:
					continue;
				}
			case sf::Event::Closed:
				argWindow.close();
				break;
			default:
				break;
			}			
		}
		//this is for the frog sprite
		if (clock.getElapsedTime().asMilliseconds() > 150.0f)
		{
			if (rectSourceSprite.left == 16)
				rectSourceSprite.left = 64;
			else
				rectSourceSprite.left -= 24;
			sprite.setTextureRect(rectSourceSprite);
			clock.restart();
		}
		//Clear the content of the window every frame
		argWindow.clear();

		//Draw the text
		argWindow.draw(textTitle);
		argWindow.draw(textTip);
		//argWindow.draw(testingRectangle);
		argWindow.draw(sprite);
		for (int i = 0; i < noOfOptions; i++)
		{
			argWindow.draw(textOptions[i]);
		}

		// Get the window to display its contents
		argWindow.display();		
	}
}

bool Game::DisplayGameOver(sf::RenderWindow & argWindow)
{
	bool isPlayingAgain = false;
	int topScore{-1};	
	int playerNumber{ 0 };
	int winnerNumber{0};
	sf::Color winnerColor{ sf::Color::White };
	//Declare and load a font
	sf::Font font;
	//it has a problem loading the text!!
	if (!font.loadFromFile("PressStart2P.ttf"))
	{
		std::cout << "Error loading the font file." << std::endl;
	}

	//Create a textTite
	sf::Text textTitle;
	textTitle.setFont(font);
	textTitle.setString("Game Over!");
	textTitle.setCharacterSize(30);
	textTitle.setStyle(sf::Text::Regular);
	textTitle.setFillColor(sf::Color::Red);
	textTitle.setPosition(200.0f, 50.0f);

	for (Frog* player : FrogPlayerList)
	{	
		if (player->GetScore() > topScore)
		{
			topScore = player->GetScore();	
			winnerNumber = playerNumber;
			winnerColor = sf::Color::Green;
		}
		playerNumber++;
		//also you will have to display which Frog had the top score
	}
	//Create a text for the highest score
	sf::Text textTopScore;
	textTopScore.setFont(font);
	textTopScore.setString("Top Score: P" + std::to_string(winnerNumber + 1) + " " + std::to_string(topScore));
	textTopScore.setCharacterSize(30);
	textTopScore.setStyle(sf::Text::Regular);
	textTopScore.setFillColor(winnerColor);
	/*textTopScore.setOutlineColor(sf::Color::White);
	textTopScore.setOutlineThickness(2.0f);*/
	textTopScore.setPosition(200.0f, 200.0f);

	//Create a textIndication
	sf::Text textIndication;
	textIndication.setFont(font);
	textIndication.setString("Press Space to go back to the main menu");
	textIndication.setCharacterSize(18);
	textIndication.setStyle(sf::Text::Regular);
	textIndication.setFillColor(sf::Color(255, 165, 0));	//This is orange
	textIndication.setPosition(50.0f, 350.0f);

	//create a textExit
	sf::Text textExit;
	textExit.setFont(font);
	textExit.setString("Press Escape to exit the game");
	textExit.setCharacterSize(18);
	textExit.setStyle(sf::Text::Regular);
	textExit.setFillColor(sf::Color(255, 165, 0));
	textExit.setPosition(100.0f, 450.0f);

	while (argWindow.isOpen())
	{
		// Handle any pending SFML events
		// These cover keyboard, mouse,joystick etc.
		sf::Event event;
		while (argWindow.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{	
				case sf::Keyboard::Escape:
					argWindow.close();
					isPlayingAgain = false;
					break;
				case sf::Keyboard::Space:
					isPlayingAgain = true;
					m_currentState = EGameState::eMainMenu;
					//reset values. consider also resetting the water level. 
					for (Frog* player : FrogPlayerList)
					{
						delete player;
					}
					FrogPlayerList.clear();
					argWindow.close();										
					break;
				default:
					continue;
				}
			case sf::Event::Closed:
				argWindow.close();
				break;
			default:
				break;
			}
		}
		//Clear the content of the window every frame
		argWindow.clear();

		//Draw the text
		argWindow.draw(textTitle);
		argWindow.draw(textTopScore);
		argWindow.draw(textIndication);
		argWindow.draw(textExit);

		// Get the window to display its contents
		argWindow.display();

	}
	return isPlayingAgain;
}

void Game::NewPlayer(std::list<Frog*> &argFrogPlayerList, const int &playerNumber, const sf::Texture &argTexture)
{
	sf::Vector2f position;
	switch (playerNumber)
	{
	case 0:
		position = { 400.0f, 500.0f };
		break;	
	default:
		break;
	}
	sf::IntRect rectSourceSprite(64, 16, 16, 16);	//margin is 16x16
	sf::Sprite sprite(argTexture, rectSourceSprite);
	sprite.scale(sf::Vector2f(2.0f, 2.0f));	//2.5f is a considerable size for the game
	sprite.setPosition(500.0f, 25.0f);
	sprite.setOrigin({ 8.0f, 8.0f }); //16/2, 16/2
	//keep count of how many actual players there are and give them a number
	//to determine which control they will use. 
	argFrogPlayerList.push_back(new Player(position, true, sprite, {32.0f, 32.0f}, 1));
}

void Game::spawnFood(Food* &argF)
{
	argF->SetToAlive();
}

void Game::DisplayUI(sf::RenderWindow &argWindow, const std::list<Frog*> &argFrogPlayerList)
{
	//Declare and load a font
	sf::Font font;
	//it has a problem loading the text!!
	if (!font.loadFromFile("PressStart2P.ttf"))
	{
		std::cout << "Error loading the font file." << std::endl;
	}
	//Create the text needed
	int playerCount = 0;
	sf::Text textPlayerName[1];
	sf::Text textScore[1];
	for (Frog* player : argFrogPlayerList)		
	{	
		//Create a textPlayerName
		textPlayerName[playerCount].setFont(font);
		textPlayerName[playerCount].setCharacterSize(15);
		textPlayerName[playerCount].setStyle(sf::Text::Regular);
		textPlayerName[playerCount].setFillColor(sf::Color::Green);
		switch (playerCount)
		{
		case 0:
			textPlayerName[playerCount].setString("P1");
			if(!player->CheckIfAlive())
				textPlayerName[playerCount].setString("P1 DEAD");
			textPlayerName[playerCount].setPosition(0.0f, 0.0f);
			break;
		default:
			break;
		}		

		//Create a textScore		
		textScore[playerCount].setFont(font);
		textScore[playerCount].setString("Score: " + std::to_string(player->GetScore()));
		textScore[playerCount].setCharacterSize(15);
		textScore[playerCount].setStyle(sf::Text::Regular);
		textScore[playerCount].setFillColor(sf::Color::Green);	//This should be given by the player class
		switch (playerCount)
		{
		case 0:
			textScore[playerCount].setPosition(0.0f, 20.0f);
			break;
		default:
			break;
		}
		argWindow.draw(textPlayerName[playerCount]);
		argWindow.draw(textScore[playerCount]);
		playerCount += 1;
	}
}

void Game::Water(sf::RenderWindow &argWindow)
{	
	//Render the water

	// Create an instance of the SFML RectangleShape and initialise it
	sf::RectangleShape shape({800.0f, 168.0f});
	shape.setPosition(0.0f, 124.0f);
	// Set the shape's fill colour attribute
	shape.setFillColor(sf::Color(0, 0, 71));
	argWindow.draw(shape);
}

