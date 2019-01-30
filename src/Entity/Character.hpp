#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <utility>
#include <queue>
#include <functional>
#include <vector>
#include <memory>
#include <cstdint>
#include <optional>


#include "EntityBase.hpp"
#include "../EventManager.hpp"
#include "../ViewManager.hpp"
#include "Timer.hpp"

/// \brief
/// This struct is used to store the data of an animation.
struct AnimationSequence {
	/// \brief
	/// The start point of the animation in the spritesheet.
	/// \details
	/// The first value is the row and the second value is the column.
	/// The size is used to calculate the startpoint in pixels.
	sf::Vector2i start;

	/// \brief
	/// The end point of the animation in the spritesheet.
	/// \details
	/// The first value is the row and the second value is the column.
	/// The size is used to calculate the endpoint in pixels.
	sf::Vector2i end;

	/// \brief
	/// The size of a single picture of the animation in the spritesheet.
	sf::Vector2f size;
	
	/// \brief
	/// The time a single picture is displayed in this sequence.
	sf::Time displayTime;

	/// \brief
	/// This is the constructor for the AnimationSequence.
	/// \param start
	/// The start point of the animation in the spritesheet.
	/// \param end
	/// The end point of the animation in the spritesheet.
	/// \param size
	/// The size of a single picture of the animation in the spritesheet.
	/// \param displayTime
	/// The time a single picture is displayed in this sequence.
	AnimationSequence(	
		sf::Vector2i start,
		sf::Vector2i end,
		sf::Vector2f size,
		sf::Time displayTime
	): 
		start(start), end(end), size(size), displayTime(displayTime)
	{}
};

/// \brief
/// This is the Character class.
/// \details
/// This class is used to make non playable characters and players for the game.
/// The methods shared among all the characters in the game are in this class.
class Character : public EntityBase {
public:
	/// /brief
	/// This are all the states a Character could be in.
	/// \details
	/// These states are mostly used to choose the right animation of the Character.
	/// mState will be updated using the updateState method.
	enum class State {
		Idle,		/// < The Character is doing nothing. 
		Moving,		/// < The Character is walking.
		Running,	/// < The Character is running.
		Jumping,	/// < The Character is jumping.
		Falling,	/// < The Character is falling.
		Shooting,	/// < The Character is shooting energy bolts.
	};

	/// \brief
	/// The actions which a Character is able to perform.
	/// \details
	/// These actions are given to the performAction method to perform a given action.
	/// After calling the perform method the state is automatically updated if the state of the Character changed.
	enum class Action {
		Left,	/// < The Character is going to the left side. 
		Right,	/// < The Character is going to the right side. 
		Jump,	/// < The Character is going to jump in the air. 
		Run,	/// < The Character is going to run.
		Shoot,	/// < The Character is going to shoot a energy bolt.
		None	/// < The Character is going to do nothing. Also known as Idle.
	};
	
	/// \brief
	/// This is the constructor of the Character class.
	/// \param position
	/// The position the Character should spawn.
	/// \param size
	/// The size of the Character. 
	/// Most of the time the same size as one single picture in the sprite
	/// \param maxVelocity
	/// The maximum velocity the Character is able to move at.
	/// \param acceleration
	/// The amount of speed the Character gains per update if moving in a direction.
	/// \param characterSheetPath
	/// The path to the spritesheet of the Character.
	Character(		
		const sf::Vector2f& position,
		const sf::Vector2f& size,
		int screenNumber, 
		const sf::Vector2f& maxVelocity, 
		const sf::Vector2f& acceleration,
		const std::string& characterSheetPath
	);
	virtual ~Character() override;

	/// \brief
	/// This method adds a new action to mUnperformedActions.
	/// \details
	///	The action will be performed the next time the all the unperformed actions will be called.
	/// \param newAction
	/// The action you want to add to the unperformed actions.
	void addAction(const Action& newAction);
	
	/// \brief
	/// This method binds an event to an action.
	/// \details
	/// This is used to bind keybindings or other conditions to perform an action. 
	/// \param event
	/// The event you want to bind the a given action.
	void bindAction(const EventManager& event);
	
	/// \brief
	/// This method is should be overridden if you want to bind multiple actions at once.
	/// \details
	/// This method is called on construction.
	virtual void bindActions() {};

	/// \brief
	/// This method binds a state to an AnimationSequence.
	/// \details
	/// The animation of the AnimationSequence will be performed 
	/// when the Character is in the given state.
	/// \param state 
	/// The state you want to bind to an animation.
	/// \param animationSequence
	/// The animation you want to bind to a given state.
	void bindAnimation(
		const State& state, 
		const AnimationSequence& animationSequence
	);

	/// \brief
	/// This method should be overridden if you want to bind multiple animations at once.
	/// \details
	/// This method is called on construction.
	virtual void bindAnimations() {};

	/// \brief
	/// This method moves the Character.
	/// \param delta
	/// The delta position you want to move the player.
	/// \details
	/// This method moves the Character using the delta.
	/// The Character will only move to the side is not restricted.
	void move(sf::Vector2f& delta);

