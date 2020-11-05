#include <SFML/Graphics.hpp>

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

const std::string ttfName = "Media/Fonts/constant.ttf";

const float scale = 0.8; /// I used 0.8 so you have space for the title(top) and a "back" button (bottom)
const float invScale = 1 / scale; /// 1.25 in the example

int main()
{
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "SFML Credits");
	sf::Font myFont;
	myFont.loadFromFile(ttfName);

	sf::View myView;
	myView.setSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	myView.setCenter(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	myView.setViewport(sf::FloatRect(0, (1 - scale) / 2, scale, scale));

	///Title
	sf::Text titleCredit("Credits", myFont, SCREEN_HEIGHT / 12);
	titleCredit.setPosition((SCREEN_WIDTH - titleCredit.getGlobalBounds().width) / 2, 0);
	titleCredit.setColor(sf::Color::White);

	///Credits themselves. You can read it from a file using fstreams. The credits are centered, and each text is left aligned.
	///However, each one isn't centered.
	///If you want each to be centered you have to create a sf::Text for each one.
	sf::Text creditText("Creator and Lead Developer\nSantiago Aboy Solanes\nLead Artist\nThat other guy\nThis\nis\nto\nshow\nhow\nit\nappears", myFont, SCREEN_WIDTH / 16);
	creditText.setPosition((SCREEN_WIDTH * invScale - creditText.getGlobalBounds().width) / 2, SCREEN_HEIGHT);
	creditText.setColor(sf::Color::White);

	///Such as this one
	sf::Text creditText2("I am centered", myFont, SCREEN_WIDTH / 16);
	creditText2.setPosition((SCREEN_WIDTH * invScale - creditText2.getGlobalBounds().width) / 2, creditText.getGlobalBounds().top + creditText.getGlobalBounds().height);
	creditText2.setColor(sf::Color::Red);

	while (window.isOpen()) {
		///You can X out the window
		sf::Event myEvent;
		while (window.pollEvent(myEvent)) {
			if (myEvent.type == sf::Event::Closed) {
				window.close();
			}
		}
		///Move the credits upward. You may want this to be tied to a sf::Clock/sf::Time and move it taking into account the delta time
		myView.move(0, SCREEN_HEIGHT * 0.0001);
		///Reset the view if they go "too far"
		if (myView.getCenter().y > SCREEN_HEIGHT * 2 + creditText.getGlobalBounds().height + creditText2.getGlobalBounds().height) {
			myView.setCenter(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		}

		window.clear();
		///set the view for the credits, and then show them
		window.setView(myView);
		window.draw(creditText);
		window.draw(creditText2);
		///set the default view, so that the title doesn't get moved and then show the title
		window.setView(window.getDefaultView());
		window.draw(titleCredit);
		///display all
		window.display();
	}
	return 0;
}