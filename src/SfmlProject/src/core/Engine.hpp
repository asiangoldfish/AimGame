#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>

// SFML
#include <SFML/Graphics.hpp>

// Custom
#include "game/Enemy.hpp"
#include "game/Player.hpp"
#include "shared/math.hpp"
#include "shared/debug.hpp"

class Game
{
private:
	// Window related data
	sf::RenderWindow* window;

	// Enemy
	std::vector<Enemy> enemies;	// Collection of enemies
	int enemyMax;				// Max spawned enemy at any given point in time
	float enemyMaxTimer;		// Enemy max cooldown timer
	float enemySpawnTimer;		// Current timer for spawning enemy

	// Player
	Player *player;
	int mouseClicks;

	// Debugger
	Debug debug;

	// Fonts and texts
	sf::Font opensans;
	sf::Text scoreText;

// Initializations
public:
	/**
	 * @brief Default constructor
	 * 
	 * When using this constructor, the window must be created
	 * manually.
	*/
	Game() 
	{
		window = new sf::RenderWindow();

		initEnemies();
		debug = Debug();
	}

	/**
	 * @brief Creates window
	 * @param videoMode Screen size
	 * @param title Window class name and displayed window title
	*/
	Game(sf::VideoMode videoMode, std::string title, int fps)
	{
		// Initialize main game window
		window = new sf::RenderWindow();
		window->create(videoMode, title);
		window->setFramerateLimit(fps);

		// Initialize player
		player = new Player();

		// Initialize enemies
		initEnemies();
		debug = Debug();

		// Initialize fonts and texts
		if (!opensans.loadFromFile("data/fonts/OpenSans-Regular.ttf"))
		{
			std::cerr << "ERROR: Could not load OpenSans font from file\n";
		}

		scoreText.setFont(opensans);
		scoreText.setCharacterSize(20);
		scoreText.setString("NONE");
		int width = scoreText.getGlobalBounds().width;
		scoreText.setPosition(window->getSize().x / 2.f - width * 2, 20.f);

		debug.log("Game initialized!");
	}

	/**
	* @brief Destructor
	* 
	* Deallocates and releases memory
	*/
	~Game()
	{
		// Window
		delete window;
		window = nullptr;

		// Player
		delete player;
		player = nullptr;
	}

// Rendering
public:
	/**
	 * @brief Draw things to screen.
	 * 
	 * This method should be called every frame to display images
	 * to the screen
	*/
	void draw()
	{
		window->clear();

		// Draw enemies randomly on the screen
		updateSpawnTimer();

		// Only spawn new enemy if spawn timer is 0 and an enemy is dead
		if (enemySpawnTimer <= 0)
		{
			//Revive the first dead enemy and spawn it in a random place on the
			// screen.
			for (auto &e : enemies)
			{
				if (!e.getIsAlive())
				{
					// Random enemy size
					float size = rng(10.f, 50.f);
					e.setSize(size);

					// Random enemy position on screen
					e.respawn(
						{ 
							rng(0, window->getSize().x - e.getMesh().getGlobalBounds().width), 
							rng(50, window->getSize().y - e.getMesh().getGlobalBounds().height)
						}
					);
					e.setIsAlive(true);
					resetSpawnTimer();
					break;
				}
			}
			
		}


		// Draw enemies to screen
		for (auto e : enemies)
		{
			if (e.getIsAlive())
			{
				e.draw(*window);
			}
		}

		// Player score
		std::stringstream ss;
		
		float accuracy;
		if (mouseClicks == 0)
			accuracy = 0.f;
		else 
			accuracy = player->getPoints() / static_cast<float>(mouseClicks) * 100.f;

		ss  << "Score: " << player->getPoints()
			<< " | Accuracy: " << std::setw(5) << std::setprecision(4) << accuracy << "%"
			<< " | Clicks: " << mouseClicks
			<< std::endl;

		scoreText.setString(ss.str());
		window->draw(scoreText);
		
		window->display();
	}

// Enemies game logic
public:
	void initEnemies()
	{
		enemyMax = 1;
		enemyMaxTimer = 0.f;
		enemySpawnTimer = 0.f;

		for (int i = 0; i < enemyMax; i++)
		{
			Enemy e;
			e.setFillColor(sf::Color::Red);
			e.setSize(25.f, 25.f);
			e.setPosition(0, 0);
			e.setEnableTick(true);
			e.setIsAlive(false);
			enemies.push_back(e);
		}
	}

	void updateSpawnTimer()
	{
		if (enemySpawnTimer >= 0)
			enemySpawnTimer -= 1 / 60.f;
	}

	void resetSpawnTimer()
	{
		enemySpawnTimer = enemyMaxTimer;
	}

	/**
	 * @brief Attempt to shoot the enemy
	 * 
	 * If the enemy was it, then kill it and remove from screen
	 * 
	 * @param aimedPos 
	*/
	void shootEnemy(sf::Vector2i aimedPos)
	{
		// Increase player mouse clicks to calculate their accuracy
		mouseClicks++;

		// TODO - Find a way to fetch the one enemy hit
		for (auto &enemy : enemies)
		{
			// Kill enemy if aimed position overlaps it
			if (enemy.isOverlapping(aimedPos))
			{
				enemy.setIsAlive(false);
				player->addPoints(1);
				resetSpawnTimer();
				break;
			}
		}
	}

public:
	sf::RenderWindow* getWindow()
	{
		return window;
	}
};