#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include "SFML/Graphics.hpp"
#include "LevelObject.hpp"
#include "../ViewManager.hpp"
#include <string>

class Platform : public LevelObject {
public:
	/// \brief
	/// Constructor for Platform.
	/// \details
	/// Constructs a platform based on the given parameters.
	/// \param filename
	/// Filename of the picture that is used as a texture for the platform.
	/// \param position
	/// The position where the platform is drawn (x/y).
	/// \param size
	/// The size of the platform (width/height).
	/// \param picturepart
	/// The part of the picture that is used as a texture for the platform.
	/// \param screenNumber
	/// The screen on which the platorm is drawn.
	/// \param repeated
	/// A boolean that decides if the picture is repeated default is false.
	Platform(const std::string& filename, const sf::Vector2f& position, const sf::Vector2f& size,
		const sf::IntRect& picturepart, int screenNumber, bool repeated = false);

	/// \brief
	/// Constructor for Platform.
	/// \details
	/// Constructs a platform based on the given parameters.
	/// \param filename
	/// Filename of the picture that is used as a texture for the platform.
	/// \param position
	/// The position where the platform is drawn (x/y).
	/// \param size
	/// The size of the platform (width/height).
	/// \param screenNumber
	/// The screen on which the platorm is drawn.
	/// \param repeated
	/// A boolean that decides if the picture is repeated default is false.
	Platform(const std::string& filename, const sf::Vector2f& position, const sf::Vector2f& size,
		int screenNumber, bool repeated = false);

	virtual ~Platform();

	/// \brief
	/// This method handles the collision when for the movingPlatform 
	virtual void handleCollision(
		std::vector<std::unique_ptr<EntityBase>*> top, 
		std::vector<std::unique_ptr<EntityBase>*> bottom, 
		std::vector<std::unique_ptr<EntityBase>*> left, 
		std::vector<std::unique_ptr<EntityBase>*> right, 
		CollisionSides hitSides
	) override;
};

#endif /* PLATFORM_HPP */