#include "SFML_GameWorld.h"

SFML_GameWorld::SFML_GameWorld(int windowWidth, int windowHeight, sf::RenderWindow* parentWindow)
	: m_windowWidth(windowWidth)
	, m_windowHeight(windowHeight)
	, m_camera(windowWidth, windowHeight)
{
	SFML_GameWorldLayer* wall = new SFML_GameWorldLayer("Media/Textures/wall.png", 1.0f, windowWidth, windowHeight);
	m_gameWorldLayerList.push_back(wall);

	m_cameraPosition = sf::Vector2f(0, 0);

	SFML_GameWorldLayer* wire = new SFML_GameWorldLayer("Media/Textures/wire.png", 0.3f, windowWidth, windowHeight);
	m_gameWorldLayerList.push_back(wire);

	SFML_GameWorldLayer* fog = new SFML_GameWorldLayer("Media/Textures/fog.png", 0.5f, windowWidth, windowHeight);
	m_gameWorldLayerList.push_back(fog);


	//this night layer makes the whole game too dark to really see what's going on. Need to set timer for it and add flashlight lighting simulation
	//SFML_GameWorldLayer* night = new SFML_GameWorldLayer("Media/Textures/night.png", 0.2f, windowWidth, windowHeight);
	//m_gameWorldLayerList.push_back(night);

	//HUD Border
	hudTexture.loadFromFile("Media/Textures/hud.png");
	hudSprite.setTexture(hudTexture);
	hudSprite.setPosition(m_windowWidth * 0.5f, m_windowHeight * 0.5f);

	sf::Vector2u hudTextureSize = hudTexture.getSize();
	hudSprite.setOrigin(hudTextureSize.x / 2, hudTextureSize.y / 2);

	hudSprite.setTextureRect(sf::IntRect(0, 0, hudTextureSize.x, hudTextureSize.y));

	//health HUD
	healthTexture.loadFromFile("Media/Textures/Pixel Hearts/PNGs/0.bmp");
	healthSprite.setTexture(healthTexture);
	healthSprite.setPosition(m_windowWidth * 0.10f, m_windowHeight * 0.10f);

	sf::Vector2u healthTextureSize = healthTexture.getSize();
	healthSprite.setOrigin(healthTextureSize.x / 2, healthTextureSize.y / 2);

	healthSprite.setTextureRect(sf::IntRect(0, 0, healthTextureSize.x, healthTextureSize.y));

	//sorts game world in descending parallaxfactor order
	std::sort(m_gameWorldLayerList.begin(), m_gameWorldLayerList.end(), layerSortFunction);

	//m_spriteObject.setDefaultTexture("Media/Textures/soldier.png", "Media/SpriteInfo/soldier.txt");
	//m_spriteObject.setPosition(0, 0);

	m_parentWindow = parentWindow;

	//m_animatedObject = new SFML_AnimatedSpriteObject();
	//m_idleAnimationID = m_animatedObject->addAnimation("Media/Textures/blood.png", "Media/SpriteInfo/blood.txt", 1.0f);
	//m_animatedObject->setPosition(0, 0);
	//m_animatedObject->setCurrentAnimation(m_idleAnimationID);

	//zombie handling
	m_numberofZombies = 10;

	for (int i = 0; i < m_numberofZombies; i++)
	{
		SFML_NPCSpriteObject* zombie = new SFML_NPCSpriteObject();
		zombie->setIdleAnimation("Media/Textures/zombie-idle.png", "Media/SpriteInfo/zombie-idle.txt", 1.0f);
		zombie->setWalkingAnimation("Media/Textures/zombie-move.png", "Media/SpriteInfo/zombie-move.txt", 1.0f);
		zombie->setAttackingAnimation("Media/Textures/zombie-attack.png", "Media/SpriteInfo/zombie-attack.txt", 1.0f);

		zombie->setPosition(rand() % 4000 - 2000, rand() % 4000 - 2000);
		zombie->setTargetLocation(sf::Vector2f(rand() % 4000 - 2000, rand() % 4000 - 2000));
		m_zombieCharacterList.push_back(zombie);
		
	}

	blood = new SFML_AnimatedSpriteObject();
	m_bloodAnimationID = blood->addAnimation("Media/Textures/blood.png", "Media/SpriteInfo/blood.txt", 1.0f);

	m_playerCharacter = new SFML_PlayableSpriteObject();
	m_playerCharacter->setFlashlightIdleAnimation("Media/Textures/hero_flashlight_idle.png", "Media/SpriteInfo/hero_flashlight_idle.txt", 1.0f);
	m_playerCharacter->setFlashlightWalkingAnimation("Media/Textures/hero_flashlight_move.png", "Media/SpriteInfo/hero_flashlight_move.txt", 1.0f);
	m_playerCharacter->setFlashlightMeleeAnimation("Media/Textures/hero_flashlight_melee.png", "Media/SpriteInfo/hero_flashlight_melee.txt", 1.0f);

	m_playerCharacter->setKnifeIdleAnimation("Media/Textures/hero_knife_idle.png", "Media/SpriteInfo/hero_knife_idle.txt", 1.0f);
	m_playerCharacter->setKnifeWalkingAnimation("Media/Textures/hero_knife_move.png", "Media/SpriteInfo/hero_knife_move.txt", 1.0f);
	m_playerCharacter->setKnifeMeleeAnimation("Media/Textures/hero_knife_melee.png", "Media/SpriteInfo/hero_knife_melee.txt", 1.0f);

	m_playerCharacter->setPistolIdleAnimation("Media/Textures/hero_pistol_idle.png", "Media/SpriteInfo/hero_pistol_idle.txt", 1.0f);
	m_playerCharacter->setPistolWalkingAnimation("Media/Textures/hero_pistol_move.png", "Media/SpriteInfo/hero_pistol_move.txt", 1.0f);
	m_playerCharacter->setPistolMeleeAnimation("Media/Textures/hero_pistol_melee.png", "Media/SpriteInfo/hero_pistol_melee.txt", 1.0f);
	m_playerCharacter->setPistolReloadAnimation("Media/Textures/hero_pistol_reload.png", "Media/SpriteInfo/hero_pistol_reload.txt", 1.0f);
	m_playerCharacter->setPistolShootAnimation("Media/Textures/hero_pistol_shoot.png", "Media/SpriteInfo/hero_pistol_shoot.txt", 1.0f);

	m_playerCharacter->setRifleIdleAnimation("Media/Textures/hero_rifle_idle.png", "Media/SpriteInfo/hero_rifle_idle.txt", 1.0f);
	m_playerCharacter->setRifleWalkingAnimation("Media/Textures/hero_rifle_move.png", "Media/SpriteInfo/hero_rifle_move.txt", 1.0f);
	m_playerCharacter->setRifleMeleeAnimation("Media/Textures/hero_rifle_melee.png", "Media/SpriteInfo/hero_rifle_melee.txt", 1.0f);
	m_playerCharacter->setRifleReloadAnimation("Media/Textures/hero_rifle_reload.png", "Media/SpriteInfo/hero_rifle_reload.txt", 1.0f);
	m_playerCharacter->setRifleShootAnimation("Media/Textures/hero_rifle_shoot.png", "Media/SpriteInfo/hero_rifle_shoot.txt", 1.0f);


	m_playerCharacter->equipFlashlight();
	m_playerCharacter->toIdleState();

	m_playerCharacter->setPosition(0, 0);
}

