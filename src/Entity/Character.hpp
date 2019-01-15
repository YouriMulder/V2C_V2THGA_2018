#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "EntityBase.hpp"

class Character : public EntityBase {
public:
	enum class Direction {
		Left,
		Right,
		Up,
		Down,
		None
	};
	
	Character(sf::Vector2f maxVelocity, sf::Vector2f acceleration);
	virtual ~Character();

	void move(const sf::Vector2f& delta);
	void setMoveDirection(const Direction& newDirection);

	void jump();
	void attack();
	void getHurt(int damage);
	
	void updateVelocity(const sf::Vector2f& deltaVelocity);
	void applyFrictionOneAxis(float& axisVelocity);
	void applyFriction();
	virtual void update();
	virtual void draw(sf::RenderWindow& window) override;

private:
	sf::Vector2f mVelocity;
	sf::Vector2f mMaxVelocity;
	sf::Vector2f mAcceleration;

	Direction mMovingDirection;

	// TODO: Flyweight
	sf::Texture mTexture;
	sf::Sprite mSprite;
};


#endif /* CHARACTER_HPP */