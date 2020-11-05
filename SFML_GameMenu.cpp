#include "SFML_GameMenu.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

SFML_GameMenu::SFML_GameMenu(std::string menufilename, int windowWidth, int windowHeight)
{
	std::ifstream inputFile(menufilename);

	if (inputFile.is_open())
	{
		std::string stringLine;
		//** This may need changing **
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			//load texture file and set it to the sprite
			m_backgroundTexture.loadFromFile(stringLine);
			m_backgroundSprite.setTexture(m_backgroundTexture);

			//set origin, texture rectangle and position of sprite
			sf::Vector2u textureSize = m_backgroundTexture.getSize();
			m_backgroundSprite.setOrigin(textureSize.x / 2, textureSize.y / 2);
			m_backgroundSprite.setTextureRect(sf::IntRect(0, 0, textureSize.x, textureSize.y));
			m_backgroundSprite.setPosition(0, 0);

			//set rectangle texture centred at 0,0
			m_backgroundRect.left = static_cast<float> (textureSize.x / 2);
			m_backgroundRect.top = static_cast<float> (textureSize.y / 2);
			m_backgroundRect.width = textureSize.x;
			m_backgroundRect.height = textureSize.y;
		}

		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			//load texture file and set it to sprite
			m_logo.loadFromFile(stringLine);
			m_logoSprite.setTexture(m_logo);

			//set origin, texture rectangle and position of sprite
			sf::Vector2u textureSize = m_logo.getSize();
			m_logoSprite.setOrigin(textureSize.x / 2, textureSize.y / 2);
			m_logoSprite.setTextureRect(sf::IntRect(0, 0, textureSize.x, textureSize.y));
			m_logoSprite.setPosition(0, m_backgroundTexture.getSize().y / 2 * 0.9f);
			//set position of the logo 90% down the screen height
		}
		//read 3rd line - font
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			m_gameFont.loadFromFile(stringLine);
		}

		std::string redString;
		std::string greenString;
		std::string blueString;

		int redInt;
		int greenInt;
		int blueInt;

		//read 4th line - normal text fill colour (RGB)
		std::getline(inputFile, stringLine);

		if (inputFile.good())
		{
			//separate them into 3 strings (separated by whitespace)
			std::istringstream stringStream(stringLine);
			stringStream >> redString;
			stringStream >> greenString;
			stringStream >> blueString;

			//convert them to int
			redInt = std::stoi(redString);
			greenInt = std::stoi(greenString);
			blueInt = std::stoi(blueString);

			m_normalTextColour = sf::Color(redInt, greenInt, blueInt);
		}

		//read 5th line - normal text outline colour (RGB)
		std::getline(inputFile, stringLine);

		if (inputFile.good())
		{
			//separate them into 3 strings (separated by whitespace)
			std::istringstream stringStream(stringLine);
			stringStream >> redString;
			stringStream >> greenString;
			stringStream >> blueString;

			//convert them to int
			redInt = std::stoi(redString);
			greenInt = std::stoi(greenString);
			blueInt = std::stoi(blueString);

			m_normalOutlineColour = sf::Color(redInt, greenInt, blueInt);
		}

		//read 6th line - Highlight text fill colour (RGB)
		std::getline(inputFile, stringLine);

		if (inputFile.good())
		{
			//separate them into 3 strings (separated by whitespace)
			std::istringstream stringStream(stringLine);
			stringStream >> redString;
			stringStream >> greenString;
			stringStream >> blueString;

			//convert them to int
			redInt = std::stoi(redString);
			greenInt = std::stoi(greenString);
			blueInt = std::stoi(blueString);

			m_highlightTextColour = sf::Color(redInt, greenInt, blueInt);
		}

		//read 7th line - highlight text outline colour (RGB)
		std::getline(inputFile, stringLine);

		if (inputFile.good())
		{
			//separate them into 3 strings (separated by whitespace)
			std::istringstream stringStream(stringLine);
			stringStream >> redString;
			stringStream >> greenString;
			stringStream >> blueString;

			//convert them to int
			redInt = std::stoi(redString);
			greenInt = std::stoi(greenString);
			blueInt = std::stoi(blueString);

			m_highlightOutlineColour = sf::Color(redInt, greenInt, blueInt);
		}

		std::string xBorderString;
		std::string yBorderString;

		int xBorderInt;
		int yBorderInt;

		//read 8th line - border size in pixels
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			//separate them into two strings
			std::istringstream stringStream(stringLine);
			stringStream >> xBorderString;
			stringStream >> yBorderString;

			//Convert them to int
			xBorderInt = std::stoi(xBorderString);
			yBorderInt = std::stoi(yBorderString);

			//set values to m_menuItemBorder
			m_menuItemBorder.x = xBorderInt;
			m_menuItemBorder.y = yBorderInt;
		}

		//read 9th line - menu alignment
		std::getline(inputFile, stringLine);
		if (inputFile.good())
		{
			if (!std::strcmp(stringLine.c_str(), "LEFT_JUSTIFIED"))
				m_menuAlignment = LEFT_JUSTIFIED;
			else if (!std::strcmp(stringLine.c_str(), "CENTRE_JUSTIFIED"))
				m_menuAlignment = CENTRE_JUSTIFIED;
			else if (!std::strcmp(stringLine.c_str(), "RIGHT_JUSTIFIED"))
				m_menuAlignment = RIGHT_JUSTIFIED;
		}

		sf::Text start;
		start.setFont(m_gameFont);
		start.setCharacterSize(50);
		start.setStyle(sf::Text::Bold);
		start.setFillColor(m_normalTextColour);
		start.setOutlineColor(m_normalOutlineColour);
		start.setOutlineThickness(1.0f);

		sf::Vector2f textpos;

		if (m_menuAlignment == CENTRE_JUSTIFIED)
		{
			textpos.x = m_backgroundRect.left - m_backgroundRect.width / 2;
			textpos.y = m_backgroundRect.top - m_menuItemBorder.y;
		}
		else if (m_menuAlignment == LEFT_JUSTIFIED)
		{
			textpos.x = m_backgroundRect.left - m_menuItemBorder.x;
			textpos.y = m_backgroundRect.top - m_menuItemBorder.y;
		}
		else if (m_menuAlignment == RIGHT_JUSTIFIED)
		{
			textpos.x = m_backgroundRect.left - m_backgroundRect.width + (m_menuItemBorder.x * 5);
			textpos.y = m_backgroundRect.top - m_menuItemBorder.y - (m_menuItemBorder.y * 3);
		}

		do
		{
			//read every line for each menu item
			std::getline(inputFile, stringLine);
			if (inputFile.good())
			{
				//set text's position to textpos
				start.setPosition(textpos.x, textpos.y);

				//set text's string to stringLine( the one we just read)
				start.setString(stringLine);

				//set text's origin to mid left coordinate
				sf::FloatRect textbox = start.getLocalBounds();
				if (m_menuAlignment == CENTRE_JUSTIFIED)
				{
					start.setOrigin(textbox.width / 2, textbox.height / 2);
				}
				else if (m_menuAlignment == LEFT_JUSTIFIED)
				{
					start.setOrigin(0, textbox.height / 2);
				}
				else if (m_menuAlignment == RIGHT_JUSTIFIED)
				{
					start.setOrigin(textbox.width, textbox.height / 2);
				}

				//store text to m_menuText array
				m_menuText.push_back(start);

				//calculate the next text position by incrementing its y position
				textpos.y += start.getLocalBounds().height * 1.2f;
			}
			else
				break;

		} while (true);

		m_highlightIndex = 0;
		m_menuText[m_highlightIndex].setFillColor(m_highlightTextColour);
		m_menuText[m_highlightIndex].setOutlineColor(m_highlightOutlineColour);

		m_prevDownKeyPressed = true;
		m_prevUpKeyPressed = true;
		m_prevReturnKeyPressed = true;


	}
	inputFile.close();
}

