#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "LevelObject.hpp"

class Projectile : public LevelObject {
public:
	Projectile(
		const std::string& filename, 
		const sf::Vector2f& position, 
		int screenNumber,
		bool isDirectionRight 
	);
	virtual ~Projectile();
};

#endif /* PROJECTILE_HPP */