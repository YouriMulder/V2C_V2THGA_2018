#include "NPC.hpp"

NPC::NPC(
	const sf::Vector2f& startPoint, 
	const float& deltaXMovement, 
	int screenNumber, 
	const uint_least8_t& health, 	
	const uint_least8_t& damage, 
	bool jumpingEnabled, 
	const sf::Time& jumpDeltaTime
):
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
	mAbleToMove(true),
	mHealth(health),
	mDamage(damage)
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
		if(mAbleToMove && mDeltaXMovement != 0.0f) {
			return mIsMovingRight; 
		}
		return false;
	}, [&] 	{addAction(Character::Action::Right);} ));
	
	Character::bindAction( EventManager( [=]()->bool { 
		if(mAbleToMove && mDeltaXMovement != 0.0f) {
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

	std::vector<
		std::vector<std::unique_ptr<EntityBase>*>
	> allObjects = {top, bottom, left, right};

	for(const auto& objectVector: allObjects) {
		for(const auto& object : objectVector) {
			if(!hitClocks.isClocked((*object)->getId())) {
				std::cout << "health: " << unsigned(mHealth) << "\n";
				std::cout << "damage: " << unsigned(mDamage) << "\n";				
				(*object)->hurt(mDamage);
				hitClocks.addClock((*object)->getId());
			}
		}
	}

	if((hitSides.right || hitSides.left) && mAbleToMove) {
		mIsMovingRight = !mIsMovingRight;
		mAbleToMove = false;
	} else {
		if(!unableToMoveTimer.isSet()) {
			unableToMoveTimer.set(unableToMoveTime);
		}
	}
}

void NPC::handleNoCollision() {
	Character::handleNoCollision();
	if(!unableToMoveTimer.isSet()) {
		unableToMoveTimer.set(unableToMoveTime);
	}
}

void NPC::hurt(uint_least8_t damage) {
	Character::startHurtAnimation();
	if(damage >= mHealth) {
		mHealth = 0;
		destroy();
	} else {
		mHealth -= damage;
	}
}

void NPC::update(const sf::Time& deltaTime) {
	Character::update(deltaTime);

	hitClocks.deleteExpired();

	if(!mAbleToMove) {
		if(unableToMoveTimer.isExpired()) {
			mAbleToMove = true;
		}
	}
	
	if(mDeltaXMovement != 0.0f) {
		if(mPosition.x >= mStartPoint.x + mDeltaXMovement) {
			mIsMovingRight = false;
		} else if(mPosition.x <= mStartPoint.x) {
			mIsMovingRight = true;
		}
	}
	
}
