#include "NPC.hpp"

NPC::NPC(const sf::Vector2f& position, int screenNumber):
	Character(
		position, sf::Vector2f(19.0f, 34.0f), 
		screenNumber, sf::Vector2f(2.0f, 2.0f), sf::Vector2f(20.0f, 10.0f) 
	)
{
	bindActions();
	bindAnimations();
}

NPC::~NPC() {}

void NPC::bindActions() {
	Character::bindAction( EventManager( []()->bool { return true; }, [&] 	{addAction(Character::Action::Jump);} ));
}

void NPC::bindAnimations() {

}
