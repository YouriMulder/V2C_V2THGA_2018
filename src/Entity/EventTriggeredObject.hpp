#ifndef EVENTTRIGGEREDOBJECT_HPP
#define EVENTTRIGGEREDOBJECT_HPP

#include "LevelObject.hpp"
#include <functional>
class EventTriggeredObject : public LevelObject {
private:
	/// \brief
	/// The work that needs to be done when a object is hit.
	std::function<void()> mWork;

	sf::RectangleShape mHitBox;

	/// \brief
	/// This is set when a ojbect needs to be destroyed on collision.
	bool mDestroyOnCollision;

public:

	/// \brief
	/// Contructor for Eventtriggerd object.
	/// \details
	/// \param filename
	/// The filename of the sprite.
	/// \param position 
	/// The position for the object.
	/// \param size
	/// The size of the object.
	/// \param screenNumber
	/// The screen number on which the object needs to be drawn.
	/// \param work
	/// The method that needs to be called when an object is hit.
	/// \param destroyOnCollision
	/// The bool if the object needs to be destroyed.
	/// \param hitBoxPosition
	/// The possition of the hitbox on which the object needs to be triggered.
	/// \param hitBoxSize 
	/// The size of the hitbox on which the object needs to be triggered.
	/// \param repeated
	/// Boolean to set if the texture needs to be repeated.
	/// \param isVisible
	/// The boolean to set the initial visability.
	EventTriggeredObject(const std::string& filename, const sf::Vector2f& position, const sf::Vector2f& size,
		int screenNumber, std::function<void()> work, bool destroyOnCollision, const sf::Vector2f& hitBoxPosition, const sf::Vector2f& hitBoxSize, bool repeated = false, bool isVisible = true );
	

	/// \brief
	/// Handle collision method for event triggerd object.
	/// \details
	/// When a player hits the object it is either destroyed or made visible. \n
	/// This depends on the destroyOnCollision boolean when this is set the object is default visible. \n
	/// When the object is hit and the boolean is set it will be destroyed. \n
	/// If the boolean is not set it will only be made visible.
	virtual void handleCollision(
		std::vector<std::unique_ptr<EntityBase>*> top,
		std::vector<std::unique_ptr<EntityBase>*> bottom,
		std::vector<std::unique_ptr<EntityBase>*> left,
		std::vector<std::unique_ptr<EntityBase>*> right,
		CollisionSides hitSides
	) override;

	/// \brief
	/// Method to handle everything when there is no collision detected.
	virtual void handleNoCollision() override;

	/// \brief
	/// Method to get the FloatRect from the hitbox
	virtual sf::FloatRect getGlobalBounds() const override;
	virtual ~EventTriggeredObject();
};
#endif /*EVENTTRIGGEREDOBJECT_HPP*/

