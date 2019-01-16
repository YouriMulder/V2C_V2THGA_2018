#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include "SFML/Graphics.hpp"

class Platform : public EntityBase {
private:
	/// \brief
	/// Image stored in a texture
	sf::Texture mTexture;
	
	/// \brief
	/// Sprite that contains a texture
	sf::Sprite mSprite;
public:
	/// \brief
	/// Constructor for Platform
	/// \details
	/// Constructs a platform based on the given parameters
	/// \param filename
	/// Filename of the picture that is used as a texture for the platform
	/// \param picturepart
	/// The part of the picture that is used as a texture for the platform
	/// \param repeated
	/// A boolean that decides if the picture is repeated default is false
	Platform(const char * filename, sf::Vector2f position, sf::Vector2f size, sf::IntRect picturepart, bool repeated = false);

	/// \brief
	/// Constructor for Platform
	/// \details
	/// Constructs a platform based on the given parameters
	/// \param filename
	/// Filename of the picture that is used as a texture for the platform
	/// \param repeated
	/// A boolean that decides if the picture is repeated default is false
	Platform(const char * filename, sf::Vector2f position, sf::Vector2f size, bool repeated = false);

	/// \brief
	/// Changes the size of the platform
	void resize(float width, float height);

	/// \brief
	/// Changes the width of the platform
	void resizeWidth(float width);

	/// \brief
	/// Changes the height of the platform
	void resizeHeight(float height);

	/// \brief
	/// Draws the platform in the given window
	void draw(sf::RenderWindow& window) override;

	/// \brief
	/// Updates the position of the platform
	void update() override;

	/// \brief
	/// Returns the outline of the platform
	sf::FloatRect getGlobalBounds();
};

#endif /*PLATFORM_HPP*/