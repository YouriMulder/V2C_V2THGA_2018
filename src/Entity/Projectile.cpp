#include "Projectile.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

Projectile::Projectile(
	const std::string& filename, 
	const sf::Vector2f& position, 
	int screenNumber,
	bool isDirectionRight 
):
	LevelObject(filename, position, sf::Vector2f(0.0f,0.0f), screenNumber),
	mIsDirectionRight(isDirectionRight)
{
	EntityBase::setIsSolid(false);
}

Projectile::~Projectile() {}

void Projectile::update(const sf::Time& deltaTime) {
	float newX = getPosition().x + (mMovementPerSecond * deltaTime.asSeconds());
	if(!mIsDirectionRight) {
		newX = getPosition().x - (mMovementPerSecond * deltaTime.asSeconds());
	}
	setPosition( sf::Vector2f(
		newX,
		getPosition().y
	));
}

void Projectile::handleCollision(
	std::vector<std::unique_ptr<EntityBase>*> top, 
	std::vector<std::unique_ptr<EntityBase>*> bottom, 
	std::vector<std::unique_ptr<EntityBase>*> left, 
	std::vector<std::unique_ptr<EntityBase>*> right, 
	CollisionSides hitSides
) {
	if(!EntityBase::shouldDestroy()) {
		std::vector<
			std::vector<std::unique_ptr<EntityBase>*>
		> allObjects = {top, bottom, left, right};
		
		for(const auto& objectVector: allObjects) {
			for(const auto& object : objectVector) {
				const auto& uniqueObject = (*object);
				if(!EntityBase::shouldDestroy() && !uniqueObject->shouldDestroy()) {
					uniqueObject->hurt(mDamage);
					destroy();
				}
			}
		}
	}
}