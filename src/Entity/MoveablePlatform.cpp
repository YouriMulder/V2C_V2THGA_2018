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

	mSpeed.x *= 25;
	mSpeed.y *= 25;
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

	mSpeed.x *= 25;
	mSpeed.y *= 25;
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
	auto oldPosition = mPosition;
	mPosition += mSpeed * deltaTime.asSeconds();

	for(const auto& entity : mAttachedEntities) {
		(*entity)->move(
			mPosition.x - oldPosition.x,
			mPosition.y - oldPosition.y
		);
	}
	mSprite.setPosition(mPosition);
}

void MoveablePlatform::handleCollision(
	std::vector<std::unique_ptr<EntityBase>*> top, 
	std::vector<std::unique_ptr<EntityBase>*> bottom, 
	std::vector<std::unique_ptr<EntityBase>*> left, 
	std::vector<std::unique_ptr<EntityBase>*> right, 
	CollisionSides hitSides
) {
	mAttachedEntities.clear();
	if(hitSides.top) {
		for(const auto& object : top) {
			mAttachedEntities.push_back(object);
		}
	}
}

void MoveablePlatform::handleNoCollision() {
	mAttachedEntities.clear();
}
