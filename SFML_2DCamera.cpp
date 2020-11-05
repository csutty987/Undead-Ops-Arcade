#include "SFML_2DCamera.h"

SFML_2DCamera::SFML_2DCamera(int projectionWindowWidth, int projectionWindowHeight)
	: m_cameraPosition(0, 0)
	, m_cameraWindowSize(projectionWindowWidth, projectionWindowHeight)
	, m_cameraZoom(1)
{


}

void SFML_2DCamera::setPosition(sf::Vector2f target)
{
	m_cameraPosition = target;
}

sf::FloatRect SFML_2DCamera::getCameraWindow(float parallaxFactor)
{

	//parallax factor should be larger than 0, if parallax factor is less than 1, the window will be smaller and appears to scroll faster, otherwise the window will be bigger and appears to scroll slower
	sf::FloatRect window;

	window.left = m_cameraPosition.x - m_cameraWindowSize.x / 2 * m_cameraZoom * parallaxFactor;
	window.top = m_cameraPosition.y - m_cameraWindowSize.y / 2 * m_cameraZoom * parallaxFactor;

	window.width = m_cameraWindowSize.x * m_cameraZoom * parallaxFactor;
	window.height = m_cameraWindowSize.y * m_cameraZoom * parallaxFactor;

	return window;
}

void SFML_2DCamera::zoomUp(float elapsedTime)
{
	float zoomSpeed = 60.0f;
	float zoomChange = m_cameraZoom * 0.1f * elapsedTime * zoomSpeed;
	m_cameraZoom = m_cameraZoom - zoomChange;
}

void SFML_2DCamera::zoomDown(float elapsedTime)
{
	float zoomSpeed = 60.0f;
	float zoomChange = m_cameraZoom * 0.1f * elapsedTime * zoomSpeed;
	m_cameraZoom = m_cameraZoom + zoomChange;
}

sf::Transform SFML_2DCamera::getViewTransform() const
{
	//transform the coordinate from world space to camera spacec
	//centered at the middle of the visible window
	//e.g. if camera is at 10,20 an object at 10,20 will be at center
	sf::Transform transform = sf::Transform::Identity;
	transform.translate(m_cameraPosition);
	return transform.getInverse();
}

sf::Transform SFML_2DCamera::getProjTransform() const
{
	//transform coordinate from camera to screen space
	//note the screen space origin point is at top left corner
	//so we effectively shift coordinate by half the screen dimension
	sf::Transform transform = sf::Transform::Identity;
	transform.translate(m_cameraWindowSize.x / 2, m_cameraWindowSize.y / 2);
	transform.scale(1.0f / m_cameraZoom, 1.0f / m_cameraZoom);
	return transform;
}

SFML_2DCamera::~SFML_2DCamera()
{

}