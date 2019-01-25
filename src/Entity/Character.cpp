#include "Character.hpp"

#include "../World/Physics.hpp"
#include "Finish.hpp"
#include <iostream>
#include <cstdint>

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
	mSelected(false),
	mIsFinished(false),
	mPreviousState(Character::State::Idle),
	mState(Character::State::Idle),
	mSpriteWidth(static_cast<unsigned int>(size.x)),
	mSpriteHeight(static_cast<unsigned int>(size.y)),
	mCurrentSpriteSheetLocation(0,0, static_cast<unsigned int>(size.x), static_cast<unsigned int>(size.y))
{
	mTexture.loadFromFile(characterSheetPath);
	mSprite = sf::Sprite(mTexture, mCurrentSpriteSheetLocation);
	mSprite.setPosition(EntityBase::mPosition);
	mSize = sf::Vector2f(
		mSprite.getGlobalBounds().width, 
		mSprite.getGlobalBounds().height
	);
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

void Character::applyGravity() {
	updateVelocity(sf::Vector2f(mVelocity.x, 2.0f));
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

	std::vector<
		std::vector<std::unique_ptr<EntityBase>*>
	> allObjects = {top, bottom, left, right};

	for(const auto& objectVector: allObjects) {
		for(const auto& object : objectVector) {
			if(dynamic_cast<Finish*>((*object).get())) {
				mIsFinished = true;
			}
		}
	}

	if(hitSides.bottom) {
		// move along with platforms
		auto highestBottom = bottom[0];
		for(const auto& object : bottom) {
			if((*object)->getPosition().y < (*highestBottom)->getPosition().y) {
				highestBottom = object; 
			}
		}

		// move to next update
		setPosition( 
			sf::Vector2f(
				mPosition.x - ((*highestBottom)->getPosition().x - (*highestBottom)->getNextPosition().x),
				(*highestBottom)->getPosition().y - getSize().y + 3 // otherwise the player will always fall when standing on moving entities
			) 
		);

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
}

void Character::handleNoCollision() {
	restrictedSides = CollisionSides();
	mIsInAir = true;
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


void Character::update(const sf::Time& deltaTime) {
	mVelocity.x = 0;
	if (mJumpForce >= 0) {
		mIsJumping = false;
	}
	if (mIsJumping && mIsInAir) {
		mVelocity.y = mJumpForce;
		mJumpForce += mJumpAcceleration;
	} else if(mIsInAir || !restrictedSides.bottom) {
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

void Character::startHurtAnimation() {
	hurtClock.restart();
	mIsHurting = true;
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
				if(mIsHurting) {
					if(hurtClock.getElapsedTime() >= totalHurtTime) {
						mIsHurting = false;
						setIsVisible(true);
					} else {
						setIsVisible(!getIsVisible());
					}
				}
				
				timeSinceLastAnimation = sf::seconds(0.0f);
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

void Character::select(bool selection) {
	mSelected = selection;
}

bool Character::isSelected() {
	return mSelected;
}

bool Character::isFinished() {
	return mIsFinished;
}