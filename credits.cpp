#include <SFML/Graphics.hpp>

int credits()
{
	const int SCREEN_WIDTH = 1920;
	const int SCREEN_HEIGHT = 1080;

	sf::Texture logoTexture;
	sf::Sprite logoSprite;
	const std::string ttfName = "Media/Fonts/SegoeMarker.ttf";

	const float scale = 0.8;
	const float invScale = 1 / scale;

	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Undead Ops Arcade Credits", sf::Style::Fullscreen);
	sf::Font myFont;
	myFont.loadFromFile(ttfName);

	sf::View myView;
	myView.setSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	myView.setCenter(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	myView.setViewport(sf::FloatRect(0, (1 - scale) / 2, scale, scale));

	//logo
	logoTexture.loadFromFile("Media/Textures/logo.jpg");
	logoSprite.setTexture(logoTexture);
	logoSprite.setPosition(SCREEN_WIDTH * 0.95f, SCREEN_HEIGHT * 0.92f);

	sf::Vector2u logoTextureSize = logoTexture.getSize();
	logoSprite.setOrigin(logoTextureSize.x / 2, logoTextureSize.y / 2);

	logoSprite.setTextureRect(sf::IntRect(0, 0, logoTextureSize.x, logoTextureSize.y));

	//credits title
	sf::Text titleCredit("Developed by ToneTwo Studios", myFont, SCREEN_HEIGHT / 12);
	titleCredit.setPosition((SCREEN_WIDTH - titleCredit.getGlobalBounds().width) / 2, 0);
	titleCredit.setFillColor(sf::Color::White);

	//credits contents
	sf::Text creditText("Staff\n \nLead Programmer		Connor Sutcliffe\nLead Artist          		John Doe\nProgrammer            	Jane Doe\nProgrammer		        Jack Smith\nArtist				          Ryan Pablo\nArtist				          Casey Holdahl\n", myFont, SCREEN_WIDTH / 16);
	creditText.setPosition((SCREEN_WIDTH * invScale - creditText.getGlobalBounds().width) / 2, SCREEN_HEIGHT);
	creditText.setCharacterSize(20);
	creditText.setFillColor(sf::Color::White);

	sf::Text creditText2("Acknowledgements\n \nwire.png		                                (http://dementiarunner.deviantart.com/art/wire-seamless-png-549508647)\ndirt.png		                                 (http://hhh316.deviantart.com/art/Seamless-Cracked-Dirt-Texture-347828451)\nfog.png			                              (http ://www.freeiconspng.com/png-images/)\nPlayer character sprite images		 (http ://opengameart.org/content/animated-top-down-survivor-player)\nNPC sprite images		        	      (http ://opengameart.org/content/animated-top-down-zombie)\nBlood sprite images			             (http ://opengameart.org/content/blood-effect-sprite-sheet)\ngame - logo.png		                     (http ://dogtimes.wps60.org/?p=2866)\nmenu.png		                              (https ://wall.alphacoders.com/by_sub_category.php?id=81399)\nSegoeMarker.ttf		                      (https ://www.azfonts.net/families/segoe-marker.html)\nPixel Hearts								    (https://opengameart.org/content/pixel-hearts)\n", myFont, SCREEN_WIDTH / 16);
	creditText2.setPosition((SCREEN_WIDTH * invScale - creditText.getGlobalBounds().width) / 2, /*creditText.getGlobalBounds().top + creditText.getGlobalBounds().height*/SCREEN_HEIGHT);
	creditText2.setCharacterSize(20);
	creditText2.setFillColor(sf::Color::White);

	while (window.isOpen()) {

		bool currentEscapeKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
		if (currentEscapeKeyPressed)
		{
			window.close();
		}

		//window close conditions
		sf::Event myEvent;
		while (window.pollEvent(myEvent)) {
			if (myEvent.type == sf::Event::Closed) {
				window.close();
			}
		}
		//Mmove credits up
		myView.move(0, SCREEN_HEIGHT * 0.00005);
		//Resets view if it goes too far
		if (myView.getCenter().y > SCREEN_HEIGHT * 2 + creditText.getGlobalBounds().height) {
			myView.setCenter(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		}
	
		//set views and draw credits & title
		window.clear();
		window.setView(myView);
		window.draw(creditText);
		window.draw(creditText2);
		window.setView(window.getDefaultView());
		window.draw(titleCredit);
		window.draw(logoSprite);
		window.display();

	}
	return 0;
}

