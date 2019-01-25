#include "Projectile.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

Projectile::Projectile(
	const std::string& filename, 
	const sf::Vector2f& position, 
	int screenNumber,
	bool isDirectionRight 
):
	LevelObject(filename, position, sf::Vector2f(0.0f,0.0f), screenNumber)
{
	LevelObject::matchSizeWithSprite();
}

Projectile::~Projectile() {}