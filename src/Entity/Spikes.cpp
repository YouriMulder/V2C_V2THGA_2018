#include "Spikes.hpp"
#include <iostream>

Spikes::Spikes(const std::string& filename, const sf::Vector2f& position, const sf::Vector2f& size,
	const sf::IntRect& picturepart, int screenNumber, uint_least8_t damage, bool repeated) :

	LevelObject(filename, position, size, picturepart, screenNumber, repeated),
	mDamage(damage)
{
	hitClocks.reserve(10);
}

Spikes::Spikes(const std::string& filename, const sf::Vector2f& position, const sf::Vector2f& size,
	int screenNumber, uint_least8_t damage, bool repeated) :

	LevelObject(filename, position, size, screenNumber, repeated),
	mDamage(damage)
{
	hitClocks.reserve(10);
}

void Spikes::addClock(uint_least64_t entityId) {
	hitClocks.push_back(
		std::make_pair(entityId, sf::Clock())
	);
}

bool Spikes::isClocked(uint_least64_t entityId) {
	for(int i = 0; i < hitClocks.size(); ++i) {
		if(hitClocks[i].first == entityId) {
			if(hitClocks[i].second.getElapsedTime() > timeBetweenHits) {
				hitClocks.erase(hitClocks.begin() + i);
				return false; 
			}
			return true;
		}
	}
	return false;
}

void Spikes::handleCollision(
	std::vector<std::unique_ptr<EntityBase>*> top, 
	std::vector<std::unique_ptr<EntityBase>*> bottom, 
	std::vector<std::unique_ptr<EntityBase>*> left, 
	std::vector<std::unique_ptr<EntityBase>*> right,  
	CollisionSides hitSides
) {
	for(auto& object : top) {
		if(!isClocked((*object)->getId())) {
			(*object)->hurt(mDamage);
			addClock((*object)->getId());
		}
	}
}

void Spikes::update(const sf::Time& deltaTime) {
	for(int i = 0; i < hitClocks.size(); ++i) {
		if(hitClocks[i].second.getElapsedTime() > timeBetweenHits) {
			hitClocks.erase(hitClocks.begin() + i);
		}
	}
}


sf::FloatRect Spikes::getGlobalBounds() const {
	return mSprite.getGlobalBounds();
}