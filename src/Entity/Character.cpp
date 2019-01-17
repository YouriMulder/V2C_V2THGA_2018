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
	mIsFacingRight(true),
	mIsInAir(false),
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

void Character::addAction(const Action& newAction) {
	mUnperformedActions.push(newAction);
}

void Character::move(const sf::Vector2f& delta) {
	EntityBase::move(delta.x, delta.y);
	mSprite.setPosition(EntityBase::mPosition);
}

void Character::applyMovement(const Action& direction) {
	switch(direction) {
		case Action::Left: {
			updateVelocity(
				sf::Vector2f(-mAcceleration.x, 0.0f)
			);
			break;
		}
		case Action::Right: {
			updateVelocity(
				sf::Vector2f(+mAcceleration.x, 0.0f)
			);
			break;
		}
		case Action::Jump: {
			updateVelocity(
				sf::Vector2f(0.0f, -mAcceleration.y)
			);
			break;
		}
	}
}

void Character::updateState(const Action& action) {
	if(mIsInAir) {
		if(mVelocity.y > 0) {
			mState = State::Jumping;
			return;
		} else if(mVelocity.y < 0) {
			mState = State::Falling;
			return;
		} else {
			mIsInAir = false;
		}
	}
	
	switch(action) {
		case Action::Left: {
			if(mVelocity.x != 0) {
				mState = State::Moving;
			} else {
				mState = State::Idle;
			}
			break;
		}
		case Action::Right: {
			if(mVelocity.x != 0) {
				mState = State::Moving;
			} else {
				mState = State::Idle;
			}			
			break;
		}
		case Action::Jump: {
			mState = State::Jumping;
			break;
		}
		case Action::Punch: {
			mState = State::Attacking;
			break;
		}
		case Action::None: {
			mState = State::Idle;
			break;
		}
	}
}

void Character::animate(const sf::Time& deltaTime) {
	timeSinceLastAnimation += deltaTime;

	updateFacingDirection();
	std::cout << mIsFacingRight << "\n";

	if(mState != mPreviousState) {
		for(const auto& animation : mAnimations) {
			if(mState == animation.first) {
				currentSprite = animation.second.start;
			}
		}
	}

	for(const auto& animation : mAnimations) {
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

void Character::left() {
	applyMovement(Action::Left);
}

void Character::right() {
	applyMovement(Action::Right);
}

void Character::jump() {
	if(!mIsInAir) {
		mIsInAir = true;
		applyMovement(Action::Jump);
	}
}
	

void Character::updateVelocity(const sf::Vector2f& deltaVelocity) {
	mVelocity += sf::Vector2f(deltaVelocity.x * 0.1f, deltaVelocity.y * 0.1f);
}

void Character::updateFacingDirection() {
	std::cout << mVelocity.x << "\n";
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
	applyFrictionOneAxis(mVelocity.x, mAcceleration.x/2);
	applyFrictionOneAxis(mVelocity.y, mAcceleration.y/8);
}

void Character::performAction(const Action& unperformedAction) {
	for(auto& action : mActions) {
		if(unperformedAction == action.first) {
			action.second();
			updateState(action.first);
			return;
		}
	}
}

void Character::update(const sf::Time& deltaTime) {
	if(mUnperformedActions.empty()) {
		updateState(Action::None);
	}

	while(!mUnperformedActions.empty()) {
		performAction(mUnperformedActions.front());
		mUnperformedActions.pop();
	}
	move(mVelocity);
	animate(deltaTime);
	applyFriction();
}

void Character::draw(sf::RenderWindow& window) {
	window.draw(mSprite);
}

void Character::draw(ViewManager& window) {
	window.draw(mSprite);
}