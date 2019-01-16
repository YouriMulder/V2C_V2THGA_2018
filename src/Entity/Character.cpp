#include "Character.hpp"

#include "../World/Physics.hpp"
#include <iostream>

Character::Character(
		const sf::Vector2f& position,
		const sf::Vector2f& size,
		int screenNumber,
		const sf::Vector2f& maxVelocity, 
		const sf::Vector2f& acceleration
):
	EntityBase(position, size, screenNumber),
	mVelocity(0.0f, 0.0f),
	mMaxVelocity(maxVelocity), 
	mAcceleration(acceleration),
	mMovingDirection(Character::Direction::None),
	mSpriteWidth(size.x),
	mSpriteHeight(size.y),
	mCurrentSpriteSheetLocation(0,0,size.x,size.y),
	mIsFacingRight(true)
{
	mTexture.loadFromFile("../res/Textures/Player/player.png");
	mSprite = sf::Sprite(mTexture, mCurrentSpriteSheetLocation);
}

Character::~Character() { }

void Character::move(const sf::Vector2f& delta) {
	EntityBase::move(delta.x, delta.y);
	mSprite.setPosition(EntityBase::mPosition);
}

void Character::setMoveDirection(const Direction& newDirection) {
	mMovingDirection = newDirection;
	
	applyMovement();
}

void Character::applyMovement() {
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
}


void Character::animate() {
	updateFacingDirection();
	if(mIsFacingRight) {
		if(mCurrentSpriteSheetLocation.width) {
			mCurrentSpriteSheetLocation.width = -mCurrentSpriteSheetLocation.width;
		}
	}
	
	if (mCurrentSpriteSheetLocation.left == mSpriteWidth * 3) {
        mCurrentSpriteSheetLocation.left = 0;
	} else {
        mCurrentSpriteSheetLocation.left += mSpriteWidth;
	}
	mSprite.setTextureRect(mCurrentSpriteSheetLocation);
}

void Character::updateVelocity(const sf::Vector2f& deltaVelocity) {
	mVelocity = deltaVelocity;
}

void Character::updateFacingDirection() {
	if(mVelocity.x > 0) {
		mIsFacingRight = true;
	} else if(mVelocity.x < 0) {
		mIsFacingRight = false;
	}
}

void Character::applyFrictionOneAxis(float& axisVelocity, const float& friction) {
	if(axisVelocity > 0) {
		axisVelocity -= friction;
		axisVelocity = axisVelocity < 0 ? 0 : axisVelocity; 
	} else if(axisVelocity < 0) {
		axisVelocity += friction;
		axisVelocity = axisVelocity > 0 ? 0 : axisVelocity; 
	}
}

void Character::applyFriction() {
	applyFrictionOneAxis(mVelocity.x, mAcceleration.x);
	applyFrictionOneAxis(mVelocity.y, mAcceleration.y);
}

void Character::update() {
	move(mVelocity);
	if(mPosition.y + mSprite.getGlobalBounds().height <= 900) {
		mPosition.y++;
	}
	animate();
}

void Character::draw(sf::RenderWindow& window) {
	window.draw(mSprite);
}

void Character::draw(ViewManager& window) {
	window.draw(mSprite);
}