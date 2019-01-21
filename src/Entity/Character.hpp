#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <utility>
#include <queue>
#include <functional>
#include <vector>
#include <memory>

#include "EntityBase.hpp"
#include "../EventManager.hpp"
#include "../ViewManager.hpp"

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
	enum class State {
		Idle,
		Moving,
		Jumping,
		Falling,
		Attacking
	};

	enum class Action {
		Left,
		Right,
		Jump,
		Duck,
		Punch,
		None
	};
	
	Character(		
		const sf::Vector2f& position,
		const sf::Vector2f& size,
		int screenNumber, 
		const sf::Vector2f& maxVelocity, 
		const sf::Vector2f& acceleration
	);
	
	virtual ~Character() override;

	void addAction(const Action& newAction);

	void move(sf::Vector2f& delta);
	void setMoveDirection(const Action& newDirection);
	void applyMovement(const Action& direction);

	void updateFacingDirection();
	void setState(const State& newState);
	void updateState(const Action& action);
	void animate(const sf::Time& deltaTime);
	
	void left();
	void right();
	void jump(); 

	void attack();
	void getHurt(int damage);
	
	void applyGravity();
	void updateVelocity(const sf::Vector2f& deltaVelocity);
	void resetVelocityY();
	void resetVelocityX();

	void applyFrictionOneAxis(float& axisVelocity, const float& friction);
	void applyFriction();
	
	void performAction(const Action& unperformedAction);
	virtual void handleCollision(
		std::vector<std::unique_ptr<EntityBase>*> others, 
		CollisionSides hitSides
	); 
	virtual void handleNoCollision() override;
	virtual sf::FloatRect getGlobalBounds() const override;
	virtual void update(const sf::Time& deltaTime) override;
	virtual void draw(sf::RenderWindow& window) override;
	virtual void draw(ViewManager& window) override;

	bool mSelected;

public:
	sf::Vector2f mVelocity;
	sf::Vector2f mMaxVelocity;
	sf::Vector2f mAcceleration;

	sf::Vector2f mGravity = { 0, 0 };
	sf::Vector2f mJumpForce = { 0, -2 };

	bool mIsFacingRight;
	bool mIsInAir;
	bool mIsJumping;
	State mPreviousState;
	State mState;

	// TODO: Flyweight
	unsigned int mSpriteWidth, mSpriteHeight;
	sf::IntRect mCurrentSpriteSheetLocation;
	sf::Texture mTexture;
	sf::Sprite mSprite;

	sf::Time timeSinceLastAnimation;

	CollisionSides restrictedSides;

	void select(bool selection);
	bool isSelected();

	std::queue<Action> mUnperformedActions = {};
	
	sf::Vector2i currentSprite = sf::Vector2i(0,0);
	
	std::vector< std::pair<Action, std::function<void()>> > mActions = {
		std::make_pair(
			Action::Left, 	[this](){left();}
		),
		std::make_pair(
			Action::Right, 	[this](){right();}
		),
		std::make_pair(
			Action::Jump, 	[this](){jump();}
		),
	};

	std::vector<std::pair<State, animationSequence>> mAnimations = {
		std::make_pair(State::Idle, 
			animationSequence(
				sf::Vector2i(0,0),
				sf::Vector2i(12,0),
				sf::Vector2f(20.0f, 35.0f),
				sf::milliseconds(100)
			)
		),
		std::make_pair(State::Moving, 
			animationSequence(
				sf::Vector2i(0,1),
				sf::Vector2i(8,1),
				sf::Vector2f(21.0f, 35.0f),
				sf::milliseconds(125)
			)
		),
		std::make_pair(State::Jumping, 
			animationSequence(
				sf::Vector2i(0,2),
				sf::Vector2i(1,2),
				sf::Vector2f(21.0f, 35.0f),
				sf::milliseconds(10)
			)
		),
		std::make_pair(State::Falling, 
			animationSequence(
				sf::Vector2i(0,4),
				sf::Vector2i(1,4),
				sf::Vector2f(21.0f, 35.0f),
				sf::milliseconds(10)
			)
		),
	};

	EventManager actions[17] = {
		EventManager(sf::Keyboard::Left, 	[&] 	{addAction(Character::Action::Left);	}),
		EventManager(sf::Keyboard::Right, 	[&] 	{addAction(Character::Action::Right);	}),
		EventManager(sf::Keyboard::Up, 		[&] 	{addAction(Character::Action::Jump);	}),
		EventManager(sf::Keyboard::Down, 	[&] 	{std::cout << "onderste pijltje \n";	}),
		EventManager(sf::Keyboard::Escape,	[&] 	{std::cout << " escape toets "; }),
		EventManager(sf::Keyboard::Space, 	[&] 	{addAction(Character::Action::Jump);	}),
		EventManager(sf::Mouse::Left, 		[&] 	{/*std::cout << "linker muis \n";*/ }),
		EventManager(sf::Keyboard::Num1, 	[&] 	{std::cout << "nummer 1 \n"; }),
		EventManager(sf::Keyboard::Num2, 	[&] 	{std::cout << "nummer 2 \n"; }),
		EventManager(sf::Keyboard::Num3, 	[&] 	{std::cout << "nummer 3 \n"; }),
		EventManager(sf::Keyboard::Num4, 	[&] 	{std::cout << "nummer 4 \n"; }),
		EventManager(sf::Keyboard::LShift, 	[&] 	{std::cout << "linker shift \n"; }),
		EventManager(sf::Keyboard::RShift, 	[&] 	{std::cout << "rechter shift \n"; }),
		EventManager(sf::Keyboard::W, 		[&] 	{std::cout << "w \n"; }),
		EventManager(sf::Keyboard::A, 		[&] 	{std::cout << "a\n"; }),
		EventManager(sf::Keyboard::S, 		[&] 	{std::cout << "s \n"; }),
		EventManager(sf::Keyboard::D, 		[&] 	{std::cout << "d \n"; })
	};

};


#endif /* CHARACTER_HPP */