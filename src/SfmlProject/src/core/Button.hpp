#pragma once
#include <SFML/Graphics.hpp>
#include "Label.hpp"

/**
 * Base class for buttons
*/
class Button
{
private:
	int id;						///< Recognizable identification number
	sf::Vector2f size;			///< Button size
	sf::RectangleShape shape;	///< Button shape to render
	
	// Colors
	sf::Color fgColor;			///< Foreground color

	// Label with text
	Label label;

// Initializations
public:
	/**
	 * Default constructor
	*/
	Button(sf::Font labelFont): label(labelFont)
	{
		id = 0;
		fgColor = sf::Color::Black;

		// Init shape
		shape.setFillColor(sf::Color::White);	// Background color
		shape.setPosition({ 0, 0 });	// Initial position
		shape.setSize({ 1, 1 });	// Initial size

		// To change the shape scale, use sf::RectangleShape::setScale
	}

// Rendering
public:
	void draw(sf::RenderTarget *target)
	{
		target->draw(shape);
	}

	/**
	 * Set the button's background color
	 * @param color New color
	*/
	void setBgColor(sf::Color color) { shape.setFillColor(color); }

	/**
	 * Set the button's new size
	 * @param size New size
	*/
	void setSize(sf::Vector2f size) { shape.setScale(size); }

	/**
	 * Set the button's new position on target
	 * @param position New position
	*/
	void setPosition(sf::Vector2f position) { shape.setPosition(position); }
};