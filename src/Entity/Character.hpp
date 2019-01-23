#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <utility>
#include <queue>
#include <functional>
#include <vector>
#include <memory>
#include <cstdint>

#include "EntityBase.hpp"
#include "../EventManager.hpp"
#include "../ViewManager.hpp"

struct AnimationSequence {
	sf::Vector2i start;
	sf::Vector2i end;
	sf::Vector2f size;
	sf::Time displayTime;

	AnimationSequence(	
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
		Running,
		Jumping,
		Falling,
		Attacking
	};

	enum class Action {
		Left,
		Right,
		Jump,
		Run,
		Duck,
		Punch,
		None
	};
	
	Character(		
		const sf::Vector2f& position,
		const sf::Vector2f& size,
		int screenNumber, 
		const sf::Vector2f& maxVelocity, 
		const sf::Vector2f& acceleration,
		const std::string& characterSheetPath
	);
	
	virtual ~Character() override;

	static uint_least8_t getHealth();
	static bool isDead();
	static bool isAlive();

	void addAction(const Action& newAction);
	void bindAction(const EventManager& event);
	void bindAnimation(
		const State& state, 
		const AnimationSequence& animationSequence
	);

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
	void run();

	void attack();
	void getHurt(int damage);
	
	void applyGravity();
	void updateVelocity(const sf::Vector2f& deltaVelocity);
	void resetVelocityY();
	void resetVelocityX();
	bool isMovingX() const;

	void applyFrictionOneAxis(float& axisVelocity, const float& friction);
	void applyFriction();
	void performAction(const Action& unperformedAction);
	
	virtual sf::Vector2f getSize() const override;
	virtual sf::FloatRect getGlobalBounds() const override;
	void setSpriteScale(float x, float y);
	void updateSizeUsingSprite();
	virtual bool isFinished() override;
	virtual void handleCollision(
		std::vector<std::unique_ptr<EntityBase>*> top, 
		std::vector<std::unique_ptr<EntityBase>*> bottom, 
		std::vector<std::unique_ptr<EntityBase>*> left, 
		std::vector<std::unique_ptr<EntityBase>*> right,  
		CollisionSides hitSides
	) override; 
	virtual void handleNoCollision() override;	
	virtual void update(const sf::Time& deltaTime) override;
	virtual void draw(sf::RenderWindow& window) override;
	virtual void draw(ViewManager& window) override;

	virtual void bindActions() {};
	virtual void bindAnimations() {};
protected:
	// static
	static uint_least8_t health;
	
	sf::Vector2f mVelocity;
	sf::Vector2f mMaxVelocity;
	sf::Vector2f mAcceleration;

	float xOffset;

	float mGravity = 0;
	float mStartingJumpForce = -7;
	float mJumpForce = mStartingJumpForce;
	float mMaxGravity = 7;
	float mJumpAcceleration = 0.3;
	float mGravityAcceleration = 0.3;

	bool mCanDoubleJump = false;

	bool mIsFacingRight;
	bool mIsInAir;
	bool mIsJumping;
	bool mIsRunning;
	bool mIsFinished;
	bool mSelected;
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
		std::make_pair(
			Action::Run, 	[this](){run();}
		),
	};

	std::vector<std::pair<State, AnimationSequence>> mAnimations = {};
	std::vector<EventManager> actions = {};
};


#endif /* CHARACTER_HPP */