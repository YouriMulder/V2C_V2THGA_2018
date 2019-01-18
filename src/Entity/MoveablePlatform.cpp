#include "MoveablePlatform.hpp"
#include "Platform.hpp"
#include <iostream>

MoveablePlatform::MoveablePlatform(const std::string& filename, const sf::Vector2f& position, const sf::Vector2f& size,
	const sf::IntRect& picturepart, int screenNumber, const sf::Vector2f& moveRange, int amountOfSteps, bool repeated) :

	Platform(filename, position, size, picturepart, screenNumber, repeated),
	beginpoint(position),
	endpoint({ beginpoint.x + moveRange.x, beginpoint.y + moveRange.y})
{
	reverse = !(endpoint.x >= beginpoint.x && endpoint.y >= beginpoint.y);
	speed = { endpoint - position };
	speed.x /= amountOfSteps;
	speed.y /= amountOfSteps;
}

MoveablePlatform::MoveablePlatform(const std::string& filename, const sf::Vector2f& position, const sf::Vector2f& size,
	int screenNumber, const sf::Vector2f& moveRange, int amountOfSteps, bool repeated) :

	Platform(filename, position, size, screenNumber, repeated),
	beginpoint(position),
	endpoint({ beginpoint.x + moveRange.x, beginpoint.y + moveRange.y })
{
	reverse = !(endpoint.x >= beginpoint.x && endpoint.y >= beginpoint.y);
	speed = { endpoint - position };
	speed.x /= amountOfSteps;
	speed.y /= amountOfSteps;
}

void MoveablePlatform::update(const sf::Time& deltaTime) {
	if (!reverse) {
		if (goingForward && mPosition.x >= endpoint.x && mPosition.y >= endpoint.y) {
			goingForward = false;
			speed.x *= -1;
			speed.y *= -1;
		}
		else if (!goingForward && mPosition.x <= beginpoint.x && mPosition.y <= beginpoint.y) {
			goingForward = true;
			speed.x *= -1;
			speed.y *= -1;
		}
	}
	else {
		if (goingForward && mPosition.x <= endpoint.x && mPosition.y <= endpoint.y) {
			goingForward = false;
			speed.x *= -1;
			speed.y *= -1;
		}
		else if (!goingForward && mPosition.x >= beginpoint.x && mPosition.y >= beginpoint.y) {
			goingForward = true;
			speed.x *= -1;
			speed.y *= -1;
		}
	}
	mPosition += speed;
	mSprite.setPosition(mPosition);
}
