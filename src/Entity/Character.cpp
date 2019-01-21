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
	mIsInAir(true),
	mIsJumping(false),
	mPreviousState(Character::State::Idle),
	mState(Character::State::Idle),
	mSpriteWidth(size.x),
	mSpriteHeight(size.y),
	mCurrentSpriteSheetLocation(0,0,size.x,size.y),
	mSelected(false)
{
	mTexture.loadFromFile("../res/Textures/Player/player.png");
	mSprite = sf::Sprite(mTexture, mCurrentSpriteSheetLocation);
	mSprite.scale(2.0f, 2.0f);
	mSize = sf::Vector2f(
		mSprite.getGlobalBounds().width, 
		mSprite.getGlobalBounds().height
	);
}

Character::~Character() { }

void Character::addAction(const Action& newAction) {
	mUnperformedActions.push(newAction);
}

void Character::move(sf::Vector2f& delta) {
	if(delta.x > 0 && restrictedSides.right) {
		delta.x = 0;
	} else if(delta.x < 0 && restrictedSides.left) {
		delta.x = 0;
	}

	if(delta.y < 0 && restrictedSides.top) {
		delta.y = 0;
	} else if(delta.y > 0 && restrictedSides.bottom) {
		delta.y = 0;
	}


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
			mVelocity.y = mJumpForce.y;
/*			updateVelocity(
				sf::Vector2f(0.0f, -10.0f)
			);*/
			break;
		}
	}
}

void Character::updateState(const Action& action) {
	if(mIsInAir) {
		if(mVelocity.y < 0) {
			mState = State::Jumping;
			return;
		} else if(mVelocity.y > 0) {
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

void Character::left() {
	applyMovement(Action::Left);
}

void Character::right() {
	applyMovement(Action::Right);
}

void Character::jump() {
	if(!mIsInAir && !mIsJumping) {
		mIsInAir = true;
		mIsJumping = true;
		applyMovement(Action::Jump);
	}
}

void Character::applyGravity() {
	updateVelocity(sf::Vector2f(mVelocity.x, 2.0f));
}

void Character::updateVelocity(const sf::Vector2f& deltaVelocity) {
	mVelocity += sf::Vector2f(deltaVelocity.x, deltaVelocity.y);

	mVelocity.x = mVelocity.x > +mMaxVelocity.x ? +mMaxVelocity.x : mVelocity.x;
	mVelocity.x = mVelocity.x < -mMaxVelocity.x ? -mMaxVelocity.x : mVelocity.x;
	
	mVelocity.y = mVelocity.y > +mMaxVelocity.y ? +mMaxVelocity.y : mVelocity.y;
	mVelocity.y = mVelocity.y < -mMaxVelocity.y ? -mMaxVelocity.y : mVelocity.y;
}

void Character::resetVelocityY() {
	mVelocity.y = 0;
}

void Character::resetVelocityX() {
	mVelocity.x = 0;
}

void Character::updateFacingDirection() {
	if(mVelocity.x > 0) {
		mIsFacingRight = true;
	} else if(mVelocity.x < 0) {
		mIsFacingRight = false;
	}
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

void Character::handleCollision(
	std::vector<std::unique_ptr<EntityBase>*> top, 
	std::vector<std::unique_ptr<EntityBase>*> bottom, 
	std::vector<std::unique_ptr<EntityBase>*> left, 
	std::vector<std::unique_ptr<EntityBase>*> right, 
		
	CollisionSides hitSides
) {
	restrictedSides = hitSides;

	if(hitSides.bottom) {
		//if (xOffset == -10000) {
		//	xOffset = mPosition.x - (*bottom[0])->getPosition().x;
		//}
		//mPosition = sf::Vector2f{ (*bottom[0])->nextPosition().x + xOffset, (*bottom[0])->nextPosition().y - mSize.y };
		xOffset = mPosition.x - (*bottom[0])->nextPosition().x;
		mPosition = sf::Vector2f((*bottom[0])->getPosition().x + xOffset, (*bottom[0])->getPosition().y - mSize.y);
		setPosition(mPosition);
		mIsInAir = false;
		mIsJumping = false;
		//std::cout << "Bot\n";
	} 
	if(hitSides.top) {
	//	std::cout << "Top\n";
	} 
	if(hitSides.left) {
		mVelocity.x = 0;
	//	std::cout << "Left\n";
	} 
	if(hitSides.right) {
		mVelocity.x = 0;
	//	std::cout << "Right\n";
		//std::cout << "Top\n";
	} 
	//std::cout << "\n";
}

void Character::handleNoCollision() {
	restrictedSides = CollisionSides();
	mIsInAir = true;
}


sf::FloatRect Character::getGlobalBounds() const {
	return mSprite.getGlobalBounds();
}

void Character::update(const sf::Time& deltaTime) {
	mVelocity.x = 0;
	if (mJumpForce.y >= 0) {
		mIsJumping = false;
	}
	if (mIsJumping && mIsInAir) {
		mVelocity.y = mJumpForce.y;
		mJumpForce.y += 0.05;
	}
	else if(mIsInAir) {
		mVelocity.y = mGravity.y;
		if (mGravity.y < 2) {
			mGravity.y += 0.05;
		}
	}
	else {
		mVelocity.y = 0;
		mJumpForce.y = -2;
		mGravity.y = 0;
		mIsJumping = false;
	}
/*
	if(mIsInAir) {
		applyGravity();
	} else {
		resetVelocityX();
	}
*/	
	for(auto & EventManager : actions) {
		EventManager();
	}
	
	if(mUnperformedActions.empty()) {
		updateState(Action::None);
	}

	while(!mUnperformedActions.empty()) {
		performAction(mUnperformedActions.front());
		mUnperformedActions.pop();
	}

	move(mVelocity);
	animate(deltaTime);
}

void Character::animate(const sf::Time& deltaTime) {
	timeSinceLastAnimation += deltaTime;

	updateFacingDirection();

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

void Character::draw(sf::RenderWindow& window) {
	window.draw(mSprite);
}

void Character::draw(ViewManager& window) {
	window.selectDrawingScreen(mScreenNumber);
	window.draw(mSprite);
}

void Character::select(bool selection) {
	mSelected = selection;
}

bool Character::isSelected() {
	return mSelected;
}