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
	timeClock.restart();
	for (int i = 0; i < noOfPlayers; i++)
	{
		//Add a new player frog.
		NewPlayer(FrogPlayerList, i, texture);
	}

	CreatePoolOfObjects(texture);

	//for the initial cars when run is initiated. Only one of each will be set to alive.
	InitialObjectSpawn();
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
		//All the river items are updated, moved and rendered every frame
		ObjectFrameCycle(argWindow, RiverItemList);
		//All the players are updated, moved and rendered every frame
		for (Frog* player : FrogPlayerList)
		{		
			if (player->CheckIfAlive())
			{				
				player->Render(argWindow);
				player->Update(screenSize, argWindow, FrogPlayerList, VehicleList, RiverItemList, TimeLeft);	//This checks for collisions
				player->Move();	
				player->ChangeToWaterSprite();
			}						
		}	
		//All the vehicles are updated, moved and rendered every frame
		ObjectFrameCycle(argWindow, VehicleList);
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
			SpawnNewObject(spawnDistance, VehicleList);
			SpawnNewObject(spawnDistance, RiverItemList);
			masterClock.restart();
		}
		if (timeClock.getElapsedTime().asMilliseconds() > 1000)
		{
			TimeLeft -= 1;
			if (TimeLeft == 0)
			{
				TimeLeft = 100;
			}
			timeClock.restart();
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
			VehicleList.clear();
			RiverItemList.clear();
			break;
		}
	}

	std::cout << "FrogGame: Finished" << std::endl;	
}

template<class T>
void Game::ObjectFrameCycle(sf::RenderWindow& argWindow, std::list<T> &ObjectList)
{
	for (T object : ObjectList)
	{
		if (object->CheckIfAlive())
		{
			object->Render(argWindow);
			object->Update(screenSize);
			object->Move();
		}
	}
}
template<class T>
void Game::SpawnNewObject(int spawnDistance, std::list<T> &ObjectList)
{
	for (T object : ObjectList)
	{
		if (!object->CheckIfAlive())
		{
			// spawn the vehicle with the random spawn distance
			switch (spawnDistance)
			{
			case 0:
				object->Spawn(ObjectList, 1.0f);
				continue;
			case 1:
				object->Spawn(ObjectList, 4.0f);
				continue;
			case 2:
				object->Spawn(ObjectList, 8.0f);
				continue;
			default:
				continue;
			}
		}
	}
}

void Game::InitialObjectSpawn()
{
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
}

void Game::CreatePoolOfObjects(sf::Texture& texture)
{
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
			VehicleList.push_back(new Vehicle({ 800.0f, 372.0f }, false, sprite, { 64.0f, 32.0f }, 0.3f, EVehicleType::eTruck));
			break;
		case 1:	//RACING CAR
			rectSourceSprite = sf::IntRect(40, 336, 16, 16);
			sprite = sf::Sprite(texture, rectSourceSprite);
			sprite.setScale({ 2.0f, 2.0f });
			sprite.setOrigin({ 8.0f, 8.0f });
			VehicleList.push_back(new Vehicle({ 800.0f, 404.0f }, false, sprite, { 32.0f, 32.0f }, 0.6f, EVehicleType::eRacingCar));
			break;
		case 2:	//STANDARD CAR
			rectSourceSprite = sf::IntRect(104, 336, 16, 16);
			sprite = sf::Sprite(texture, rectSourceSprite);
			sprite.setScale({ 2.0f, 2.0f });
			sprite.setOrigin({ 8.0f, 8.0f });
			VehicleList.push_back(new Vehicle({ 800.0f, 468.0f }, false, sprite, { 32.0f, 32.0f }, 0.5f, EVehicleType::eStandardCar));
			break;
			// these following ones will be going from left to right
		case 3: //BIG WHEEL CAR
			rectSourceSprite = sf::IntRect(128, 336, 16, 16);
			sprite = sf::Sprite(texture, rectSourceSprite);
			sprite.setScale({ 2.0f, 2.0f });
			sprite.setOrigin({ 8.0f, 8.0f });
			VehicleList.push_back(new Vehicle({ 0.0f, 436.0f }, false, sprite, { 32.0f, 32.0f }, -0.3f, EVehicleType::eBigWheelCar));
			break;
		case 4: //YELLOW CAR
			rectSourceSprite = sf::IntRect(16, 336, 16, 16);
			sprite = sf::Sprite(texture, rectSourceSprite);
			sprite.setScale({ 2.0f, 2.0f });
			sprite.setOrigin({ 8.0f, 8.0f });
			VehicleList.push_back(new Vehicle({ 0.0f, 340.0f }, false, sprite, { 32.0f, 32.0f }, -0.4f, EVehicleType::eYellowCar));
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
				RiverItemList.push_back(new RiverItem({ 800.0f, 244.0f }, false, sprite, { 96.0f, 32.0f }, 0.5f, ERiverItemType::eLog));
				continue;
			case 1:
				RiverItemList.push_back(new RiverItem({ 0.0f, 212.0f }, false, sprite, { 96.0f, 32.0f }, -0.3f, ERiverItemType::eLog));
				continue;
			case 2:
				RiverItemList.push_back(new RiverItem({ 800.0f, 148.0f }, false, sprite, { 96.0f, 32.0f }, 0.3f, ERiverItemType::eLog));
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

				RiverItemList.push_back(new RiverItem({ 800.0f, 276.0f }, false, sprite, { 32.0f, 32.0f }, 0.4f, ERiverItemType::eTurtle));
				continue;
			case 1:
				sprite.setRotation(180.0f);
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
}

