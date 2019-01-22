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

sf::Vector2f MoveablePlatform::getNextPosition() const {
	auto s = speed;
	if (!reverse) {
		if (goingForward && mPosition.x >= endpoint.x && mPosition.y >= endpoint.y) {
			s = -s;
		}
		else if (!goingForward && mPosition.x <= beginpoint.x && mPosition.y <= beginpoint.y) {
			s = -s;
		}
	} else {
		if (goingForward && mPosition.x <= endpoint.x && mPosition.y <= endpoint.y) {
			s = -s;
		}
		else if (!goingForward && mPosition.x >= beginpoint.x && mPosition.y >= beginpoint.y) {
			s = -s;
		}
	}
	return mPosition + s;
}

void MoveablePlatform::update(const sf::Time& deltaTime) {
	if (!reverse) {
		if (goingForward && mPosition.x >= endpoint.x && mPosition.y >= endpoint.y) {
			goingForward = false;
			speed = -speed;
		}
		else if (!goingForward && mPosition.x <= beginpoint.x && mPosition.y <= beginpoint.y) {
			goingForward = true;
			speed = -speed;
		}
	}
	else {
		if (goingForward && mPosition.x <= endpoint.x && mPosition.y <= endpoint.y) {
			goingForward = false;
			speed = -speed;
		}
		else if (!goingForward && mPosition.x >= beginpoint.x && mPosition.y >= beginpoint.y) {
			goingForward = true;
			speed = -speed;
		}
	}
	mPosition += speed;
	mSprite.setPosition(mPosition);
}
