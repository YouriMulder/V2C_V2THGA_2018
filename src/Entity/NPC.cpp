#include "NPC.hpp"

NPC::NPC(const sf::Vector2f& startPoint, const float& deltaXMovement, int screenNumber, bool jumpingEnabled, const sf::Time& jumpDeltaTime):
	Character(
		startPoint, sf::Vector2f(50.0f, 50.0f), 
		screenNumber, sf::Vector2f(2.0f, 2.0f), sf::Vector2f(20.0f, 10.0f),
		"../res/Textures/NPC/fly.png"
	),
	mStartPoint(startPoint),
	mDeltaXMovement(deltaXMovement),
	mIsMovingRight(true),
	mJumpingEnabled(jumpingEnabled),
	mJumpDeltaTime(jumpDeltaTime),
	mAbleToMove(true)
{
	setSpriteScale(1.0f, 1.0f);

	if(deltaXMovement < 0) {
		mIsMovingRight = false;
	}
	bindActions();
	bindAnimations();
}

NPC::~NPC() {}

void NPC::bindActions() {
	Character::bindAction( EventManager( [=]()->bool { 
		if(lastTimeSinceJumpClock.getElapsedTime() >= mJumpDeltaTime && mJumpingEnabled) {
			lastTimeSinceJumpClock.restart();
			return true;
		}
		return false;
	}, [&] 	{addAction(Character::Action::Jump);} ));
	Character::bindAction( EventManager( [=]()->bool { 
		if(mAbleToMove) {
			return mIsMovingRight; 
		}
		return false;
	}, [&] 	{addAction(Character::Action::Right);} ));
	Character::bindAction( EventManager( [=]()->bool { 
		if(mAbleToMove) {
			return !mIsMovingRight;
		}
		return false;
	}, [&] 	{addAction(Character::Action::Left);} ));
}

void NPC::bindAnimations() {
	Character::bindAnimation(
		Character::State::Idle, 
		AnimationSequence(
			sf::Vector2i(0,0),
			sf::Vector2i(8,0),
			sf::Vector2f(50.0f, 50.0f),
			sf::milliseconds(150)
		)
	);
	Character::bindAnimation(
		Character::State::Moving, 
		AnimationSequence(
			sf::Vector2i(0,0),
			sf::Vector2i(8,0),
			sf::Vector2f(50.0f, 50.0f),
			sf::milliseconds(150)
		)
	);
}

void NPC::handleCollision(
	std::vector<std::unique_ptr<EntityBase>*> top, 
	std::vector<std::unique_ptr<EntityBase>*> bottom, 
	std::vector<std::unique_ptr<EntityBase>*> left, 
	std::vector<std::unique_ptr<EntityBase>*> right, 
	CollisionSides hitSides
) {
	Character::handleCollision(top, bottom, left, right, hitSides);
	
	if((hitSides.right || hitSides.left) && mAbleToMove) {
		mIsMovingRight = !mIsMovingRight;
		mAbleToMove = false;
		unableToMoveTimerSet = false;
	} else {
		if(!unableToMoveTimerSet) {
			unableToMoveTimerSet = true;
			unableToMoveClock.restart();
		}
	}
}

void NPC::handleNoCollision() {
	Character::handleNoCollision();
	if(!unableToMoveTimerSet) {
		unableToMoveTimerSet = true;
		unableToMoveClock.restart();
	}
}

void NPC::update(const sf::Time& deltaTime) {
	Character::update(deltaTime);

	if(!mAbleToMove) {
		if(unableToMoveClock.getElapsedTime() >= unableToMoveTime && unableToMoveTimerSet) {
			unableToMoveTimerSet = false;
			mAbleToMove = true;
		}
	}

	if(mPosition.x >= mStartPoint.x + mDeltaXMovement) {
		mIsMovingRight = false;
	} else if(mPosition.x <= mStartPoint.x) {
		mIsMovingRight = true;
	}
	
}
