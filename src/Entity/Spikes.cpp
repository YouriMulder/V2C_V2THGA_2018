#include "Spikes.hpp"
#include <iostream>

Spikes::Spikes(const std::string& filename, const sf::Vector2f& position, const sf::Vector2f& size,
	const sf::IntRect& picturepart, int screenNumber, uint_least8_t damage, bool repeated) :

	LevelObject(filename, position, size, picturepart, screenNumber, repeated),
	mDamage(damage)
{}

Spikes::Spikes(const std::string& filename, const sf::Vector2f& position, const sf::Vector2f& size,
	int screenNumber, uint_least8_t damage, bool repeated) :

	LevelObject(filename, position, size, screenNumber, repeated),
	mDamage(damage)
{}

void Spikes::handleCollision(
	std::vector<std::unique_ptr<EntityBase>*> top, 
	std::vector<std::unique_ptr<EntityBase>*> bottom, 
	std::vector<std::unique_ptr<EntityBase>*> left, 
	std::vector<std::unique_ptr<EntityBase>*> right,  
	CollisionSides hitSides
) {
	for(auto& object : top) {
		if(!hitClocks.isClocked((*object)->getId())) {
			(*object)->hurt(mDamage);
			hitClocks.addClock((*object)->getId());
		}
	}
}

void Spikes::update(const sf::Time& deltaTime) {
	hitClocks.deleteExpired();
}


sf::FloatRect Spikes::getGlobalBounds() const {
	return mSprite.getGlobalBounds();
}