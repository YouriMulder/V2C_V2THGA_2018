#include "MoveablePlatform.hpp"
#include "Platform.hpp"
#include <iostream>

MoveablePlatform::MoveablePlatform(const std::string& filename, const sf::Vector2f& position, const sf::Vector2f& size,
	const sf::IntRect& picturepart, int screenNumber, const sf::Vector2f& moveRange, int amountOfSteps, bool repeated) :

	Platform(filename, position, size, picturepart, screenNumber, repeated),
	mBeginpoint(position),
	mEndpoint({ mBeginpoint.x + moveRange.x, mBeginpoint.y + moveRange.y})
{
	mReverse = !(mEndpoint.x >= mBeginpoint.x && mEndpoint.y >= mBeginpoint.y);
	mSpeed = { mEndpoint - position };
	mSpeed.x /= amountOfSteps;
	mSpeed.y /= amountOfSteps;
}

MoveablePlatform::MoveablePlatform(const std::string& filename, const sf::Vector2f& position, const sf::Vector2f& size,
	int screenNumber, const sf::Vector2f& moveRange, int amountOfSteps, bool repeated) :

	Platform(filename, position, size, screenNumber, repeated),
	mBeginpoint(position),
	mEndpoint({ mBeginpoint.x + moveRange.x, mBeginpoint.y + moveRange.y })
{
	mReverse = !(mEndpoint.x >= mBeginpoint.x && mEndpoint.y >= mBeginpoint.y);
	mSpeed = { mEndpoint - position };
	mSpeed.x /= amountOfSteps;
	mSpeed.y /= amountOfSteps;
}

sf::Vector2f MoveablePlatform::getNextPosition() const {
	auto s = mSpeed;
	if (!mReverse) {
		if (mGoingForward && mPosition.x >= mEndpoint.x && mPosition.y >= mEndpoint.y) {
			s = -s;
		}
		else if (!mGoingForward && mPosition.x <= mBeginpoint.x && mPosition.y <= mBeginpoint.y) {
			s = -s;
		}
	} else {
		if (mGoingForward && mPosition.x <= mEndpoint.x && mPosition.y <= mEndpoint.y) {
			s = -s;
		}
		else if (!mGoingForward && mPosition.x >= mBeginpoint.x && mPosition.y >= mBeginpoint.y) {
			s = -s;
		}
	}
	return mPosition + s;
}

void MoveablePlatform::update(const sf::Time& deltaTime) {
	if (!mReverse) {
		if (mGoingForward && mPosition.x >= mEndpoint.x && mPosition.y >= mEndpoint.y) {
			mGoingForward = false;
			mSpeed = -mSpeed;
		}
		else if (!mGoingForward && mPosition.x <= mBeginpoint.x && mPosition.y <= mBeginpoint.y) {
			mGoingForward = true;
			mSpeed = -mSpeed;
		}
	}
	else {
		if (mGoingForward && mPosition.x <= mEndpoint.x && mPosition.y <= mEndpoint.y) {
			mGoingForward = false;
			mSpeed = -mSpeed;
		}
		else if (!mGoingForward && mPosition.x >= mBeginpoint.x && mPosition.y >= mBeginpoint.y) {
			mGoingForward = true;
			mSpeed = -mSpeed;
		}
	}
	mPosition += mSpeed;
	mSprite.setPosition(mPosition);
}