void SFML_GameWorld::update(float elapsedTime)
{
	processEvents(elapsedTime);

	//m_animatedObject->update(elapsedTime);
	//m_spriteObject.update(elapsedTime);
	//m_camera.setPosition(m_cameraPosition);

	if (m_playerCharacter->getHealth() >= 50)
	{
		healthTexture.loadFromFile("Media/Textures/Pixel Hearts/PNGs/1.bmp");
		healthSprite.setTexture(healthTexture);
		healthSprite.setPosition(m_windowWidth * 0.35f, m_windowHeight * 0.35f);

		sf::Vector2u healthTextureSize = healthTexture.getSize();
		healthSprite.setOrigin(healthTextureSize.x / 2, healthTextureSize.y / 2);

		healthSprite.setTextureRect(sf::IntRect(0, 0, healthTextureSize.x, healthTextureSize.y));
	}
	else if (m_playerCharacter->getHealth() >= 10)
	{
		healthTexture.loadFromFile("Media/Textures/Pixel Hearts/PNGs/2.bmp");
		healthSprite.setTexture(healthTexture);
		healthSprite.setPosition(m_windowWidth * 0.35f, m_windowHeight * 0.35f);

		sf::Vector2u healthTextureSize = healthTexture.getSize();
		healthSprite.setOrigin(healthTextureSize.x / 2, healthTextureSize.y / 2);

		healthSprite.setTextureRect(sf::IntRect(0, 0, healthTextureSize.x, healthTextureSize.y));
	}

	for (int counter = 0; counter < m_gameWorldLayerList.size(); counter++)
	{
		m_gameWorldLayerList[counter]->followCamera(&m_camera);
	}

	//update NPCs
	for (unsigned int counter = 0; counter < m_zombieCharacterList.size(); counter++)
	{
		m_zombieCharacterList[counter]->update(elapsedTime);
	}


	m_playerCharacter->update(elapsedTime);
	m_camera.setPosition(m_playerCharacter->getWorldPosition());

	//updates bullets
	for (unsigned int counter = 0; counter < m_bulletList.size(); counter++)
	{
		m_bulletList[counter]->update(elapsedTime);
	}
}

