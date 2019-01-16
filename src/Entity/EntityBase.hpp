#ifndef ENTITY_BASE_HPP
#define ENTITY_BASE_HPP

#include <SFML/Graphics.hpp>
#include "../ViewManager.hpp"

class EntityBase {
protected:
	sf::Vector2f mPosition;
	sf::Vector2f mSize;
public:
	EntityBase();
	void move(float deltaX, float deltaY);
	void move(const sf::Vector2f& deltaPosition);
	void setPosition(float x, float y);
	void setPosition(const sf::Vector2f& newPosition);

	virtual void update() = 0;
	virtual void draw(sf::RenderWindow& window) = 0;
	virtual void draw(ViewManager& window) = 0;
	virtual ~EntityBase();
};

#endif /* ENTITY_BASE_HPP */