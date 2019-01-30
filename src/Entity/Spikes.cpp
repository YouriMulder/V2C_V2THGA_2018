#include "Spikes.hpp"
#include <iostream>

Spikes::Spikes(const std::string& filename, const sf::Vector2f& position, const sf::Vector2f& size,
	const sf::IntRect& picturepart, int screenNumber, uint_least8_t damage, bool repeated) :

	LevelObject(filename, position, size, picturepart, screenNumber, repeated),
	mDamage(damage)
{
	EntityBase::setIsSolid(false);
}

Spikes::Spikes(const std::string& filename, const sf::Vector2f& position, const sf::Vector2f& size,
	int screenNumber, uint_least8_t damage, bool repeated) :

	LevelObject(filename, position, size, screenNumber, repeated),
	mDamage(damage)
{
	EntityBase::setIsSolid(false);
}

void Spikes::handleCollision(
	std::vector<std::unique_ptr<EntityBase>*> top, 
	std::vector<std::unique_ptr<EntityBase>*> bottom, 
	std::vector<std::unique_ptr<EntityBase>*> left, 
	std::vector<std::unique_ptr<EntityBase>*> right,  
	CollisionSides hitSides
) {
	std::vector<
		std::vector<std::unique_ptr<EntityBase>*>
	> allObjects = {top, bottom, left, right};

	for(const auto& objectVector: allObjects) {
		for(const auto& object : objectVector) {
			if(!hitClocks.isClocked((*object)->getId())) {
				(*object)->hurt(mDamage);
				hitClocks.addTimer((*object)->getId());
			}
		}
	}
}

void Spikes::update(const sf::Time& deltaTime) {
	hitClocks.deleteExpired();
}


sf::FloatRect Spikes::getGlobalBounds() const {
	return mSprite.getGlobalBounds();
}