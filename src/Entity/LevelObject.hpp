#ifndef LEVELOBJECT_HPP
#define LEVELOBJECT_HPP

#include "SFML/Graphics.hpp"
#include "EntityBase.hpp"
#include "../ViewManager.hpp"
#include <string>

class LevelObject : public EntityBase {
protected:
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
	/// \param screenNumber
	/// 
	/// \param repeated
	/// A boolean that decides if the picture is repeated default is false
	LevelObject(const std::string& filename, const sf::Vector2f& position, const sf::Vector2f& size,
		const sf::IntRect& picturepart, int screenNumber, bool repeated = false);

	/// \brief
	/// Constructor for Platform
	/// \details
	/// Constructs a platform based on the given parameters
	/// \param filename
	/// Filename of the picture that is used as a texture for the platform
	/// \param repeated
	/// A boolean that decides if the picture is repeated default is false
	LevelObject(const std::string& filename, const sf::Vector2f& position, const sf::Vector2f& size,
		int screenNumber, bool repeated = false);

	virtual ~LevelObject();

	/// \brief
	/// Changes the size of the platform
	void resize(float width, float height);

	/// \brief
	/// Changes the size of the platform
	void resize(const sf::Vector2f& newSize);

	/// \brief
	/// Changes the width of the platform
	void resizeWidth(float width);

	/// \brief
	/// Changes the height of the platform
	void resizeHeight(float height);

	/// \brief
	/// Draws the platform in the given window
	virtual void draw(sf::RenderWindow& window) override;

	/// \brief
	/// Draws the platform in the given window
	virtual void draw(ViewManager& window) override;

	/// \brief
	/// Updates the position of the platform
	virtual void update(const sf::Time& deltaTime) override;

	/// \brief
	/// Return the position of the sprite
	virtual sf::Vector2f getPosition() const override;

	/// \brief
	/// Returns the outline of the platform
	virtual sf::FloatRect getGlobalBounds() const override;
};

#endif /* LEVELOBJECT_HPP */