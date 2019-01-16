#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "EntityBase.hpp"
#include "../ViewManager.hpp"

class Character : public EntityBase {
public:
	enum class Direction {
		Left,
		Right,
		Up,
		Down,
		None
	};

	enum class State {
		Idle,
		Moving,
		Jumping,
		Attacking
	};
	
	Character(		
		const sf::Vector2f& position,
		const sf::Vector2f& size,
		int screenNumber, 
		const sf::Vector2f& maxVelocity, 
		const sf::Vector2f& acceleration
	);
	virtual ~Character();

	void move(const sf::Vector2f& delta);
	void setMoveDirection(const Direction& newDirection);
	void applyMovement();

	void updateFacingDirection();
	void animate();
	void jump(); 
	void attack();
	void getHurt(int damage);
	
	void updateVelocity(const sf::Vector2f& deltaVelocity);
	void applyFrictionOneAxis(float& axisVelocity, const float& friction);
	void applyFriction();
	virtual void update();
	virtual void draw(sf::RenderWindow& window) override;
	virtual void draw(ViewManager& window) override;

private:
	sf::Vector2f mVelocity;
	sf::Vector2f mMaxVelocity;
	sf::Vector2f mAcceleration;

	Direction mMovingDirection;

	// TODO: Flyweight
	unsigned int mSpriteWidth, mSpriteHeight;
	sf::IntRect mCurrentSpriteSheetLocation;
	bool mIsFacingRight;
	sf::Texture mTexture;
	sf::Sprite mSprite;
};


#endif /* CHARACTER_HPP */