#ifndef MOVEABLEPLATFORM_HPP
#define MOVEABLEPLATFORM_HPP

#include "SFML/Graphics.hpp"
#include "Platform.hpp"
#include <string>

class MoveablePlatform : public Platform {
private:
	sf::Vector2f beginpoint;
	sf::Vector2f endpoint;
	sf::Vector2f speed;
	bool goingForward = true;
	bool reverse;
public:
	MoveablePlatform(const std::string& filename, const sf::Vector2f& position, const sf::Vector2f& size,
		const sf::IntRect& picturepart, int screenNumber, const sf::Vector2f& moveRange, int amountOfSteps, bool repeated = false);
	MoveablePlatform(const std::string& filename, const sf::Vector2f& position, const sf::Vector2f& size,
		int screenNumber, const sf::Vector2f& moveRange, int amountOfSteps, bool repeated = false);
	void update(const sf::Time& deltaTime) override;
};

#endif