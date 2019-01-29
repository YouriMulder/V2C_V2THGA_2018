#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP
#include "LevelObject.hpp"

class Background : public LevelObject {
public:
	Background(const std::string& filename, const sf::Vector2f& position, const sf::Vector2f& sizeTexture, const sf::Vector2f & wantedSize,
		int screenNumber, bool repeated = false);
	virtual ~Background();
	sf::FloatRect getGlobalBounds() const override;
};

#endif /*BACKGROUND_HPP*/