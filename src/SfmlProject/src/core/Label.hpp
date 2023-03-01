#pragma once
#include <SFML/Graphics.hpp>

class Label
{
private:
	// Fonts
	sf::Font font;			///< Font
	sf::Text text;			///< Text
	int size;				///< Font size
	sf::Color color;		///< Font color

public:
	Label(sf::Font font)
	{
		this->font = font;
		text = sf::Text();
		size = 16;
		color == sf::Color::Black;
	}
};