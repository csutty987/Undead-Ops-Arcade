#include <SFML/Graphics.hpp>
#include "SFML_TitleScreen.h"
#include "SFML_GameMenu.h"
#include "SFML_GameWorldLayer.h"
#include "SFML_GameWorld.h"
#include "credits.h"
#pragma once

class SFML_Application :
	public sf::NonCopyable
{
public:
	SFML_Application(int windowWidth, int windowHeight);
	~SFML_Application();

	void run();

private:
	void update(sf::Time elapsedTime);
	void render();

	enum AppState {
		TITLESCREEN,
		MAINMENU,
		GAMEPLAYING,
		EXITING,
		OPTIONMENU,
		CREDITS
	};

private:
	//true if application is successfully initialised 
	bool m_initialised;

	//attributes for graphics/window
	sf::RenderWindow m_window;
	std::size_t m_screenWidth;
	std::size_t m_screenHeight;

	//attribute for capturing events
	sf::Event m_event;

	//fonts
	sf::Font m_textFont;
	sf::Text m_messageText;

	//attribute for appstate
	AppState m_appState;

	bool m_previousDownKeyPressed;
	bool m_previousUpKeyPressed;

	SFML_TitleScreen m_titleScreen;

	SFML_GameMenu m_mainMenu;

	SFML_GameWorld m_gameWorld;


	sf::Time m_timeCounter;
	sf::Time m_desiredUpdateTime;
	std::size_t m_FPSCounter;

	void updateFPS(sf::Time elapsedTime);

};


