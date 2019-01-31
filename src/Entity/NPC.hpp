#ifndef NPC_HPP
#define NPC_HPP

#include "Character.hpp"
#include <cstdint>
#include <SFML/System/Clock.hpp>
#include "Timers.hpp"
#include "Timer.hpp"

/// \brief
/// This is the NPC class.
/// \details
/// This class is used to make non playable characters a the game.
/// These non playable characters move through the levels using a small algorithm.
class NPC : public Character {
private:
	/// \brief
	/// This is the position where the NPC will spawn at.
	sf::Vector2f mStartPoint;
	
	/// \brief
	/// This is the amount of difference in the X axis the NPC will walk from mStartPoint.
	float mDeltaXMovement;

	/// \brief
	/// The NPC is moving to the right if this is true.\n
	/// The NPC is moving to the left if this is false.
	bool mIsMovingRight;

	/// \brief 
	/// The amount of time the NPC is unable to move after a collision.
	sf::Time unableToMoveTime = sf::seconds(2);

	/// \brief
	/// This is a timer used to make the player unable to move for a given time.
	Timer unableToMoveTimer;

	/// \brief
	/// The NPC is able to jump if this is true.\n
	/// The NPC is NOT able to jump if this is false.
	bool mJumpingEnabled;

	/// \brief
	/// This is the time there should be between jumps.
	sf::Time mJumpDeltaTime;

	/// \brief
	/// This clock is used to check how 
	/// long it has been the NPC jumped for the last time.
	/// \details
	/// The clock will be set when the NPC has jumped.
	/// If the value of the clock is greater 
	/// than mJumpDeltaTime the NPC is able to jump again.
	sf::Clock lastTimeSinceJumpClock;


	/// \brief
	/// The NPC is able to move if this is true.\n
	/// The NPC is NOT able to move if this is false.	
	bool mAbleToMove;
	
	/// \brief
	/// This is the amount of health the player got at the moment.
	uint_least8_t mHealth;

	/// \brief
	/// This is the amount of damage the NPC will deal when something hit him.
	uint_least8_t mDamage;

	/// \brief
	/// These are all the clocked objects which are hurt by the NPC.
	/// \details
	/// When something collided with the NPC there will be a Timer added to this object.
	/// Only when there is not a timer the NPC is able to hurt him again.
	Timers hitClocks;

public:
	/// \brief
	/// This is the constructor for the NPC class.
	/// \param startPoint
	/// The position where the player spawns at.
	/// \param deltaXMovement
	/// The amount of difference in the X axis 
	/// the NPC will walk from mStartPoint.
	/// \param screenNumber
	/// The screen you want to draw the NPC to.
	/// \param health
	/// The health for a NPC.
	/// \param damage
	/// The damage the NPC will deal to other objects.
	/// \param jumpingEnabled
	/// Whether or not jumping is enabled.
	/// \param jumpDeltaTime
	/// The time there should be between jumps.
	NPC(const sf::Vector2f& startPoint, 
		const float& deltaXMovement, 
		int screenNumber,
		const uint_least8_t& health,
		const uint_least8_t& damage,
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