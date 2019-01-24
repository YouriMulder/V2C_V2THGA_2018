#ifndef ENTITY_BASE_HPP
#define ENTITY_BASE_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <cstdint>

#include "../ViewManager.hpp"
#include "Side.hpp"

class EntityBase {
private: 
	static void increaseNextId();

protected:
	uint_least64_t id;
	sf::Vector2f mPosition;
	sf::Vector2f mSize;
	int mScreenNumber;
	
	static uint_least64_t nextId;
public:
	static void backToStartId();

	EntityBase(
		const sf::Vector2f& mPosition, 
		const sf::Vector2f mSize, 
		int mScreenNumber 
	);
	
	uint_least64_t getId() const;
	void move(float deltaX, float deltaY);
	void move(const sf::Vector2f& deltaPosition);
	void setPosition(float x, float y);
	void setPosition(const sf::Vector2f& newPosition);

	void setScreenNumber(int newScreenNumber);
	int getScreenNumber() const;

	virtual void hurt(uint_least8_t damage) {};

	virtual sf::Vector2f getSize() const;
	virtual sf::Vector2f getPosition() const;
	virtual sf::Vector2f getNextPosition() const;
	virtual sf::FloatRect getGlobalBounds() const;
	virtual bool isFinished();
	
	virtual void update(const sf::Time& deltaTime) = 0;
	virtual void handleCollision(
		std::vector<std::unique_ptr<EntityBase>*> top, 
		std::vector<std::unique_ptr<EntityBase>*> bottom, 
		std::vector<std::unique_ptr<EntityBase>*> left, 
		std::vector<std::unique_ptr<EntityBase>*> right, 
		CollisionSides hitSides
	) {};
	virtual void handleNoCollision() {};

	virtual void setColor(const sf::Color& newColor) {};
	virtual void draw(sf::RenderWindow& window) = 0;
	virtual void draw(ViewManager& window) = 0;
	virtual ~EntityBase();
};

#endif /* ENTITY_BASE_HPP */