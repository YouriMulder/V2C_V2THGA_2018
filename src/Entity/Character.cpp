#include "Character.hpp"

#include "../World/Physics.hpp"

#include <iostream>

Character::Character(sf::Vector2f maxVelocity, sf::Vector2f acceleration):
	mVelocity(0.0f, 0.0f),
	mMaxVelocity(maxVelocity), 
	mAcceleration(acceleration),
	mMovingDirection(Character::Direction::None)
{
	mTexture.loadFromFile("../res/textures/player/player.png");
	mSprite = sf::Sprite(mTexture);
}

Character::~Character() { }

void Character::move(const sf::Vector2f& delta) {
	EntityBase::move(delta.x, delta.y);
	mSprite.setPosition(EntityBase::mPosition);
}

void Character::setMoveDirection(const Direction& newDirection) {
	mMovingDirection = newDirection;
}

void Character::updateVelocity(const sf::Vector2f& deltaVelocity) {
	mVelocity += deltaVelocity;
	if(mVelocity.x > mMaxVelocity.x) {
		mVelocity.x = mMaxVelocity.x;
	} else if(mVelocity.x < -mMaxVelocity.x) {
		mVelocity.x = -mMaxVelocity.x;
	}

	if(mVelocity.y > mMaxVelocity.y) {
		mVelocity.y = mMaxVelocity.y;
	} else if(mVelocity.y < -mMaxVelocity.y) {
		mVelocity.y = -mMaxVelocity.y;
	}

}

void Character::applyFrictionOneAxis(float& axisVelocity) {
	if(axisVelocity > 0) {
		axisVelocity -= Physics::airResistance;
		axisVelocity = axisVelocity < 0 ? 0 : axisVelocity; 
	} else if(axisVelocity < 0) {
		axisVelocity += Physics::airResistance;
		axisVelocity = axisVelocity > 0 ? 0 : axisVelocity; 
	}
}

void Character::applyFriction() {
	applyFrictionOneAxis(mVelocity.x);
	applyFrictionOneAxis(mVelocity.y);
}

void Character::update() {
	switch(mMovingDirection) {
		case Direction::Down: {
			updateVelocity(
				sf::Vector2f(0.0f, +mAcceleration.y)
			);
			break;
		}
		case Direction::Up: {
			updateVelocity(
				sf::Vector2f(0.0f, -mAcceleration.y)
			);
			break;
		}
		case Direction::Left: {
			updateVelocity(
				sf::Vector2f(-mAcceleration.x, 0.0f)
			);
			break;
		}
		case Direction::Right: {
			updateVelocity(
				sf::Vector2f(+mAcceleration.x, 0.0f)
			);
			break;
		}
		case Direction::None: {
			applyFriction();
			break;
		}
	}
	move(mVelocity);
}

void Character::draw(sf::RenderWindow& window) {
	window.draw(mSprite);
}