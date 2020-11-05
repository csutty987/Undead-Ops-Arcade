#pragma once
#include <SFML/Graphics.hpp>
#include "SFML_GameWorldLayer.h"
#include "SFML_SpriteObject.h"
#include "SFML_AnimatedSpriteObject.h"
#include "SFML_NPCSpriteObject.h"
#include "SFML_PlayableSpriteObject.h"
#include "SFML_BulletSpriteObject.h"

class SFML_GameWorld :
	public sf::Drawable
{
public:
	SFML_GameWorld(int windowWidth, int windowHeight, sf::RenderWindow* parentWindow);
	~SFML_GameWorld();

	void update(float elapsedTime);

private:
	void processEvents(float elapsedTime);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	int m_windowWidth;
	int m_windowHeight;

	std::vector<SFML_GameWorldLayer*> m_gameWorldLayerList;
	SFML_2DCamera m_camera;
	sf::Vector2f m_cameraPosition;


	sf::Texture healthTexture;
	sf::Sprite healthSprite;

	sf::Texture hudTexture;
	sf::Sprite hudSprite;

	SFML_SpriteObject m_spriteObject;

	sf::RenderWindow* m_parentWindow;

	//sorts gameworldlayer array
	static bool layerSortFunction(SFML_GameWorldLayer* a, SFML_GameWorldLayer* b);

	SFML_AnimatedSpriteObject* m_animatedObject;
	int m_idleAnimationID;

	std::vector<SFML_NPCSpriteObject*> m_zombieCharacterList;
	int m_numberofZombies;

	SFML_PlayableSpriteObject* m_playerCharacter;

	SFML_AnimatedSpriteObject* blood;
	int m_bloodAnimationID;

	std::vector<SFML_BulletSpriteObject*> m_bulletList;


};

