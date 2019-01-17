#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include "SFML/Graphics.hpp"
#include "LevelObject.hpp"
#include "ViewManager.hpp"
#include <string>

class Platform : public LevelObject {
public:
	/// \brief
	/// Constructor for Platform
	/// \details
	/// Constructs a platform based on the given parameters
	/// \param filename
	/// Filename of the picture that is used as a texture for the platform
	/// \param picturepart
	/// The part of the picture that is used as a texture for the platform
	/// \param screenNumber
	/// 
	/// \param repeated
	/// A boolean that decides if the picture is repeated default is false
	Platform(const std::string& filename, const sf::Vector2f& position, const sf::Vector2f& size,
		const sf::IntRect& picturepart, int screenNumber, bool repeated = false);

	/// \brief
	/// Constructor for Platform
	/// \details
	/// Constructs a platform based on the given parameters
	/// \param filename
	/// Filename of the picture that is used as a texture for the platform
	/// \param repeated
	/// A boolean that decides if the picture is repeated default is false
	Platform(const std::string& filename, const sf::Vector2f& position, const sf::Vector2f& size,
		int screenNumber, bool repeated = false);

	/// \brief
	/// Returns the outline of the platform
	sf::FloatRect getGlobalBounds() const override;
};

#endif /* PLATFORM_HPP */