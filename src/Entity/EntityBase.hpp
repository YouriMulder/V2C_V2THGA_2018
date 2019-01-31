#ifndef ENTITY_BASE_HPP
#define ENTITY_BASE_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <cstdint>

#include "../ViewManager.hpp"
#include "Side.hpp"


/// \brief
/// This is a general class for every entity in the game world.
/// \details
/// This class should be used as a parent class for every entity in the world.
/// Some of the methods must be overridden by the derived classes.
class EntityBase {
private: 
	/// \brief
	/// Increases the nextId by one.
	static void increaseNextId();

protected:
	/// \brief
	/// The first id which is free to use for a new EntityBase object.
	static uint_least64_t nextId;
	
	/// \brief
	/// The id of the EntityBase.
	uint_least64_t id;
	
	/// \brief
	/// The position of the EntityBase in the world.
	sf::Vector2f mPosition;

	/// \brief
	/// The size of the EntityBase.
	sf::Vector2f mSize;

	/// \brief
	/// The screen the EntityBase should be drawn to.
	int mScreenNumber;

	/// \brief
	/// The EntityBase is visible on the screen if this is true.\n
	/// The EntityBase is NOT visible on the screen if this is false.\n
	bool mIsVisible;

	/// \brief
	/// The EntityBase is solid on the screen if this is true.\n
	/// The EntityBase is NOT solid on the screen if this is false.\n
	bool mIsSolid;

	/// \brief
	/// The EntityBase should be destroyed if this is true.\n
	/// The EntityBase should NOT be destroyed if this is false.\n
	bool mShouldDestroyed;

public:
	/// \brief
	/// Set the nextId to zero. (Reset)
	/// \details
	/// This should be called when all EntityBase objects are destroyed.
	static void backToStartId();

	/// \brief
	/// This is the constructor for the EntityBase class.
	/// \param position
	/// The position where the EntityBase should spawn.
	/// \param size
	/// The size of the EntityBase.
	/// \param screenNumber
	/// The screenNumber where the EntityBase should be drawn to.
	/// \param isSolid
	/// Whether or not the EntityBase should be solid or not.
	/// \param isVisible
	/// Whether or not the EntityBase should be drawn to the screen.
	EntityBase(
		const sf::Vector2f& position, 
		const sf::Vector2f size, 
		int screenNumber,
		bool isSolid = true,
		bool isVisible = true
	);
	virtual ~EntityBase();
	
	/// \brief
	/// A method to get the id.
	/// \return
	/// An uint_least64_t containing the id of the EntityBase.
	uint_least64_t getId() const;

	/// \brief
	/// This method moves the EntityBase by adding the delta to mPosition.
	/// \param deltaX
	/// The amount of X you want to add to mPosition.
	/// \param deltaY
	/// The amount of Y you want to add to mPosition.
	void move(float deltaX, float deltaY);
	
	/// \brief
	/// This method moves the EntityBase by adding the delta to mPosition.
	/// \param deltaPosition
	/// The difference in position you want to add to mPosition.
	void move(const sf::Vector2f& deltaPosition);

	/// \brief
	/// This method sets the screenNumber.
	/// \param newScreenNumber
	/// The value you want to set screenNumber to.
	void setScreenNumber(int newScreenNumber);

	/// \brief
	/// This method returns the value of mScreenNumber.
	/// \return
	/// An int containing the value of mScreenNumber.
	int getScreenNumber() const;
	
	/// \brief
	/// This method sets mIsVisible.
	/// \param isVisible
	/// The value you want to set mIsVisible to.
	void setIsVisible(bool isVisible);

	/// \brief
	/// This method returns mScreenNumber.
	/// \return
	/// A bool containing the value of mIsVisible.
	bool isVisible() const;
	
	/// \brief
	/// This method sets mIsSolid.
	/// \param isSolid
	/// The value you want to set mIsSolid to.
	void setIsSolid(bool isSolid);

	/// \brief
	/// This method returns the value of mIsSolid.
	/// \return
	/// A bool containing the value of mIsSolid.
	bool isSolid() const;

	/// \brief
	/// This method sets mShouldDestroy to true.
	/// \details
	/// mShouldDestroy should be used to check if a EntityBase should be destroyed.
	/// So the object can be destroyed outside this class.
	void destroy();

	/// \brief
	/// This method returns mIsSolid.
	/// \return
	/// A bool containing the value of mIsSolid.
	bool shouldDestroy() const;

	/// \brief
	/// This is a virtual method should be 
	/// overridden if you want to hurt a EntityBase on damage. 
	virtual void hurt(uint_least8_t damage) {};

	/// \brief
	/// This method sets mPosition.
	/// \param x
	/// The value you want to set mPosition.x to.
	/// \param y
	/// The value you want to set mPosition.y to.
	void setPosition(float x, float y);
	
