#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Character.hpp"

class Player : public Character {
protected:
	// static
	static uint_least8_t maxHealth;
	static uint_least8_t health;
public:
	static uint_least8_t getHealth();
	static void resetHealth();
	static bool isDead();
	static bool isAlive();
	
	Player(const sf::Vector2f& position, int screenNumber);
	virtual ~Player();

	virtual void hurt(uint_least8_t damage);
	virtual void bindActions() override;
	virtual void bindAnimations() override;
};

#endif /* PLAYER_HPP */ 