	/// \brief
	/// This method is used to apply the right movement given an action using the velocity.
	/// \details
	/// If the direction is left the Character will move left and vise versa.
	/// The method updates mVelocity.
	/// \param direction
	/// The direction you want to move in.
	void applyMovement(const Action& direction);

	/// \brief
	/// This method updates the facing direction.
	/// \details
	/// mIsFacingRight will be set to true if the player is moving right.
	/// When the player is moving left it will be set to false.
	/// When the player is not moving the 
	/// same direction the player was facing before will be kept.
	void updateFacingDirection();

	/// \brief
	/// This method adds a given delta velocity to the current mVelocity.
	/// \details
	/// mVelocity is updated and kept under the (-)mMaxVelocity.
	/// When the Character is running the mMaxVelocity is multiplied by 2.
	/// \param deltaVelocity
	/// This is the velocity you want to add to mVelocity.
	void updateVelocity(const sf::Vector2f& deltaVelocity);
	
	/// \brief
	/// This method sets the Y direction of mVelocity to 0.
	void resetVelocityY();

	/// \brief
	/// This method sets the X direction of mVelocity to 0.
	void resetVelocityX();

	/// \brief
	/// This method checks whether the Character is moving in the X direction.
	/// \details
	/// If mVelocity.x is 0 this method will return false otherwise it will return true.
	bool isMovingX() const;

	/// \brief
	/// This function updates the current state of the Character.
	/// \details
	/// A parameter action is passed into this method, 
	/// using that action the new mState is determent.
	/// \param action
	/// This is the action the Character is currently performing.
	void updateState(const Action& action);

	/// \brief
	/// This method starts the hurting animation.
	/// \details
	/// The hurtClock is restarted and mIsHurting is set to true.
	/// The player starts now starts flickering.
	/// This flickering animation is handled by the animate method.
	/// Everytime a new picture is being set in the animate method 
	/// setIsVisible is toggled.
	void startHurtAnimation();

	/// \brief
	/// This method is used to animate the Character his movement.
	/// \details
	/// This method is used to show the Character's animation on the screen.
	/// This is done using a vector containing std::pairs, this vector is called mAnimations.
	/// The vector is filled using bindAnimation and bindAnimations.
	/// In this vector the first item of the pair is the state 
	/// and the second the AnimationSequence that should be displayed in that state.
	/// \param deltaTime
	/// The amount of time between the past update and this update.
	/// This is used to check whether a new picture should be selected.
	void animate(const sf::Time& deltaTime);
	
	/// \brief
	/// This method moves the Character to the left using applyMovement.
	void left();

	/// \brief
	/// This method moves the Character to the right using applyMovement.
	void right();

	/// \brief
	/// This method makes the Character jump into the air.
	/// \details
	/// A Character is able to single jump and double jump.
	/// Double jump can only be triggered when you are falling down after jumping. 
	void jump();

	/// \brief
	/// This method makes the Character run using applyMovement.
	void run();

	/// \brief
	/// This method is used to shoot a projectile.
	/// \details
	/// When mShootTimer is expired the Character is able to shoot.
	/// mShootTimer is restarted and mIsShooting is set to true.
	/// \returns
	/// A bool containing whether the player was able to shoot or not.
	virtual bool shoot();

	/// \brief
	/// This method returns the value of mIsShooting.
	/// \return
	/// A bool containing the value of mIsShooting.
	virtual bool isShooting() const;

	/// \brief
	/// This method returns a projectile when the Character is shooting.
	/// \details
	/// Using this method a new projectile is made. 
	/// This projectile exists until a collision is detected.
	/// \return
	/// An std::optional containing a projectile when mIsShooting is true.
	/// if mIsShooting is false the std::optional is empty.
	std::optional<std::unique_ptr<EntityBase>> getProjectile();

	/// \brief
	/// This method performs the given action.
	/// \param unperformedAction
	/// This is the action you want to perform.
	void performAction(const Action& unperformedAction);
	
	/// \brief
	/// This method returns the size of the Character.
	/// \return 
	/// A sf::Vector2f containing the size of the Character.
	virtual sf::Vector2f getSize() const override;

	/// \brief
	/// This method returns the global bounds of the Character.
	/// \return
	/// a Sf::FloatRect containing the global bounds of the Character.
	virtual sf::FloatRect getGlobalBounds() const override;
	
	/// \brief
	/// This method sets the scale of mSprite and updates mSize accordingly.
	void setSpriteScale(float x, float y);
	
	/// \brief
	/// This method updates mSize using the global bounds of mSprite.
	void updateSizeUsingSprite();

	/// \brief
	/// This method returns the value of mIsFinished.
	/// \return
	/// A bool containing the value of mIsFinished.
	virtual bool isFinished() const override;