int SFML_GameMenu::update(sf::Time elapsedTime)
{
	bool m_currentDownKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
	bool m_currentUpKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
	bool m_currentReturnKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Return);

	if (m_currentDownKeyPressed && !m_prevDownKeyPressed)
	{
		//set colour of the current higlighted menu item to normal colour
		m_menuText[m_highlightIndex].setFillColor(m_normalTextColour);
		m_menuText[m_highlightIndex].setOutlineColor(m_normalOutlineColour);

		//increment highlighted index by one, modulated by number of menu items
		m_highlightIndex++;
		m_highlightIndex = m_highlightIndex % m_menuText.size();

		//set colour of the new highlighted menu item to highlight colour
		m_menuText[m_highlightIndex].setFillColor(m_highlightTextColour);
		m_menuText[m_highlightIndex].setOutlineColor(m_highlightOutlineColour);
	}
	else if (m_currentUpKeyPressed && !m_prevUpKeyPressed)
	{
		//set colour of current highlight menu item to normal colour
		m_menuText[m_highlightIndex].setFillColor(m_normalTextColour);
		m_menuText[m_highlightIndex].setOutlineColor(m_normalOutlineColour);

		//increment highlighted index by one, if it becomes negative then add the number of menu items to it.
		m_highlightIndex--;
		if (m_highlightIndex < 0)
			m_highlightIndex = m_highlightIndex + m_menuText.size();

		//set colour of new highlighted menu item to highlight colour
		m_menuText[m_highlightIndex].setFillColor(m_highlightTextColour);
		m_menuText[m_highlightIndex].setOutlineColor(m_highlightOutlineColour);
	}

	m_prevDownKeyPressed = m_currentDownKeyPressed;
	m_prevUpKeyPressed = m_currentUpKeyPressed;

	bool hasSelected = false;

	if (m_currentReturnKeyPressed && !m_prevReturnKeyPressed)
		hasSelected = true;

	m_prevReturnKeyPressed = m_currentReturnKeyPressed;

	if (hasSelected)
		return m_highlightIndex;
	else
		return -1;
}

void SFML_GameMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_backgroundSprite, states);
	target.draw(m_logoSprite, states);

	for (std::size_t count = 0; count < m_menuText.size(); count++)
		target.draw(m_menuText[count], states);
}

SFML_GameMenu::~SFML_GameMenu()
{
	//clear menu item list
	m_menuText.clear();
}