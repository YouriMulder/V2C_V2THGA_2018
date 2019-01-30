#include "Character.hpp"

#include "../World/Physics.hpp"
#include "Projectile.hpp"
#include <iostream>
#include <cstdint>
#include <memory>
#include <optional>


template<typename T>
std::ostream& operator<<(typename std::enable_if<std::is_enum<T>::value, std::ostream>::type& stream, const T& e) {
    return stream << static_cast<typename std::underlying_type<T>::type>(e);
}

Character::Character(
	const sf::Vector2f& position,
	const sf::Vector2f& size,
	int screenNumber,
	const sf::Vector2f& maxVelocity, 
	const sf::Vector2f& acceleration,
	const std::string& characterSheetPath
):
	EntityBase(position, size, screenNumber),
	id(nextId),
	mVelocity(0.0f, 0.0f),
	mMaxVelocity(maxVelocity),
	mAcceleration(acceleration),
	mIsFacingRight(true),
	mIsInAir(true),
	mIsJumping(false),
	mCanDoubleJump(false),
	mIsRunning(false),
	mIsShooting(false),
	mIsFinished(false),
	mPreviousState(Character::State::Idle),
	mState(Character::State::Idle)
{
	mTexture.loadFromFile(characterSheetPath);
	mSprite = sf::Sprite(mTexture, 
		sf::IntRect(0,0, static_cast<unsigned int>(size.x), static_cast<unsigned int>(size.y))
	);
	mSprite.setPosition(EntityBase::mPosition);
	mSize = sf::Vector2f(
		mSprite.getGlobalBounds().width, 
		mSprite.getGlobalBounds().height
	);
	bindActions();
	bindAnimations();
}

Character::~Character() { }

void Character::addAction(const Action& newAction) {
	mUnperformedActions.push(newAction);
}

void Character::bindAction(const EventManager& event) {
	actions.push_back(event);
}

void Character::bindAnimation(
	const State& state, 
	const AnimationSequence& animationSequence) 
{
	mAnimations.push_back(std::make_pair(state, animationSequence));
}

void Character::move(sf::Vector2f& delta) {
	if(delta.x > 0 && mRestrictedSides.right) {
		delta.x = 0;
	} else if(delta.x < 0 && mRestrictedSides.left) {
		delta.x = 0;
	}

	if(delta.y < 0 && mRestrictedSides.top) {
		delta.y = 0;
	} else if(delta.y > 0 && mRestrictedSides.bottom) {
		delta.y = 0;
	}


	EntityBase::move(delta.x, delta.y);
	mSprite.setPosition(EntityBase::mPosition);
}

void Character::applyMovement(const Action& direction) {
	auto deltaVelocity = mAcceleration;
	
	switch(direction) {
		case Action::Left: {
			updateVelocity(
				sf::Vector2f(-deltaVelocity.x, 0.0f)
			);
			break;
		}
		case Action::Right: {
			updateVelocity(
				sf::Vector2f(+deltaVelocity.x, 0.0f)
			);
			break;
		}
		case Action::Jump: {
			mVelocity.y = mStartingJumpForce;
			break;
		}
	}
}

void Character::updateFacingDirection() {
	if(mVelocity.x > 0) {
		mIsFacingRight = true;
	} else if(mVelocity.x < 0) {
		mIsFacingRight = false;
	}
}

void Character::updateVelocity(const sf::Vector2f& deltaVelocity) {
	auto maxVelocity = mMaxVelocity;
	if(mIsRunning) {
		maxVelocity.x *= 2;
	}
	mVelocity += sf::Vector2f(deltaVelocity.x, deltaVelocity.y);

	mVelocity.x = mVelocity.x > +maxVelocity.x ? +maxVelocity.x : mVelocity.x;
	mVelocity.x = mVelocity.x < -maxVelocity.x ? -maxVelocity.x : mVelocity.x;	
}

void Character::resetVelocityY() {
	mVelocity.y = 0;
}

void Character::resetVelocityX() {
	mVelocity.x = 0;
}

bool Character::isMovingX() const {
	return mVelocity.x != 0;
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
			if(isMovingX()) {
				mState = State::Moving;
				updateFacingDirection();
			} else {
				mState = State::Idle;
			}
			break;
		}
		case Action::Right: {
			if(isMovingX()) {
				mState = State::Moving;
				updateFacingDirection();
			} else {
				mState = State::Idle;
			}
			break;
		}
		case Action::Jump: {
			mState = State::Jumping;
			break;
		}
		case Action::Run: {
			if(isMovingX()) {
				mState = State::Running;
			} else {
				mState = State::Idle;
			}
			break;
		}
		case Action::Shoot: {
			if(isMovingX()) {
				mState = State::Running;
			} else {
				mState = State::Idle;
			}
			break;
		}
		case Action::None: {
			mState = State::Idle;
			break;
		}
	}
}

void Character::startHurtAnimation() {
	mHurtTimer.set(mTotalHurtTime);
	mIsHurting = true;
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
		mCanDoubleJump = true;
	} else if (mCanDoubleJump && !mIsJumping) {
		mJumpForce = mStartingJumpForce;
		mIsInAir = true;
		mIsJumping = true;
		applyMovement(Action::Jump);
		mCanDoubleJump = false;
	}
}

void Character::run() {
	if(!mIsInAir && !mIsJumping && !mIsRunning) {
		mIsRunning = true;
		applyMovement(Action::Run);
	}
}