	/// \brief
	/// This method sets mPosition.
	/// \param newPosition
	/// The value you want to set mPosition to.
	virtual void setPosition(const sf::Vector2f& newPosition);
	
	/// \brief
	/// This method sets mSize.
	/// \param newSize
	/// The value you want to set mSize to.
	void setSize(const sf::Vector2f& newSize);

	/// \brief
	/// This method returns the value of mSize.
	/// \return
	/// A sf::Vector2f containing the value of mSize.
	virtual sf::Vector2f getSize() const;

	/// \brief
	/// This method returns the value of mPosition.
	/// \return
	/// A sf::Vector2f containing the value of mPosition.
	virtual sf::Vector2f getPosition() const;
	
	/// \brief
	/// This method returns the next position the EntityBase will be.
	/// \details
	/// Note that in the derived classes the nextPosition could be different.
	/// \return
	/// A sf::Vector2f containing the value of mPosition.
	virtual sf::Vector2f getNextPosition() const;
	
	/// \brief
	/// This method returns the global bounds of the EntityBase.
	/// \return
	/// A sf::Vector2f containing the global bounds of the EntityBase.
	virtual sf::FloatRect getGlobalBounds() const;
	
	/// \brief
	/// This method is used to check if the EntityBase is finished.
	/// \return
	/// A bool containing whether the EntityBase is finshed or not.
	virtual bool isFinished() const;
	
	/// \brief
	/// A pure virtual method used to update the EntityBase.
	/// \param deltaTime
	/// The time between the last update and this update.
	/// Used to make movement based on time not framerate.
	virtual void update(const sf::Time& deltaTime) = 0;
	
	/// \brief
	/// Function used to handle collisions.
	/// \details
	/// This method is most of the time overridden in 
	/// derived classes to get the correct behaviour. 
	/// \param top
	/// This contains all the objects that the Character collides with on the top.
	/// \param bottom
	/// This contains all the objects that the Character collides with on the bottom.	
	/// \param left
	/// This contains all the objects that the Character collides with on the left.
	/// \param right
	/// This contains all the objects that the Character collides with on the right.
	/// \param hitSides
	/// This contains booleans of all sides which are true 
	/// when something collided on that side.
	virtual void handleCollision(
		std::vector<std::unique_ptr<EntityBase>*> top, 
		std::vector<std::unique_ptr<EntityBase>*> bottom, 
		std::vector<std::unique_ptr<EntityBase>*> left, 
		std::vector<std::unique_ptr<EntityBase>*> right, 
		CollisionSides hitSides
	) {};

	/// \brief
	/// This function is called when no collision is detected.
	/// \details
	/// This method is most of the time overridden in 
	/// derived classes to get the correct behaviour. 
	virtual void handleNoCollision() {};
	
	/// \brief
	/// This method removes the non solid objects from the vector 
	// and sets the hit side to false if no solid object is hit	
	/// \param top
	/// This contains all the objects that the Character collides with on the top.
	/// \param bottom
	/// This contains all the objects that the Character collides with on the bottom.	
	/// \param left
	/// This contains all the objects that the Character collides with on the left.
	/// \param right
	/// This contains all the objects that the Character collides with on the right.
	/// \param hitSides
	/// This contains booleans of all sides which are true 
	/// when something collided on that side.
	void removeNonSolid(
		std::vector<std::unique_ptr<EntityBase>*>& top, 
		std::vector<std::unique_ptr<EntityBase>*>& bottom, 
		std::vector<std::unique_ptr<EntityBase>*>& left, 
		std::vector<std::unique_ptr<EntityBase>*>& right, 
		CollisionSides& hitSides
	) const;

	/// \brief
	/// This method handles changing color if overridden.
	virtual void setColor(const sf::Color& newColor) {};
	
	/// \brief
	/// This method draws to the sf::RenderWindow if mIsVisible is true.
	/// \param window
	/// The window you want to draw to.
	void drawIfVisible(sf::RenderWindow& window); 
	
	/// \brief
	/// This method draws to the ViewManager if mIsVisible is true.
	/// \param window
	/// The window you want to draw to.
	void drawIfVisible(ViewManager& window); 	

	/// \brief
	/// This pure virtual method draws the EntityBase to the sf::RenderWindow.
	/// \param window
	/// The window you want to draw to.
	virtual void draw(sf::RenderWindow& window) = 0;

	/// \brief
	/// This pure virtual method draws to the sf::RenderWindow.
	/// \details
	/// You should select the correct screen before drawing using ViewManager.
	/// \param window
	/// The window you want to draw to.
	virtual void draw(ViewManager& window) = 0;
};

#endif /* ENTITY_BASE_HPP */