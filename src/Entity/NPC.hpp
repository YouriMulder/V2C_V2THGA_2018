#ifndef NPC_HPP
#define NPC_HPP

#include "Character.hpp"

class NPC : public Character {
public:
	NPC(const sf::Vector2f& position, int screenNumber);
	virtual ~NPC();

	virtual void bindActions() override;
	virtual void bindAnimations() override;
};

#endif /* NPC_HPP */