	/// \brief
	/// This method handles the collision for a Character.
	/// \details
	/// This method is called by the Collision class.
	/// In this method the restricted sides is updated,
	/// mIsInAir is set to false when the Character hits the ground,
	/// the position is set correctly when standing on a moving object, etc.
	/// If you want a more in depth view what's happening in this method.
	/// You should check the defintion.
	virtual void handleCollision(
		std::vector<std::unique_ptr<EntityBase>*> top, 
		std::vector<std::unique_ptr<EntityBase>*> bottom, 
		std::vector<std::unique_ptr<EntityBase>*> left, 
		std::vector<std::unique_ptr<EntityBase>*> right,  
		CollisionSides hitSides
	) override;

	/// \brief
	/// This method handles a no collision.
	/// \details
	/// When this method is called it means there was no collision with anything.
	/// This method is called by the Collision class.	
	virtual void handleNoCollision() override;

	/// \brief
	/// This method updates all the values in the Character.
	/// \details
	/// A few values are updates when this function is called. \n
	/// For example: \n
	/// Direction/movement is updated \n
	/// mState is updated \n
	/// Unperformed actions will be performed \n
	/// Player animation is called \n
	virtual void update(const sf::Time& deltaTime) override;
	
	/// \brief
	/// This method draws the Character to a sf::RenderWindow.
	virtual void draw(sf::RenderWindow& window) override;
	
	/// \brief
	/// This method draws the Character to a ViewManager.
	/// \warning
	/// The right screen inside the ViewManager must be selected before drawing.
	virtual void draw(ViewManager& window) override;

protected:
	/// \brief
	/// The id of a Character used to 
	/// identify which Character it is.
	uint_least64_t id;

	/// \brief
	/// The current velocity of the Character 
	/// used to move the Character.
	sf::Vector2f mVelocity;

	/// \brief
	/// The mamixum velocity of the Character.
	/// The Character is not able to exceed this velocity.
	sf::Vector2f mMaxVelocity;

	/// \brief
	/// The amount of acceleration of the Character.
	sf::Vector2f mAcceleration;

	/// \brief
	/// The Character is facing right if this is true.\n
	/// The Character is facing left if this is false.
	bool mIsFacingRight;

	/// \brief
	/// The Character is in the air if this is true.\n
	/// The Character is on the ground if this is false.
	bool mIsInAir;
	
	/// \brief
	/// The Character is in the air if this is true.\n
	/// The Character is on the ground if this is false.
	bool mIsJumping;

	/// \brief
	/// The Character is in the air if this is true.\n
	/// The Character is on the ground if this is false.
	bool mCanDoubleJump;

	/// \brief
	/// The Character is running if this is true.\n
	/// The Character is running if this is false.
	bool mIsRunning;

	/// \brief
	/// The Character is shooting if this is true.\n
	/// The Character is shooting if this is false.
	bool mIsShooting;

	/// \brief
	/// The Character is finished if this is true.\n
	/// The Character is finished if this is false.
	bool mIsFinished;
	
	/// \brief
	/// The previous state the Character was in.
	State mPreviousState;

	/// \brief
	/// The current state the character is in.
	State mState;

	/// \brief
	/// The texture of the Character.
	sf::Texture mTexture;

	/// \brief
	/// The sprite of the Character.
	sf::Sprite mSprite;
	
	/// \brief
	/// The Character is hurting if this is true.\n
	/// The Character is hurting if this is false.
	bool mIsHurting = false;
	
	CollisionSides mRestrictedSides;
	
	float mGravity = 0.0f;
	float mStartingJumpForce = -7.0f;
	float mJumpForce = mStartingJumpForce;
	float mMaxGravity = 7.0f;
	float mJumpAcceleration = 0.3f;
	float mGravityAcceleration = 0.3f;

	/// \brief
	/// The timer to stop the Character from shooting continuesly.
	Timer mShootTimer;

	/// \brief
	/// The time there is be between shots.
	sf::Time mTimeBetweenShots = sf::seconds(1);
	
	/// \brief
	/// The last time a new picture has been set during a AnimationSequence.
	sf::Time mTimeSinceLastAnimation;
	
	/// \brief
	/// The timer used to check if the hurt animation should stop.
	Timer mHurtTimer;
	
	/// \brief
	/// The time the hurt animation is shown.
	sf::Time mTotalHurtTime = sf::seconds(1);

	/// \brief
	/// All the unperformed actions.
	/// These will be performed in the update method.
	std::queue<Action> mUnperformedActions = {};
	
	/// \brief
	/// The current location in the spritesheet.
	/// \details 
	/// The pixel location is calculated using the size.
	sf::Vector2i currentSprite = sf::Vector2i(0,0);

	/// \brief
	/// These are all the possible action which can be performed.
	/// \details
	/// When performAction is called the right action 
	/// is searched in this vector and the std::function is called.
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
		std::make_pair(
			Action::Shoot, 	[this](){shoot();}
		),
	};

	/// \brief
	/// These are all the states which should be filled in any derived class.
	/// \details
	/// You should bind these in the derived class.
	std::vector<std::pair<State, AnimationSequence>> mAnimations = {};
	
	/// \brief
	/// These are all the events/actions the Character has.
	/// \details
	/// You should bind these in the derived class.
	std::vector<EventManager> actions = {};
};


#endif /* CHARACTER_HPP */