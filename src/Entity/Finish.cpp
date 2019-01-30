#include "Finish.hpp"

Finish::Finish(const std::string& filename, const sf::Vector2f& position, const sf::Vector2f& size,
	int screenNumber, bool repeated):
	LevelObject(filename, position, size, screenNumber, repeated)
{}

Finish::~Finish() {}