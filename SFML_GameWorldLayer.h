#pragma once
#include <SFML/Graphics.hpp>
#include "SFML_2DCamera.h"

class SFML_GameWorldLayer :
	public sf::Drawable
{

public:
	SFML_GameWorldLayer(std::string textureFileName, float parallaxFactor, int viewportWidth, int viewportHeight);

	void followCamera(SFML_2DCamera* camera);

	void setParallaxFactor(float parallaxFactor);
	float getparallaxFactor();

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Texture m_layerTexture;
	sf::VertexArray m_layerVertices;

	float m_parallaxFactor;
};

