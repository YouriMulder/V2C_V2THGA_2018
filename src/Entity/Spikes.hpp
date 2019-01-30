#ifndef SPIKES_HPP
#define SPIKES_HPP

#include <SFML/Graphics.hpp>

#include "EntityBase.hpp"
#include "LevelObject.hpp"
#include "Timers.hpp"
#include "../ViewManager.hpp"
#include <string>
#include <vector>
#include <cstdint>

class Spikes : public LevelObject {
private:
	/// \brief
	/// The amount of damage a spike does on collision.
	uint_least8_t mDamage;

	/// \brief
	/// The hitclocks to determine the intervals between the damage done.
	Timers hitClocks;
	
public:
	/// \brief
	/// Constructor for Spikes.
	/// \details
	/// Constructs a spike based on the given parameters.
	/// \param filename
	/// Filename of the picture that is used as a texture for the spikes.
	/// \param position
	/// The position where the spike is drawn (x/y).
	/// \param size
	/// The size of the spikes (width/height).
	/// \param picturepart
	/// The part of the picture that is used as a texture for the spikes.
	/// \param screenNumber
	/// The screen on which the spike is drawn.
	/// \param damage
	/// The amount of damage the spikes will do on collision.
	/// \param repeated
	/// A boolean that decides if the picture is repeated default is false.
	Spikes(const std::string& filename, const sf::Vector2f& position, const sf::Vector2f& size,
		const sf::IntRect& picturepart, int screenNumber, uint_least8_t damage, bool repeated = false);

	/// \brief
	/// Constructor for Spikes.
	/// \details
	/// Constructs a spike based on the given parameters.
	/// \param filename
	/// Filename of the picture that is used as a texture for the spikes.
	/// \param position
	/// The position where the spike is drawn (x/y).
	/// \param size
	/// The size of the spikes (width/height).
	/// \param screenNumber
	/// The screen on which the spike is drawn.
	/// \param damage
	/// The amount of damage the spikes will do on collision.
	/// \param repeated
	/// A boolean that decides if the picture is repeated default is false.
	Spikes(const std::string& filename, const sf::Vector2f& position, const sf::Vector2f& size,
		int screenNumber, uint_least8_t damage, bool repeated = false);


	/// \brief
	/// Returns the globalBounds of the sprite.
	virtual sf::FloatRect getGlobalBounds() const override;
	
	/// \brief
	/// handles collision for spikes
	/// \details
	/// Calls the hurt function of the object it collides with.
	virtual void handleCollision(
		std::vector<std::unique_ptr<EntityBase>*> top, 
		std::vector<std::unique_ptr<EntityBase>*> bottom, 
		std::vector<std::unique_ptr<EntityBase>*> left, 
		std::vector<std::unique_ptr<EntityBase>*> right,  
		CollisionSides hitSides
	) override;
	
	/// \brief
	/// Deletes the hitclocks that are expired.
	virtual void update(const sf::Time& deltaTime) override;
};

#endif /* SPIKES_HPP */