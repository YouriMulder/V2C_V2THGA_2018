#ifndef NPC_HPP
#define NPC_HPP

#include "Character.hpp"
#include <cstdint>
#include <SFML/System/Clock.hpp>
#include "Timers.hpp"

class NPC : public Character {
private:
	sf::Vector2f mStartPoint;
	float mDeltaXMovement;
	uint_least8_t mDamage;
	bool mIsMovingRight;
	bool mJumpingEnabled;
	sf::Time mJumpDeltaTime;
	bool mAbleToMove;
	
	uint_least8_t mHealth;

	sf::Clock lastTimeSinceJumpClock;
	bool unableToMoveTimerSet = true;
	sf::Time unableToMoveTime = sf::seconds(2);
	sf::Clock unableToMoveClock;

	Timers hitClocks;

public:
	NPC(const sf::Vector2f& startPoint, 
		const float& deltaXMovement, 
		int screenNumber,
		uint_least8_t damage = 1,
		bool jumpingEnabled = false, 
		const sf::Time& jumpDeltaTime = sf::seconds(0)
	);
	virtual ~NPC();

	virtual void bindActions() override;
	virtual void bindAnimations() override;
	virtual void handleCollision(
	std::vector<std::unique_ptr<EntityBase>*> top, 
	std::vector<std::unique_ptr<EntityBase>*> bottom, 
	std::vector<std::unique_ptr<EntityBase>*> left, 
	std::vector<std::unique_ptr<EntityBase>*> right, 
	CollisionSides hitSides
	) override;
	virtual void handleNoCollision() override;
	virtual void hurt(uint_least8_t damage) override;
	virtual void update(const sf::Time& deltaTime) override;

};
#endif /* NPC_HPP */