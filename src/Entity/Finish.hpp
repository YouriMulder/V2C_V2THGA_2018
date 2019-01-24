#ifndef FINISH_HPP
#define FINISH_HPP
#include "LevelObject.hpp"

class Finish : public LevelObject{
public:
	Finish(const std::string& filename, const sf::Vector2f& position, const sf::Vector2f& size,
		int screenNumber, bool repeated = false);
	virtual ~Finish();
	sf::FloatRect getGlobalBounds() const override;
};

#endif /*FINISH_HPP*/