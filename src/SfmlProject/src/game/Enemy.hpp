#pragma once
#include <iostream>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "../shared/math.hpp"

class Enemy
{
private:
	// Name
	int maxNameLength;		///< Name's maximum length
	std::string name;		///< Enemy name

	// Mesh
	sf::CircleShape mesh;	///< Enemy mesh

	// Time
	bool enableTick;		///< Enable tick. Enabling this may impact game performance
	float t;

	// Physics
	int direction;

	// Life span
	bool isAlive;			///< Whether the enemy is dead

// Class initializations and deletion
public:
	/**
	 * @brief Enemy default constructor
	*/
	Enemy()
	{
		// Name
		maxNameLength = 20;
		name = "";

		// Mesh
		mesh.setRadius(1.f);
		mesh.setPosition(0, 0);
		mesh.setFillColor(sf::Color::Red);

		// Physics
		direction = 1;

		// Time
		enableTick = false;
		t = 0.f;

		// Lifespan
		isAlive = false;
	}

	/**
	 * @brief Enemy destructor
	*/
	~Enemy() {}

// Accessors and mutators
public:
	/**
	 * @brief Get the enemy's name
	*/
	std::string getName()
	{
		return name;
	}

	/**
	 * @brief Set the enemy's name
	 * @param Maximum name length
	*/
	void setName(std::string name)
	{
		if (name.length() <= maxNameLength)
		{
			this->name = name;
		}
	}

	//--------------- Mesh related ------------//

	/**
	 * @brief Set the mesh's scale
	 * @param x Scale in x-axis
	 * @param y Scale in y-axis 
	*/
	void setSize(float x, float y)
	{
		mesh.setScale(x, y);
	}

	void setSize(float x)
	{
		mesh.setScale(x, x);
	}

	sf::Vector2f getSize()
	{
		return sf::Vector2f(mesh.getScale());
	}

	/**
	 * @brief Set the enemy's display color
	 * @param color Color to display
	*/
	void setFillColor(sf::Color color)
	{
		mesh.setFillColor(color);
	}

	sf::Vector2f getPosition()
	{
		return mesh.getPosition();
	}

	void setPosition(float x, float y)
	{
		mesh.setPosition(x, y);
	}

	sf::CircleShape getMesh() const { return mesh; }

	// --------------- Overlapping ------------//
	
	/**
	 * @brief Checks whether a given position is overlapping the enemy
	 * @param position Position to check against
	 * @return True if overlapping, false if not
	*/
	bool isOverlapping(sf::Vector2i position)
	{
		// Use the mesh's global bounds to check for overlapping
		return mesh.getGlobalBounds().contains(
			static_cast<float>(position.x), static_cast<float>(position.y)
		);
	}

	//--------------- Time related ------------//
	void setEnableTick(bool enableTick)
	{
		this->enableTick = enableTick;
	}

	//--------------- Lifespan related ------------//
	bool getIsAlive() { return isAlive; }
	void setIsAlive(bool boo ) { isAlive = boo; };

// Game logic
public:
	
	/**
	 * @brief Draw the enemy on target
	 * @param target Target to render on
	*/
	void draw(sf::RenderTarget& target)
	{
		t += 1.f / 60.f * direction;

		/*
		// Interpolate x-position
		if (enableTick)
		{
			if (t >= 1) { // Endret her
				direction = -1;
			}
			else if (t <= 0) {
				direction = 1;
			}
			t += 1.f / 60.f * direction;

			mesh.setPosition(lerp(0, target.getSize().x - mesh.getScale().x, t), mesh.getPosition().y);
		}
		*/



		// Enemy circular motion
		/*
		float radius = 50.f;

		float delay = 2.f;

		float x = target.getSize().x / 2.f + radius * std::cos(t * delay * PI);
		float y = target.getSize().y / 2.f + radius * std::sin(t * delay * PI);

		std::cout << t << std::endl;

		mesh.setPosition(x, y);
		*/

		// Render to screen only if alive
		if (isAlive)
		{
			target.draw(mesh);
		}
	}

	/**
	 * @brief Respawn enemy
	 * @param position Position to respawn at
	*/
	void respawn(sf::Vector2f position)
	{
		mesh.setPosition(position);
		isAlive = true;
	}
};