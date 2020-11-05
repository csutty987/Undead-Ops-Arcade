#pragma once
#include <SFML/Graphics.hpp>
class SFML_SpriteAnimation
{
public:

	SFML_SpriteAnimation();
	~SFML_SpriteAnimation();

	//member function to store memory address of texture to use
	void setSpriteSheet(sf::Texture* spriteTexture);

	//function to add a frame (rectangle and centre)
	void addFrame(sf::IntRect textureRect, sf::Vector2f centre);

	//function returns current frame info
	bool getCurrentFrame(sf::IntRect* rect, sf::Vector2f* centre);

	//function sets delay between showing consecutive frames
	void setFrameTime(float timeperFrame);

	//function returns the delay between showing consecutive frames
	float getTimePerFrame();

	float getFrameTime();

	//returns address of texture used
	sf::Texture* getSpriteSheet();

	//function returns number of frames in this animation
	int getNumberofFrames();

	void getTextureInfo(int newFrame, sf::IntRect * rect, sf::Vector2f* centre);

	//set and gets loop flag
	void setLoop(bool loop);
	bool isLooped() const;

	//set and get interruptible flag
	void setCanbeInterrupted(bool trueorfalse);
	bool canbeInterrupted() const;

	//increment and get frame number, reset animation
	void incrementFrameNumber();
	int getCurrentFrameNumber();
	void resetCurrentAnimation();

	//check if animation is complete, will never be true if anim is looping
	bool isCompleted();

private:
	//frames info
	std::vector<sf::IntRect> m_frameRectangleList;
	std::vector<sf::Vector2f> m_frameCentreList;

	//pointer to the texture object
	sf::Texture* m_spritesheet;

	//current frame numbers and time delay
	int m_currentFrameNumber;
	float m_timeperFrame;

	//animation controls
	bool m_isLoop;
	bool m_canbeInterrupted;
};

