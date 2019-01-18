#ifndef ENTITY_BASE_HPP
#define ENTITY_BASE_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include "../ViewManager.hpp"
#include "Side.hpp"

class EntityBase {
protected:
	sf::Vector2f mPosition;
	sf::Vector2f mSize;
	int mScreenNumber;
public:
	EntityBase(
		const sf::Vector2f& mPosition, 
		const sf::Vector2f mSize, 
		int mScreenNumber 
	);
	void move(float deltaX, float deltaY);
	void move(const sf::Vector2f& deltaPosition);
	void setPosition(float x, float y);
	void setPosition(const sf::Vector2f& newPosition);
	virtual sf::Vector2f getPosition() const;
	virtual sf::FloatRect getGlobalBounds() const;

	void setScreenNumber(int newScreenNumber);
	int getScreenNumber() const;

	virtual void handleCollision(std::unique_ptr<EntityBase> & other, Side hitSide) {};
	virtual void update() = 0;
	virtual void draw(sf::RenderWindow& window) = 0;
	virtual void draw(ViewManager& window) = 0;
	virtual ~EntityBase();
};

#endif /* ENTITY_BASE_HPP */