void Game::DisplayMainMenu(sf::RenderWindow &argWindow)
{
	bool displayHighscore{ false }, displayP2{ false }, displayP3{false};
	//Open Highscore text
	std::ifstream readFile;
	int topScore{-1};
	readFile.open("Highscore.txt");
	if (readFile.is_open())
	{
		while (!readFile.eof())
		{
			readFile >> topScore;
		}
	}
	readFile.close();
	//Declare and load a font
	sf::Font font;	
	//it has a problem loading the text!!
	if (!font.loadFromFile("PressStart2P.ttf"))
	{
		std::cout << "Error loading the font file." << std::endl;
	}
	sf::Clock clock;
	//Create a textTitle, tip, highscore and controls text
	sf::Text textTitle, textTip, textHighscore, textControls, textControlP1, textControlP2, textControlP3;
	CreateText(textTitle, font, sf::String("FROGGER"), 30, sf::Color::Green, { 250.0f, 50.0f });
	CreateText(textTip, font, sf::String("Press Space to select the option"), 18, sf::Color(255, 165, 0), { 100.0f, 550.0f });
	CreateText(textHighscore, font, sf::String("Highscore: " + std::to_string(topScore)), 18, sf::Color::Green, { 250.0f, 350.0f });
	CreateText(textControls, font, sf::String("Controls:"), 18, sf::Color(255, 165, 0), { 200.0f, 400.0f });
	CreateText(textControlP1, font, sf::String("P1 Controls: WASD (movement)"), 18, sf::Color::Green, { 200.0f, 430.0f });
	CreateText(textControlP2, font, sf::String("P2 Controls: IJKL (movement)"), 18, sf::Color::Cyan, { 200.0f, 460.0f });
	CreateText(textControlP3, font, sf::String("P3 Controls: Arrows (movement)"), 18, sf::Color::Yellow, { 200.0f, 490.0f });


	//create a sprite
	sf::Texture texture;
	texture.loadFromFile("GeneralRip.png");

	sf::Sprite spriteP1, spriteP2, spriteP3;
	sf::IntRect rectSourceSprite(64, 16, 16, 16);	//margin is 16x16
	spriteP1 = sf::Sprite(texture, sf::IntRect(64, 16, 16, 16));

	//rectSourceSprite = sf::IntRect(64, 48, 16, 16);
	spriteP2 = sf::Sprite(texture, sf::IntRect(64, 48, 16, 16));

	//rectSourceSprite = sf::IntRect(64, 80, 16, 16);
	spriteP3 = sf::Sprite(texture, sf::IntRect(64, 80, 16, 16));

	spriteP1.scale(sf::Vector2f(5.0f, 5.0f));	//2.0f is a considerable size for the game
	spriteP2.scale(sf::Vector2f(5.0f, 5.0f));
	spriteP3.scale(sf::Vector2f(5.0f, 5.0f));

	spriteP1.setPosition(500.0f, 25.0f);
	spriteP2.setPosition(600.0f, 25.0f);
	spriteP3.setPosition(700.0f, 25.0f);

	// this is for sprite testing purposes
	/*sf::RectangleShape testingRectangle({ 200.0f,100.0f });
	testingRectangle.setFillColor(sf::Color::White);
	testingRectangle.setPosition({ 495.0f, 20.0f });*/

	const int noOfOptions{ 4 };	
	int optionIndex{ 0 };		
	sf::Text textOptions[noOfOptions];	
	
	
	for (int i = 0; i < noOfOptions; i++)
	{
		switch (i)
		{
		case 0:
			CreateText(textOptions[i], font, sf::String("Single Player"), 18, sf::Color(255, 165, 0), { 250.0f, 150.0f });
			break;
		case 1:
			CreateText(textOptions[i], font, sf::String("2 Player Mode"), 18, sf::Color(255, 165, 0), { 250.0f, 200.0f });
			break;
		case 2:
			CreateText(textOptions[i], font, sf::String("3 Player Mode"), 18, sf::Color(255, 165, 0), { 250.0f, 250.0f });
			break;
		case 3:
			CreateText(textOptions[i], font, sf::String("Highscore"), 18, sf::Color(255, 165, 0), { 250.0f, 300.0f });
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

					if (optionIndex == 1) { displayP2 = true; }
					else if (optionIndex == 2) { displayP3 = true; }

					if (optionIndex != 1) { displayP2 = false; }
					if (optionIndex != 2) { displayP3 = false; }
					if (optionIndex != 3) { displayHighscore = false; }
					continue;
				case sf::Keyboard::S:
					textOptions[optionIndex].setOutlineThickness(0.0f);
					optionIndex++;
					if (optionIndex > noOfOptions - 1) { optionIndex = 0; }
					textOptions[optionIndex].setOutlineColor(sf::Color::White);
					textOptions[optionIndex].setOutlineThickness(2.0f);

					if (optionIndex == 1) { displayP2 = true; }
					else if (optionIndex == 2) { displayP3 = true; }

					if (optionIndex != 1) { displayP2 = false; }
					if (optionIndex != 2) { displayP3 = false; }
					if (optionIndex != 3) { displayHighscore = false; }
					continue;
				case sf::Keyboard::Space:					
					//if the player is on the button of "Play game then go straight to the game"	
					if (optionIndex != 3)
					{
						m_currentState = EGameState::eRunGame;
						if (optionIndex == 0) { noOfPlayers = 1; }
						else if (optionIndex == 1) { noOfPlayers = 2; }
						else if (optionIndex == 2) { noOfPlayers = 3; }
						break;
					}									
					else if (optionIndex == 3) { displayHighscore = true; }				
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
			spriteP1.setTextureRect(rectSourceSprite);
			spriteP2.setTextureRect(sf::IntRect(rectSourceSprite.left, 48, 16, 16));
			spriteP3.setTextureRect(sf::IntRect(rectSourceSprite.left, 80, 16, 16));
			clock.restart();
		}
		//Clear the content of the window every frame
		argWindow.clear();

		//Draw the text
		argWindow.draw(textTitle);
		argWindow.draw(textTip);
		//argWindow.draw(testingRectangle);
		argWindow.draw(spriteP1);
		argWindow.draw(textControlP1);
		for (int i = 0; i < noOfOptions; i++)
		{
			argWindow.draw(textOptions[i]);
		}
		if (displayP2)
		{ 
			argWindow.draw(spriteP2);
			argWindow.draw(textControlP2);
		}
		if (displayP3)
		{
			argWindow.draw(spriteP2);
			argWindow.draw(textControlP2);
			argWindow.draw(spriteP3);
			argWindow.draw(textControlP3);
		}
		if (displayHighscore) { argWindow.draw(textHighscore); }
		argWindow.draw(textControls);
		// Get the window to display its contents
		argWindow.display();		
	}
}

