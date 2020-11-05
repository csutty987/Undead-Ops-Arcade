#include <SFML/Graphics.hpp>
#pragma once

class SFML_GameMenu :
	public sf::Drawable, public sf::Transformable
{
public:
	SFML_GameMenu(std::string menufilename, int windowWidth, int windowHeight);
	~SFML_GameMenu();

	int update(sf::Time elapsedTime);


private:
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

	enum MENU_ALIGNMENT
	{
		LEFT_JUSTIFIED,
		CENTRE_JUSTIFIED,
		RIGHT_JUSTIFIED
	};

	MENU_ALIGNMENT m_menuAlignment;

	sf::Texture m_logo;
	sf::Sprite m_logoSprite;

	sf::Texture m_backgroundTexture;
	sf::Sprite m_backgroundSprite;
	sf::FloatRect m_backgroundRect;

	sf::Font m_gameFont;
	sf::Color m_highlightTextColour;
	sf::Color m_normalTextColour;
	sf::Color m_normalOutlineColour;
	sf::Color m_highlightOutlineColour;
	sf::Vector2f m_menuItemBorder;
	std::vector<sf::Text> m_menuText;

	int m_highlightIndex;

	bool m_prevDownKeyPressed;
	bool m_prevUpKeyPressed;
	bool m_prevReturnKeyPressed;



};

