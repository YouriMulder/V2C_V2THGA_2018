#ifndef SPIKES_HPP
#define SPIKES_HPP

#include "SFML/Graphics.hpp"
#include "LevelObject.hpp"
#include "../ViewManager.hpp"
#include <string>

class Spikes : public LevelObject {
private:
	int damage;
public:
	Spikes(const std::string& filename, const sf::Vector2f& position, const sf::Vector2f& size,
		const sf::IntRect& picturepart, int screenNumber, int damage, bool repeated = false);
	Spikes(const std::string& filename, const sf::Vector2f& position, const sf::Vector2f& size,
		int screenNumber, int damage, bool repeated = false);
	sf::FloatRect getGlobalBounds() const override;
	int getDamage() const;
};

#endif /* SPIKES_HPP */