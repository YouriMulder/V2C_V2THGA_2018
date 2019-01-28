#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Character.hpp"

class Player : public Character {
protected:
	// static
	static uint_least8_t maxHealth;
	static uint_least8_t health;
	static uint_least8_t maxEnergy;
	static uint_least8_t energy;

public:
	static uint_least8_t getHealth();
	static void setMaxHealth(uint_least8_t newMaxEnergy);
	static void resetHealth();
	static uint_least8_t getEnergy();
	static void setMaxEnergy(uint_least8_t newMaxEnergy);
	static void resetEnergy();
	static void reset();

	static bool isDead();
	static bool isAlive();
	
	Player(const sf::Vector2f& position, int screenNumber);
	virtual ~Player();

	virtual bool shoot() override;
	virtual void hurt(uint_least8_t damage) override;
	virtual void bindActions() override;
	virtual void bindAnimations() override;

	virtual void handleCollision(
		std::vector<std::unique_ptr<EntityBase>*> top, 
		std::vector<std::unique_ptr<EntityBase>*> bottom, 
		std::vector<std::unique_ptr<EntityBase>*> left, 
		std::vector<std::unique_ptr<EntityBase>*> right, 
		CollisionSides hitSides
	);
};

#endif /* PLAYER_HPP */ 