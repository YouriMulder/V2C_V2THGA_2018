#include "Player.hpp"
#include "../SoundPlayer.hpp"
#include "../EventManager.hpp"
#include "Finish.hpp"
#include <SFML/Graphics.hpp>

// static 
uint_least8_t Player::maxHealth = 10;
uint_least8_t Player::health = maxHealth;
uint_least8_t Player::maxEnergy = 10;
uint_least8_t Player::energy = maxEnergy;

uint_least8_t Player::getHealth() {
	return health;
}

void Player::setMaxHealth(uint_least8_t newMaxHealth) {
	maxHealth = newMaxHealth;
}

void Player::setHealth(uint_least8_t newHealth) {
	if (newHealth > maxHealth) {
		health = maxHealth;
	} else if (newHealth < 0) {
		health = 0;
	} else {
		health = newHealth;
	}
}

void Player::addHealth(int_least8_t deltaHealth) {
	if(health + deltaHealth > maxHealth) {
		health = maxHealth;
	} else if(health + deltaHealth < 0) {
		health = 0;
	} else {
		health += deltaHealth;
	}
}

void Player::resetHealth() {
	health = maxHealth;
}

uint_least8_t Player::getEnergy() {
	return energy;
}

void Player::setMaxEnergy(uint_least8_t newMaxEnergy) {
	maxEnergy = newMaxEnergy;
}

void Player::setEnergy(uint_least8_t newEnergy) {
	if (newEnergy > maxEnergy) {
		energy = maxEnergy;
	} else if (newEnergy < 0) {
		energy = 0;
	} else {
		energy = newEnergy;
	}
}

void Player::addEnergy(int_least8_t deltaEnergy) {
	if(energy + deltaEnergy > maxEnergy) {
		energy = maxEnergy;
	} else if(energy + deltaEnergy < 0) {
		energy = 0;
	} else {
		energy += deltaEnergy;
	}
}

void Player::resetEnergy() {
	energy = maxEnergy;
}

void Player::reset() {
	resetHealth();
	resetEnergy();
}

bool Player::isDead() {
	return !isAlive();
}

bool Player::isAlive() {
	return health > 0;
}

Player::Player(const sf::Vector2f& position, int screenNumber):
	Character(
		position, sf::Vector2f(19.0f, 34.0f), 
		screenNumber, sf::Vector2f(2.0f, 2.0f), sf::Vector2f(20.0f, 10.0f),
		"../res/Textures/Player/player.png"
	)
{
	setSpriteScale(2.0f, 2.0f);
	bindActions();
	bindAnimations();
}

Player::~Player() {}

bool Player::shoot() {
	if(energy > 0 && Character::shoot()) {
		energy--;
		mSoundPlayer.play(Sounds::shoot);
		return true;
	}
	return false;
}

void Player::hurt(uint_least8_t damage) {
	Character::startHurtAnimation();
	mSoundPlayer.play(Sounds::hurt);
	if(damage >= Player::health) {
		Player::health = 0;
	} else {
		Player::health -= damage;
	}
}

void Player::bindActions() {
	Character::bindAction(EventManager(sf::Keyboard::Left, 		[&] 	{addAction(Character::Action::Left);	}));
	Character::bindAction(EventManager(sf::Keyboard::Right, 	[&] 	{addAction(Character::Action::Right);	}));
	Character::bindAction(EventManager(sf::Keyboard::Up, 		[&] 	{addAction(Character::Action::Jump);	}));
	Character::bindAction(EventManager(sf::Keyboard::A, 		[&] 	{addAction(Character::Action::Left);	}));
	Character::bindAction(EventManager(sf::Keyboard::D, 		[&] 	{addAction(Character::Action::Right);	}));
	Character::bindAction(EventManager(sf::Keyboard::W, 		[&] 	{addAction(Character::Action::Jump);	}));
	
	Character::bindAction(EventManager(sf::Keyboard::Space, 	[&] 	{addAction(Character::Action::Jump);	}));
	Character::bindAction(EventManager(sf::Keyboard::LShift, 	[&] 	{addAction(Character::Action::Run);		}));

	Character::bindAction(EventManager(sf::Keyboard::F, 		[&] 	{addAction(Character::Action::Shoot);		}));
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

void Player::handleCollision(
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
			const auto& uniqueObject = (*object);
			if(dynamic_cast<Finish*>(uniqueObject.get())) {
				mIsFinished = true;
			}
		}
	}
}