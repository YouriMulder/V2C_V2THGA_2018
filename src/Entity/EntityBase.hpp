#ifndef ENTITY_BASE_HPP
#define ENTITY_BASE_HPP

#include <SFML/Graphics.hpp>

class EntityBase {
protected:
	sf::Vector2f mPosition;
	sf::Vector2f mSize;

	// ViewManager& mViewManager
	// int viewport 
public:
	EntityBase();
	void move(float deltaX, float deltaY);

	virtual void update() = 0;
	virtual void draw(sf::RenderWindow& window) = 0;
	virtual ~EntityBase();
};

#endif /* ENTITY_BASE_HPP */