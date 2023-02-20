#pragma once

#include <iostream>

class Player
{
private:
	std::string name;
	int points;

// Initializations
public:
	Player()
	{
		name = "Unknown Name";
		points = 0;
	}

	Player(std::string name)
	{
		this->name = name;
		points = 0;
	}

// Accessors and Mutators
public:
	/**
	 * @brief Get player name
	 * @return Player name
	*/
	std::string getName() { return name; }

	/**
	 * @brief Set player name
	 * @param name New player name
	*/
	void setName(std::string name) { this->name = name; }

	/**
	 * @brief Get player's current point score
	 * @return Player's point score
	*/
	int getPoints() { return points; }

	/**
	 * @brief Add more points to the player
	 * @param points Number of points to add
	*/
	void addPoints(int points)
	{
		// Make sure it doesn't become negative
		if (this->points + points < 0)
		{
			this->points = 0;
		}
		else
		{
			this->points += points;
		}
	}
};