#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <windows.h>
#include <sysinfoapi.h> // Time

// SFML
#include <SFML/Graphics.hpp>

// Custom
#include "game/Enemy.hpp"
#include "shared/math.hpp"

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

	// System time
	SYSTEMTIME st; // , lt;

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
	}

	/**
	 * @brief Creates window
	 * @param videoMode Screen size
	 * @param title Window class name and displayed window title
	*/
	Game(sf::VideoMode videoMode, std::string title, int fps)
	{
		// Initialize system time for debugging
		initSystime();

		// Initialize main game window
		window = new sf::RenderWindow();
		window->create(videoMode, title);
		window->setFramerateLimit(fps);

		// Initialize enemies
		initEnemies();
	}

	/**
	* @brief Destructor
	* 
	* Deallocates and releases memory
	*/
	~Game()
	{
		delete window;
		window = nullptr;
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
			/*
			Revive the first dead enemy and spawn it in a random place on the
			screen.
			*/
			for (auto &e : enemies)
			{
				if (!e.getIsAlive())
				{
					e.respawn({ rng() * window->getSize().x, rng() * window->getSize().y });
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


		window->display();
	}

// Enemies game logic
public:
	void initEnemies()
	{
		enemyMax = 10;
		enemyMaxTimer = 1;
		enemySpawnTimer = enemyMaxTimer;

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
		enemySpawnTimer -= 1 / 60.f;
	}

	void resetSpawnTimer()
	{
		enemySpawnTimer = enemyMaxTimer;
	}

public:
	sf::RenderWindow* getWindow()
	{
		return window;
	}

// For debugging only
private:
	/**
	 * @brief Initialize system time for debugging
	*/
	void initSystime()
	{
		GetSystemTime(&st);
	}

	void log(std::string msg)
	{
		// Time
		std::cout << "[ " << st.wHour + 1 << ":" << st.wMinute << ":" << st.wSecond << " ] ";

		// Message
		std::cout << msg << std::endl;
	}
};