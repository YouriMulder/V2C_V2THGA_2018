#include "Platform.hpp"

Platform::Platform(const std::string& filename, const sf::Vector2f& position, const sf::Vector2f& size, const sf::IntRect& picturepart, int screenNumber, bool repeated) :
	LevelObject(filename, position, size, picturepart, screenNumber, repeated)
{}

Platform::Platform(const std::string& filename, const sf::Vector2f& position, const sf::Vector2f& size, int screenNumber, bool repeated) :
	LevelObject(filename, position, size, screenNumber, repeated)
{}

sf::FloatRect Platform::getGlobalBounds() const {
	return mSprite.getGlobalBounds();
}