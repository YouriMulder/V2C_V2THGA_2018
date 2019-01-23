#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Character.hpp"

class Player : public Character {
public:
	Player(const sf::Vector2f& position, int screenNumber);
	virtual ~Player();

	virtual void bindActions() override;
	virtual void bindAnimations() override;
};

#endif /* PLAYER_HPP */ 