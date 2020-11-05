#include "SFML_Application.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

SFML_Application::SFML_Application(int windowWidth, int windowHeight)
	: m_window(sf::VideoMode(windowWidth, windowHeight), "Undead Ops Arcade", sf::Style::Fullscreen)
	, m_initialised(true)
	, m_screenWidth(windowWidth)
	, m_screenHeight(windowHeight)
	, m_appState(TITLESCREEN)
	, m_previousDownKeyPressed(false)
	, m_previousUpKeyPressed(false)
	, m_titleScreen("Media/Textures/title-screen.png", windowWidth, windowHeight)
	, m_mainMenu("Media/MenuInfo/main-menu.txt", windowWidth, windowHeight)
	, m_desiredUpdateTime(sf::seconds(1.f / 60.f))
	, m_timeCounter(sf::seconds(0))
	, m_FPSCounter(0)
	, m_gameWorld(windowWidth, windowHeight, &m_window)
	

{
	//load fonts to be used for on screen messages
	m_initialised = m_textFont.loadFromFile("Media/Fonts/SegoeMarker.ttf");

	//set message text object to use the font loaded
	m_messageText.setFont(m_textFont);

	//m_mainMenu.setScale(0.85f, 0.85f);
	//m_mainMenu.setPosition(m_screenWidth / 2, m_screenHeight / 2);

	


}

void SFML_Application::update(sf::Time elapsedTime)
{

	//check if player has tried to close window, if so close application
	//m_event triggers when the x window is pressed or alt F4 is pressed
	m_window.pollEvent(m_event);
	if (m_event.type == sf::Event::Closed)
		m_window.close();

	//declare keypressed variables
	bool currentDownKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
	bool currentUpKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
	bool currentEscapeKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);

	int selection;

	//prepare message text and its position
	switch (m_appState)
	{
	case TITLESCREEN:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			m_appState = MAINMENU;
		}
		m_titleScreen.update(elapsedTime);
		break;
	case MAINMENU:
		m_mainMenu.setScale(0.85f, 0.85f);
		m_mainMenu.setPosition(m_screenWidth / 2, m_screenHeight / 2);
		m_previousDownKeyPressed = currentDownKeyPressed;
		m_previousUpKeyPressed = currentUpKeyPressed;
		selection = m_mainMenu.update(elapsedTime);
		if (selection >= 0)
		{
			if (selection == 0)
				m_appState = GAMEPLAYING;
			else if (selection == 1)
				m_appState = OPTIONMENU;
			else if (selection == 2)
				m_appState = CREDITS;
			else if (selection == 3)
				m_appState = EXITING;
		}

		m_messageText.setString("Main Menu Screen");

		break;
	case OPTIONMENU:
		if (currentEscapeKeyPressed)
			m_appState = MAINMENU;
		m_messageText.setString("Option Menu Screen");

		break;
	case GAMEPLAYING:
		if (currentEscapeKeyPressed/* && !m_prevEscapeKeyPressed*/)
			m_appState = MAINMENU;

		m_gameWorld.update(elapsedTime.asSeconds());

		break;

	case CREDITS:
		if (currentEscapeKeyPressed)
			m_appState = MAINMENU;
		
		credits();
		m_appState = MAINMENU;
		m_messageText.setString("Credits Screen");

		break;
	case EXITING:
		m_window.close();
		break;

	}

	m_messageText.setPosition(m_screenWidth, m_screenHeight);
	m_messageText.setCharacterSize(20);

	sf::FloatRect textbox = m_messageText.getLocalBounds();
	m_messageText.setOrigin(textbox.width, textbox.height);
}

void SFML_Application::render()
{
	m_window.clear();

	switch (m_appState)
	{
	case TITLESCREEN:
		m_window.draw(m_titleScreen);
		break;
	case MAINMENU:
		m_window.draw(m_mainMenu);
		break;
	case OPTIONMENU:
		m_window.draw(m_messageText);
		break;
	case CREDITS:
		int credits();
		m_window.draw(m_messageText);
		break;
	case GAMEPLAYING:
		m_window.draw(m_gameWorld);
		m_window.draw(m_messageText);
		break;
	case EXITING:
		break;
	}

	m_window.display();
}

void SFML_Application::run()
{
	if (!m_initialised)
		return;

	sf::Clock clock;

	//variable to track time since update() was executed
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (m_window.isOpen())
	{
		
		//get elapsed time since last loop
		sf::Time elapsedTime = clock.restart();

		timeSinceLastUpdate += elapsedTime;

		while (timeSinceLastUpdate > m_desiredUpdateTime)
		{
			//update application states
			update(m_desiredUpdateTime);

			//subtract m_desiredUpdateTime froM timeSinceLastUpdate
			timeSinceLastUpdate -= m_desiredUpdateTime;
		}

		//calcualte FPS
		updateFPS(elapsedTime);

		//render result to screen
		render();
	}
}

void SFML_Application::updateFPS(sf::Time elapsedTime)
{
	//increment time counter by the time since last render
	m_timeCounter += elapsedTime;

	//increment FPS counter by one
	m_FPSCounter += 1;

	//if one seconds has passed
	if (m_timeCounter >= sf::seconds(1.0f))
	{
		//set message text
		m_messageText.setString("Refresh rate = " + std::to_string(m_FPSCounter) + " fps \n" + "Time between screen refreshes = " + std::to_string(m_timeCounter.asMicroseconds() / m_FPSCounter) + " microseconds \n");

		//take away 1 seconds from time counter
		m_timeCounter -= sf::seconds(1.0f);

		//reset FPS counter
		m_FPSCounter = 0;
	}

}

SFML_Application::~SFML_Application()
{
	
}