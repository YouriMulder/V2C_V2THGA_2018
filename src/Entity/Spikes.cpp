#include "Spikes.hpp"

Spikes::Spikes(const std::string& filename, const sf::Vector2f& position, const sf::Vector2f& size,
	const sf::IntRect& picturepart, int screenNumber, int damage, bool repeated) :

	LevelObject(filename, position, size, picturepart, screenNumber, repeated),
	damage(damage)
{}

Spikes::Spikes(const std::string& filename, const sf::Vector2f& position, const sf::Vector2f& size,
	int screenNumber, int damage, bool repeated) :

	LevelObject(filename, position, size, screenNumber, repeated),
	damage(damage)
{}

sf::FloatRect Spikes::getGlobalBounds() const {
	return mSprite.getGlobalBounds();
}

int Spikes::getDamage() const {
	return damage;
}