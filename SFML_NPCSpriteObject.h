#pragma once
#include "SFML_AnimatedSpriteObject.h"
class SFML_NPCSpriteObject :
	public SFML_AnimatedSpriteObject
{
public:
			SFML_NPCSpriteObject();
	virtual ~SFML_NPCSpriteObject();

	virtual void	update(float elapsedTime);

	void	setTargetLocation(sf::Vector2f targetLocation);
	void	setMovementSpeed(float speed);

	int		setIdleAnimation(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime);
	int		setWalkingAnimation(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime);
	int		setAttackingAnimation(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime);

	bool	isInVision(sf::Vector2f targetpoint);

	void	toIdleState();
	void	toWalkingState();
	void	toAttackingState();

	void	setHealth(int damage);
	int		getHealth();

private:

	enum NPCState {
		IDLE,
		WALKING,
		ATTACKING
	};

	NPCState		m_state;
	
	sf::Vector2f	m_targetLocation;
	float			m_moveSpeed;
	int				m_health;
	int				m_idleAnimationID;
	int				m_walkingAnimationID;
	int				m_attackingAnimationID;
	bool			m_alive;

	float			m_visionConeAngle;
	float			m_visionRange;

};

