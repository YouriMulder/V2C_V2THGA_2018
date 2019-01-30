#include "Background.hpp"



Background::Background(const std::string& filename, const sf::Vector2f& position, const sf::Vector2f& sizeTexture, const sf::Vector2f & wantedSize,
	int screenNumber, bool repeated):
	LevelObject(filename,position,sizeTexture,screenNumber,repeated)
{
	resize(wantedSize);
}


Background::~Background()
{
}