bool Character::shoot() {
	if(mShootTimer.isExpired()) {
		mIsShooting = true;
		mShootTimer.set(mTimeBetweenShots);
		return true;
	}
	return false;
}

bool Character::isShooting() const {
	return mIsShooting;
}

std::optional<std::unique_ptr<EntityBase>> Character::getProjectile() {
	if(mIsShooting) {
		float x = mIsFacingRight ? getPosition().x + getSize().x + 10.0f : getPosition().x - 10.0f;
		
		mIsShooting = false;
		return std::make_unique<Projectile>(
			"../res/Textures/HUD/energy.png", 
			sf::Vector2f(
				mIsFacingRight ? getPosition().x + getSize().x + 20.0f : getPosition().x - 20.0f,
				getPosition().y + getSize().y/2
			),
			getScreenNumber(),
			mIsFacingRight
		);
	}
	return {};
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

sf::Vector2f Character::getSize() const {
	return sf::Vector2f(
		mSprite.getGlobalBounds().width,
		mSprite.getGlobalBounds().height
	);
}

sf::FloatRect Character::getGlobalBounds() const {
	return mSprite.getGlobalBounds();
}

void Character::setSpriteScale(float x, float y) {
	mSprite.setScale(x, y);
	updateSizeUsingSprite();
}

void Character::updateSizeUsingSprite() {
	EntityBase::mSize = sf::Vector2f(
		mSprite.getGlobalBounds().width,
		mSprite.getGlobalBounds().height	
	);
}

bool Character::isFinished() const {
	return mIsFinished;
}

void Character::handleCollision(
	std::vector<std::unique_ptr<EntityBase>*> top, 
	std::vector<std::unique_ptr<EntityBase>*> bottom, 
	std::vector<std::unique_ptr<EntityBase>*> left, 
	std::vector<std::unique_ptr<EntityBase>*> right, 
	CollisionSides hitSides
) {

	EntityBase::removeNonSolid(top, bottom, left, right, hitSides);

	if(hitSides.bottom) {
		if(mVelocity.y > 0) {
			mVelocity.y = 0;
		}

		mIsInAir = false;
		mIsJumping = false;
		mCanDoubleJump = true;
	} 
	if(hitSides.top) {
		mVelocity.y = 0;
		mIsJumping = false;
		mIsInAir = true;
		// DIE!
	} 
	if(hitSides.left) {
		mVelocity.x = 0;
	} 
	if(hitSides.right) {
		mVelocity.x = 0;
	} 
	
	mRestrictedSides = hitSides;

}

void Character::handleNoCollision() {
	mRestrictedSides = CollisionSides();
	mIsInAir = true;
}

void Character::update(const sf::Time& deltaTime) {
	mVelocity.x = 0;
	if (mJumpForce >= 0) {
		mIsJumping = false;
	}
	if (mIsJumping && mIsInAir) {
		mVelocity.y = mJumpForce;
		mJumpForce += mJumpAcceleration;
	} else if(mIsInAir || !mRestrictedSides.bottom) {
		mIsInAir = true;
		mVelocity.y = mGravity;
		if (mGravity < mMaxGravity) {
			mGravity += mGravityAcceleration;
		}
	} else {
		mVelocity.y = 0;
		mJumpForce = mStartingJumpForce;
		mGravity = 0;
		mIsJumping = false;
	}
	
	for(auto & action : actions) {
		action();
	}
	
	if(mUnperformedActions.empty()) {
		updateState(Action::None);
	}

	bool runningActionFound = false;
	while(!mUnperformedActions.empty()) {
		if(mUnperformedActions.front() == Action::Run) {
			runningActionFound = true;
		}
		performAction(mUnperformedActions.front());
		mUnperformedActions.pop();
	}

	if(!runningActionFound) {
		mIsRunning = false;
	}

	move(mVelocity);
	animate(deltaTime);
}

void Character::animate(const sf::Time& deltaTime) {
	mTimeSinceLastAnimation += deltaTime;

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
			
			if(mTimeSinceLastAnimation >= animation.second.displayTime) {
				if(mIsHurting) {
					if(mHurtTimer.isExpired()) {
						mIsHurting = false;
						setIsVisible(true);
					} else {
						setIsVisible(!isVisible());
					}
				}
				
				mTimeSinceLastAnimation = sf::seconds(0.0f);
				currentSprite.x++;


				if(currentSprite == animation.second.end) {					
					currentSprite = animation.second.start;
				}
				
				if(mIsFacingRight) {
					mSprite.setTextureRect(
						sf::IntRect(
							static_cast<int>(currentSprite.x * animation.second.size.x),
							static_cast<int>(currentSprite.y * animation.second.size.y),
							static_cast<int>(animation.second.size.x),
							static_cast<int>(animation.second.size.y)
						)
					);
				} else {
					mSprite.setTextureRect(
						sf::IntRect(
							static_cast<int>((currentSprite.x + 1) * animation.second.size.x),
							static_cast<int>(currentSprite.y * animation.second.size.y),
							static_cast<int>(-animation.second.size.x),
							static_cast<int>(animation.second.size.y)
						)
					);
				}
			}
		}
	}
	mPreviousState = mState;
	mSize = sf::Vector2f(
		mSprite.getGlobalBounds().width, 
		mSprite.getGlobalBounds().height
	);
}

void Character::draw(sf::RenderWindow& window) {
	window.draw(mSprite);
}

void Character::draw(ViewManager& window) {
	window.selectDrawingScreen(mScreenNumber);
	window.draw(mSprite);
}