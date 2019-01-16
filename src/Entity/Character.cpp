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
	mIsFacingRight(true),
	mPreviousState(Character::State::Idle),
	mState(Character::State::Idle),
	mSpriteWidth(size.x),
	mSpriteHeight(size.y),
	mCurrentSpriteSheetLocation(0,0,size.x,size.y)
{
	mTexture.loadFromFile("../res/Textures/Player/player.png");
	mSprite = sf::Sprite(mTexture, mCurrentSpriteSheetLocation);
	mSprite.scale(2.0f, 2.0f);
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
		case Direction::Left: {
			setState(Character::State::Moving);
			updateVelocity(
				sf::Vector2f(-mAcceleration.x, 0.0f)
			);
			break;
		}
		case Direction::Right: {
			setState(Character::State::Moving);	
			updateVelocity(
				sf::Vector2f(+mAcceleration.x, 0.0f)
			);
			break;
		}
		case Direction::None: {
			setState(Character::State::Idle);
			applyFriction();
			break;
		}
	}
}


void Character::animate(const sf::Time& deltaTime) {
	timeSinceLastAnimation += deltaTime;

	updateFacingDirection();

	if(mState != mPreviousState) {
		for(const auto& animation : animations) {
			if(mState == animation.first) {
				currentSprite = animation.second.start;
			}
		}
	}

	for(const auto& animation : animations) {
		if(mState == animation.first) {
			
			if(timeSinceLastAnimation >= animation.second.displayTime) {
				timeSinceLastAnimation = sf::seconds(0.0f);
				currentSprite.x++;


				if(currentSprite == animation.second.end) {					
					currentSprite = animation.second.start;
				}
				
				if(mIsFacingRight) {
					mSprite.setTextureRect(
						sf::IntRect(
							currentSprite.x * animation.second.size.x,
							currentSprite.y * animation.second.size.y,
							animation.second.size.x,
							animation.second.size.y
						)
					);
				} else {
					mSprite.setTextureRect(
						sf::IntRect(
							(currentSprite.x + 1) * animation.second.size.x,
							currentSprite.y * animation.second.size.y,
							-animation.second.size.x,
							animation.second.size.y
						)
					);
				}
			}
		}
	}
	mPreviousState = mState;
}

void Character::updateVelocity(const sf::Vector2f& deltaVelocity) {
	mVelocity = sf::Vector2f(deltaVelocity.x * 0.1f, deltaVelocity.y * 0.1f);
}

void Character::updateFacingDirection() {
	if(mVelocity.x > 0) {
		mIsFacingRight = true;
	} else if(mVelocity.x < 0) {
		mIsFacingRight = false;
	}
}

void Character::setState(const State& newState) {
	mState = newState;
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

void Character::update(const sf::Time& deltaTime) {
	move(mVelocity);
	if(mPosition.y + mSprite.getGlobalBounds().height <= 900) {
		mPosition.y++;
	}
	animate(deltaTime);
}

void Character::draw(sf::RenderWindow& window) {
	window.draw(mSprite);
}

void Character::draw(ViewManager& window) {
	window.draw(mSprite);
}