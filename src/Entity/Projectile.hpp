#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "LevelObject.hpp"
#include "Timer.hpp"
#include <cstdint>

/// \brief
/// Class to construct a projectile.
class Projectile : public LevelObject {
	/// \brief
	/// Direction of the projectile.
	/// \details
	/// If this is true the projectile moves to the right.\n
	/// If this is false the projectile moves to the left.
	bool mIsDirectionRight;

	/// \brief
	/// Timer to destroy the projectile.
	/// \details
	/// After this timer ends the projectile is destructed.
	Timer destroyTimer;

	/// \brief
	/// The speed of the projectile.
	float mMovementPerSecond = 300.0f;

	/// \brief
	/// The amount of damage a projectile inflicts when it collisions.
	uint_least8_t mDamage = 1;

public:
	/// \brief
	/// Constructor for a projectile.
	/// \param filename
	/// The file used as a texture for the projectile.
	/// \param position
	/// The position from which the projectile will be shot.
	/// \param screenNumber
	/// The screen on which the projectile will be drawn.
	/// \param isDirectionRight
	/// The direction in which the projectile will be shot.
	Projectile(
		const std::string& filename, 
		const sf::Vector2f& position, 
		int screenNumber,
		bool isDirectionRight 
	);
	virtual ~Projectile();

	/// \brief
	/// Updates the projectile
	/// \details
	/// Updates the position of the projectile based on mMovementPerSecond and mIsDirectionRight.
	virtual void update(const sf::Time& deltaTime) override;

	/// \brief
	/// Handles collision for a projectile.
	/// \details
	/// Destructs the projectile and calls the hurt function of the object it collides with.
	virtual void handleCollision(
		std::vector<std::unique_ptr<EntityBase>*> top, 
		std::vector<std::unique_ptr<EntityBase>*> bottom, 
		std::vector<std::unique_ptr<EntityBase>*> left, 
		std::vector<std::unique_ptr<EntityBase>*> right, 
		CollisionSides hitSides
	) override;

};

#endif /* PROJECTILE_HPP */