void SFML_GameWorld::processEvents(float elapsedTime)
{
	//camera controls
	/*float cameraPanSpeed = 60.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_cameraPosition.x = m_cameraPosition.x - cameraPanSpeed * elapsedTime;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_cameraPosition.x = m_cameraPosition.x + cameraPanSpeed * elapsedTime;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		m_cameraPosition.y = m_cameraPosition.y - cameraPanSpeed * elapsedTime;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_cameraPosition.y = m_cameraPosition.y + cameraPanSpeed * elapsedTime;
	}*/

	//zoom controls
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
	{
		m_camera.zoomUp(elapsedTime);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
	{
		m_camera.zoomDown(elapsedTime);
	}

	//weapon switching
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		m_playerCharacter->equipKnife();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		m_playerCharacter->equipPistol();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		m_playerCharacter->equipRifle();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
	{
		m_playerCharacter->equipFlashlight();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		m_playerCharacter->toReloadState();
	}

	//get camera transform world to screen
	sf::Transform transform;
	transform = m_camera.getProjTransform() * m_camera.getViewTransform();

	//inverse - screen to world
	sf::Transform inv = transform.getInverse();

	//get mouse position in screen space
	sf::Vector2f mouseScreenPosition = sf::Vector2f(sf::Mouse::getPosition(*m_parentWindow));

	//convert to world space coordinate
	sf::Vector2f wp = inv.transformPoint(mouseScreenPosition);

	//get sprite global bounding rectangle
	sf::FloatRect rect = m_spriteObject.getGlobalBounds();

	SFML_BulletSpriteObject* bullet = m_playerCharacter->processEvents(elapsedTime, transform, mouseScreenPosition);
	if (bullet)
		m_bulletList.push_back(bullet);

	sf::Vector2f PCPos = m_playerCharacter->getWorldPosition();

	if (rect.contains(PCPos))
	{
		//if player inside the bounding rectangle, attack
		m_spriteObject.setColor(sf::Color(255, 0, 0));
	}
	else
	{
		//otherwise revert back to normal colour (white)
		m_spriteObject.setColor(sf::Color(255, 255, 255));
	}

	//vision cone
	for (unsigned int counter = 0; counter < m_zombieCharacterList.size(); counter++)
	{
		if (m_zombieCharacterList[counter]->isInVision(PCPos))
		{
			//player is within npcs vision cone
			m_zombieCharacterList[counter]->setColor(sf::Color(255, 0, 0));

			m_zombieCharacterList[counter]->setTargetLocation(PCPos);

		}
		else
		{
			//player is outside npcs vision cone
			m_zombieCharacterList[counter]->setColor(sf::Color(255, 255, 255));
			
		}
	}
	
	//COLLISION DETECTION

	//get bounding box for playable character
	sf::FloatRect PCBoundingBox = m_playerCharacter->getGlobalBounds();

	//get bounding boxes for zombies
	sf::FloatRect NPCBoundingBox[10];

	//check collision for each zombie
	for (unsigned int counter0 = 0; counter0 < m_bulletList.size(); counter0++)
	{
		for (unsigned int counter = 0; counter < m_zombieCharacterList.size(); counter++)
		{
			NPCBoundingBox[counter] = m_zombieCharacterList[counter]->getGlobalBounds();

			if (PCBoundingBox.intersects(NPCBoundingBox[counter]))
			{
			
				m_zombieCharacterList[counter]->toAttackingState();
				//deal damage to player
				m_playerCharacter->setHealth(20);

				
			}

			//get bounding boxes for bullets
			sf::FloatRect bulletBox = m_bulletList[counter0]->getGlobalBounds();

			if (bulletBox.intersects(NPCBoundingBox[counter]))
			{

					//spawn blood (currently not working)
					blood->setPosition(m_zombieCharacterList[counter]->getPosition());
					blood->setCurrentAnimation(m_bloodAnimationID);

					//deal damage to NPC
					int damage = m_playerCharacter->getDamage();
					m_zombieCharacterList[counter]->setHealth(damage);

					//highlight zombie with more red
					m_zombieCharacterList[counter]->setColor(sf::Color(128, 0, 0));
			}
		}
	}
	
}



void SFML_GameWorld::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//render each game world layer with parallax factor >= 1.0
	for (unsigned int counter = 0; counter < m_gameWorldLayerList.size(); counter++)
	{
		if (m_gameWorldLayerList[counter]->getparallaxFactor() >= 1.0f)
			target.draw(*m_gameWorldLayerList[counter]);
	}

	//get camera view-projection transform and set it to the renderstate
	sf::RenderStates renderState;
	renderState.transform = m_camera.getProjTransform() * m_camera.getViewTransform();

	//zombie/NPC draw
	for (unsigned int counter = 0; counter < m_zombieCharacterList.size(); counter++)
	{
		target.draw(*m_zombieCharacterList[counter], renderState);
	}

	target.draw(*m_playerCharacter, renderState);

	//draw each bullet object in the list
	for (unsigned int counter = 0; counter < m_bulletList.size(); counter++)
	{
		target.draw(*m_bulletList[counter], renderState);
	}

    //target.draw(*m_animatedObject, renderState);
	//draw sprite object with the renderstate
	//target.draw(m_spriteObject, renderState);

	
	//render each game world layer with parallax factor 1
	for (unsigned int counter = 0; counter < m_gameWorldLayerList.size(); counter++)
	{
		if (m_gameWorldLayerList[counter]->getparallaxFactor() < 1.0f)
			target.draw(*m_gameWorldLayerList[counter]);
	}

	target.draw(healthSprite);
	target.draw(hudSprite);

	
}


bool SFML_GameWorld::layerSortFunction(SFML_GameWorldLayer* a, SFML_GameWorldLayer* b)
{
	return (a->getparallaxFactor() > b->getparallaxFactor());
}

SFML_GameWorld::~SFML_GameWorld()
{
	for (std::vector<SFML_GameWorldLayer*>::iterator it = m_gameWorldLayerList.begin();
		it != m_gameWorldLayerList.end();
		it++)

	{
		delete (*it);
	}
	m_gameWorldLayerList.clear();

	//clear memory space used for animated object
	delete m_animatedObject;
}