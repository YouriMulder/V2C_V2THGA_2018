#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <utility>
#include <vector>

#include "EntityBase.hpp"
#include "../ViewManager.hpp"
#include "Animation.hpp"

struct animationSequence {
	sf::Vector2i start;
	sf::Vector2i end;
	sf::Vector2f size;
	sf::Time displayTime;

	animationSequence(	
		sf::Vector2i start,
		sf::Vector2i end,
		sf::Vector2f size,
		sf::Time displayTime
	): 
		start(start), end(end), size(size), displayTime(displayTime)
	{}
};

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
	void setState(const State& newState);
	void animate(const sf::Time& deltaTime);
	void jump(); 
	void attack();
	void getHurt(int damage);
	
	void updateVelocity(const sf::Vector2f& deltaVelocity);
	void applyFrictionOneAxis(float& axisVelocity, const float& friction);
	void applyFriction();
	virtual void update(const sf::Time& deltaTime);
	virtual void draw(sf::RenderWindow& window) override;
	virtual void draw(ViewManager& window) override;

private:
	sf::Vector2f mVelocity;
	sf::Vector2f mMaxVelocity;
	sf::Vector2f mAcceleration;

	Direction mMovingDirection;
	bool mIsFacingRight;
	State mPreviousState;
	State mState;

	// TODO: Flyweight
	unsigned int mSpriteWidth, mSpriteHeight;
	sf::IntRect mCurrentSpriteSheetLocation;
	sf::Texture mTexture;
	sf::Sprite mSprite;


	sf::Time timeSinceLastAnimation;
	
	sf::Vector2i currentSprite = sf::Vector2i(0,0);
	std::vector<std::pair<State, animationSequence>> animations = {
		std::make_pair(State::Idle, 
			animationSequence(
				sf::Vector2i(0,0),
				sf::Vector2i(12,0),
				mSize,
				sf::milliseconds(100)
			)
		),
		std::make_pair(State::Moving, 
			animationSequence(
				sf::Vector2i(0,1),
				sf::Vector2i(8,1),
				sf::Vector2f(21.0f, 34.0f),
				sf::milliseconds(125)
			)
		),
	};


};


#endif /* CHARACTER_HPP */