void Game::CreateText(sf::Text& argText, const sf::Font& argFont, const sf::String& argString, const int& argCharSize, const sf::Color& argColor, const sf::Vector2f& argPosition)
{
	argText.setFont(argFont);
	argText.setString(argString);
	argText.setCharacterSize(argCharSize);
	argText.setFillColor(argColor);
	argText.setPosition(argPosition);
}

bool Game::DisplayGameOver(sf::RenderWindow & argWindow)
{
	bool isPlayingAgain = false;
	int topScore{ -1 }, playerScore{ 0 }, winnerPlayer{ 1 }, PlayerNumber{1};
	bool newHighscore{ false };
	sf::Color winnerColour = sf::Color::Green;

	//Declare and load a font
	sf::Font font;
	if (!font.loadFromFile("PressStart2P.ttf"))
	{
		std::cout << "Error loading the font file." << std::endl;
	}
	//Open Highscore text
	std::ifstream readFile;
	readFile.open("Highscore.txt");
	if (readFile.is_open())
	{
		while (!readFile.eof())
		{
			readFile >> topScore;
		}
	}
	readFile.close();	
	//Get the current highscore
	std::ofstream writeFile("Highscore.txt");
	//Create a textTite, highscore text,
	sf::Text textTitle, textHighscoreInfo;
	CreateText(textTitle, font, sf::String("Game Over!"), 30, sf::Color::Red, { 250.0f, 50.0f });
	CreateText(textHighscoreInfo, font, sf::String("New Highscore!"), 30, sf::Color::Yellow, { 200.0f, 90.0f });

	for (Frog* player : FrogPlayerList)
	{	
		if (writeFile.is_open())
		{
			if (player->GetScore() > topScore)
			{
				topScore = player->GetScore();	
				newHighscore = true;
				winnerColour = player->GetColor();
				winnerPlayer = PlayerNumber;
			}
			writeFile << topScore;
			playerScore = player->GetScore();
		}
		writeFile.close();
		PlayerNumber++;
	}	
	//Create Highscore number text, final score text, indication text, exit text
	sf::Text textHighscoreNumber, textScore, textIndication, textExit;
	CreateText(textHighscoreNumber, font, sf::String("Highscore: " + std::to_string(topScore)), 30, sf::Color::Green, { 200.0f, 250.0f });
	CreateText(textScore, font, sf::String("Winner P" + std::to_string(winnerPlayer) + " Score: " + std::to_string(playerScore)), 30, winnerColour, { 200.0f, 200.0f });
	CreateText(textIndication, font, sf::String("Press Space to go back to the main menu"), 18, sf::Color(255, 165, 0), { 50.0f, 450.0f });
	CreateText(textExit, font, sf::String("Press Escape to exit the game"), 18, sf::Color(255, 165, 0), { 150.0f, 550.0f });

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
		argWindow.draw(textScore);
		if (newHighscore) { argWindow.draw(textHighscoreInfo); }
		argWindow.draw(textHighscoreNumber);
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
	sf::IntRect rectSourceSprite;
	sf::Sprite sprite;
	switch (playerNumber)
	{
	case 0:	
		rectSourceSprite = sf::IntRect(64, 16, 16, 16);	//margin is 16x16
		sprite = sf::Sprite(argTexture, rectSourceSprite);
		sprite.scale(sf::Vector2f(2.0f, 2.0f));
		sprite.setOrigin({ 8.0f, 8.0f }); //16/2, 16/2
		position = { 200.0f, 500.0f };
		argFrogPlayerList.push_back(new Player(position, true, sprite, { 32.0f, 32.0f }, sf::Color::Green, 1));	//Also pass a color
		break;	
	case 1:
		rectSourceSprite = sf::IntRect(64, 48, 16, 16);
		sprite = sf::Sprite(argTexture, rectSourceSprite);
		sprite.scale(sf::Vector2f(2.0f, 2.0f));
		sprite.setOrigin({ 8.0f, 8.0f }); //16/2, 16/2
		position = { 400.0f, 500.0f };
		argFrogPlayerList.push_back(new Player(position, true, sprite, { 32.0f, 32.0f }, sf::Color::Cyan, 2));	//Also pass a color
		break;
	case 2:
		rectSourceSprite = sf::IntRect(64, 80, 16, 16);
		sprite = sf::Sprite(argTexture, rectSourceSprite);
		sprite.scale(sf::Vector2f(2.0f, 2.0f));
		sprite.setOrigin({ 8.0f, 8.0f }); //16/2, 16/2
		position = { 600.0f, 500.0f };
		argFrogPlayerList.push_back(new Player(position, true, sprite, { 32.0f, 32.0f }, sf::Color::Yellow, 3));	//Also pass a color
		break;
	default:
		break;
	}	

	//sprite = sf::Sprite(argTexture, rectSourceSprite);
	//sprite.scale(sf::Vector2f(2.0f, 2.0f));	//2.0f is a considerable size for the game
	////sprite.setPosition(500.0f, 25.0f);	//I don't know what this does so I removed it lol
	//sprite.setOrigin({ 8.0f, 8.0f }); //16/2, 16/2
	////keep count of how many actual players there are and give them a number
	////to determine which control they will use. 
	//argFrogPlayerList.push_back(new Player(position, true, sprite, {32.0f, 32.0f}, 1));
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
	sf::Text textTime, textPlayerName[3], textScore[3], textLives[3];

	//Create a textTime
	CreateText(textTime, font, sf::String("Time: " + std::to_string(TimeLeft)), 15, sf::Color::Green, { 560.0f, 560.0f });

	for (Frog* player : argFrogPlayerList)		
	{	
		switch (playerCount)
		{
		case 0:
			CreateText(textPlayerName[playerCount], font, sf::String("P1"), 15, player->GetColor(), { 0.0f, 0.0f });
			if (!player->CheckIfAlive())
				CreateText(textPlayerName[playerCount], font, sf::String("P1 DEAD"), 15, player->GetColor(), { 0.0f, 0.0f });
			break;
		case 1:
			CreateText(textPlayerName[playerCount], font, sf::String("P2"), 15, player->GetColor(), { 300.0f, 0.0f });
			if (!player->CheckIfAlive())
				CreateText(textPlayerName[playerCount], font, sf::String("P2 DEAD"), 15, player->GetColor(), { 300.0f, 0.0f });
			break;
		case 2:
			CreateText(textPlayerName[playerCount], font, sf::String("P3"), 15, player->GetColor(), { 600.0f, 0.0f });
			if (!player->CheckIfAlive())
				CreateText(textPlayerName[playerCount], font, sf::String("P3 DEAD"), 15, player->GetColor(), { 600.0f, 0.0f });
			break;
		default:
			break;
		}		
		//Create a textScore			
		switch (playerCount)
		{
		case 0:
			CreateText(textScore[playerCount], font, sf::String("Score: " + std::to_string(player->GetScore())), 15, player->GetColor(), { 0.0f, 20.0f });
			break;
		case 1:
			CreateText(textScore[playerCount], font, sf::String("Score: " + std::to_string(player->GetScore())), 15, player->GetColor(), { 300.0f, 20.0f });
			break;
		case 2:
			CreateText(textScore[playerCount], font, sf::String("Score: " + std::to_string(player->GetScore())), 15, player->GetColor(), { 600.0f, 20.0f });
			break;
		default:
			break;
		}

		//Create a textLives
		switch (playerCount)
		{
		case 0:
			CreateText(textLives[playerCount], font, sf::String("Lives: " + std::to_string(player->GetLives())), 15, player->GetColor(), { 0.0f, 40.0f });
			break;
		case 1:
			CreateText(textLives[playerCount], font, sf::String("Lives: " + std::to_string(player->GetLives())), 15, player->GetColor(), { 300.0f, 40.0f });
			break;
		case 2:
			CreateText(textLives[playerCount], font, sf::String("Lives: " + std::to_string(player->GetLives())), 15, player->GetColor(), { 600.0f, 40.0f });
			break;
		default:
			break;
		}
		argWindow.draw(textTime);
		argWindow.draw(textPlayerName[playerCount]);
		argWindow.draw(textScore[playerCount]);
		argWindow.draw(textLives[playerCount]);
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