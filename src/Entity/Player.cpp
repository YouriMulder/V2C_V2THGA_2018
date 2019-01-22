#include "Player.hpp"

#include "../EventManager.hpp"
#include <SFML/Graphics.hpp>

Player::Player(const sf::Vector2f& position, int screenNumber):
	Character(
		position, sf::Vector2f(19.0f, 34.0f), 
		screenNumber, sf::Vector2f(2.0f, 2.0f), sf::Vector2f(20.0f, 10.0f) 
	)
{
	bindActions();
	bindAnimations();
}

Player::~Player() {}

void Player::bindActions() {
	Character::bindAction(EventManager(sf::Keyboard::Left, 		[&] 	{addAction(Character::Action::Left);	}));
	Character::bindAction(EventManager(sf::Keyboard::Right, 	[&] 	{addAction(Character::Action::Right);	}));
	Character::bindAction(EventManager(sf::Keyboard::Up, 		[&] 	{addAction(Character::Action::Jump);	}));
	Character::bindAction(EventManager(sf::Keyboard::Space, 	[&] 	{addAction(Character::Action::Jump);	}));
	Character::bindAction(EventManager(sf::Keyboard::LShift, 	[&] 	{addAction(Character::Action::Run);		}));
}

void Player::bindAnimations() {
	Character::bindAnimation(
		Character::State::Idle, 
		AnimationSequence(
				sf::Vector2i(0,0),
				sf::Vector2i(12,0),
				sf::Vector2f(20.0f, 35.0f),
				sf::milliseconds(100)
		)
	);
	Character::bindAnimation(
		Character::State::Moving, 
		AnimationSequence(
				sf::Vector2i(0,1),
				sf::Vector2i(8,1),
				sf::Vector2f(21.0f, 35.0f),
				sf::milliseconds(125)
		)
	);
	Character::bindAnimation(
		Character::State::Running, 
		AnimationSequence(
			sf::Vector2i(0,1),
			sf::Vector2i(8,1),
			sf::Vector2f(21.0f, 35.0f),
			sf::milliseconds(75)
		)
	);
	Character::bindAnimation(
		Character::State::Jumping, 
		AnimationSequence(
			sf::Vector2i(0,2),
			sf::Vector2i(1,2),
			sf::Vector2f(21.0f, 35.0f),
			sf::milliseconds(10)
		)
	);
	Character::bindAnimation(
		Character::State::Falling, 
		AnimationSequence(
			sf::Vector2i(0,4),
			sf::Vector2i(1,4),
			sf::Vector2f(21.0f, 35.0f),
			sf::milliseconds(10)
		)
	);
}