#include "Platform.hpp"

Platform::Platform(const std::string& filename, const sf::Vector2f& position, const sf::Vector2f& size,
	const sf::IntRect& picturepart, int screenNumber, bool repeated) :

	LevelObject(filename, position, size, picturepart, screenNumber, repeated)
{}

Platform::Platform(const std::string& filename, const sf::Vector2f& position, const sf::Vector2f& size,
	int screenNumber, bool repeated) :

	LevelObject(filename, position, size, screenNumber, repeated)
{}

Platform::~Platform() {}

void Platform::handleCollision(
	std::vector<std::unique_ptr<EntityBase>*> top, 
	std::vector<std::unique_ptr<EntityBase>*> bottom, 
	std::vector<std::unique_ptr<EntityBase>*> left, 
	std::vector<std::unique_ptr<EntityBase>*> right, 
	CollisionSides hitSides
) {
	if(hitSides.top) {
		for(const auto& object : top) {
			(*object)->setPosition(
				(*object)->getPosition().x,
				getPosition().y - (*object)->getSize().y + 1
			);
		}
	}
}