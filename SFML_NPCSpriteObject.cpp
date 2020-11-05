#include "SFML_NPCSpriteObject.h"


SFML_NPCSpriteObject::SFML_NPCSpriteObject()
	: m_targetLocation(0, 0)
	, m_moveSpeed(100.0f)
	, m_state(IDLE)
	, m_idleAnimationID(-1)
	, m_walkingAnimationID(-1)
	, m_attackingAnimationID(-1)
	, m_visionConeAngle(90.0f)
	, m_visionRange(1200.0f)
	, m_health(100)
	, m_alive(true)
{

}

SFML_NPCSpriteObject::~SFML_NPCSpriteObject()
{
}

int SFML_NPCSpriteObject::setIdleAnimation(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime)
{
	m_idleAnimationID = addAnimation(spriteSheetFilename, spriteInfoFilename, animationTime);
	return m_idleAnimationID;
}

int	SFML_NPCSpriteObject::setWalkingAnimation(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime)
{
	m_walkingAnimationID = addAnimation(spriteSheetFilename, spriteInfoFilename, animationTime);
	return m_walkingAnimationID;
}

int SFML_NPCSpriteObject::setAttackingAnimation(std::string spriteSheetFilename, std::string spriteInfoFilename, float animationTime)
{
	m_attackingAnimationID = addAnimation(spriteSheetFilename, spriteInfoFilename, animationTime);
	return m_attackingAnimationID;
}

void SFML_NPCSpriteObject::toIdleState()
{
	m_state = IDLE;
	setCurrentAnimation(m_idleAnimationID);
}

void SFML_NPCSpriteObject::toWalkingState()
{
	m_state = WALKING;
	setCurrentAnimation(m_walkingAnimationID);
}

void SFML_NPCSpriteObject::toAttackingState()
{
	m_state = ATTACKING;
	setCurrentAnimation(m_attackingAnimationID);
}

bool SFML_NPCSpriteObject::isInVision(sf::Vector2f targetpoint)
{
	const float PI = 3.1415f;

	//get npc current location
	sf::Vector2f currentPosition = getPosition();

	//calculate vector from the npcs current position to the target point
	sf::Vector2f vector = targetpoint - currentPosition;

	//calculate distance (l2 norm) between current location and target position
	float distance = sqrt(vector.x * vector.x + vector.y * vector.y);

	//check if distance is outside vision range
	if (distance > m_visionRange)
		return false;

	//get npc's orientation. getRotation() always produces angle in degrees and in 0-360 range
	float faceAngle = getRotation();

	//calculate angle of the vector
	float targetAngle = atan2(vector.y, vector.x);

	//convert to degrees
	targetAngle = targetAngle * 180 / PI;

	//angle could be outside the 0-360 range, so it must be converted to that range.

	while (targetAngle > 360)
		targetAngle = targetAngle - 360;

	while (targetAngle < 0)
		targetAngle = targetAngle + 360;

	//calculate absolute difference between targetAngle and faceAngle
	float angleDifference = fabs(targetAngle - faceAngle);

	//if within half of the vision cone angle then it is within the vision cone
	if (angleDifference <= m_visionConeAngle / 2)
		return true;
	else
		return false;
}

void SFML_NPCSpriteObject::setTargetLocation(sf::Vector2f targetLocation)
{
	m_targetLocation = targetLocation;
}

void SFML_NPCSpriteObject::setMovementSpeed(float speed)
{
	m_moveSpeed = speed;
}

void SFML_NPCSpriteObject::setHealth(int damage)
{
	m_health = m_health - damage;
}

int SFML_NPCSpriteObject::getHealth()
{
	return m_health;
}

void SFML_NPCSpriteObject::update(float elapsedTime)
{

	const float PI = 3.1415f;

	//get npc current location
	sf::Vector2f currentPosition = getPosition();

	//calculate the vector from the npc's current position to the target point
	sf::Vector2f faceDirection = m_targetLocation - currentPosition;

	//calculate distance (l2-norm) between current location and target position
	float distance = sqrt(faceDirection.x * faceDirection.x + faceDirection.y * faceDirection.y);

	//if the distance is less than the displacement to cover in this frame
	if (distance < elapsedTime * m_moveSpeed)
	{
		//this npc has reached its destination point
		setPosition(m_targetLocation);

		
		//Set animation to idle
		if (currentPosition == m_targetLocation)
		{
			toAttackingState();
		}
	}
	else
	{
		//otherwise keep moving

		//rotate npc to face target rotation
		float angle = atan2(faceDirection.y, faceDirection.x);
		setRotation(angle / PI * 180);

		//calculate movement vector
		sf::Vector2f unitMoveVector = sf::Vector2f(cos(angle), sin(angle));
		sf::Vector2f totalMoveVector = unitMoveVector * elapsedTime * m_moveSpeed;

		move(totalMoveVector);
		//set animation to walking
		toWalkingState();
	}


	if (m_health <= 0)
	{
		m_alive = false;
		setPosition(100000, 100000);
	}

	SFML_AnimatedSpriteObject::update(elapsedTime);
}
