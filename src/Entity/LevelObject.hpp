#ifndef LEVELOBJECT_HPP
#define LEVELOBJECT_HPP

#include "SFML/Graphics.hpp"
#include "EntityBase.hpp"
#include "../ViewManager.hpp"
#include <string>

class LevelObject : public EntityBase {
protected:
	/// \brief
	/// Image stored in a texture.
	sf::Texture mTexture;

	/// \brief
	/// Sprite that contains a texture.
	sf::Sprite mSprite;
public:
	/// \brief
	/// Constructor for LevelObject.
	/// \details
	/// Constructs a LevelObject based on the given parameters.
	/// \param filename
	/// Filename of the picture that is used as a texture for the LevelObject.
	/// \param position
	/// The position where the LevelObject is drawn (x/y).
	/// \param size
	/// The size of the LevelObject (width/height).
	/// \param picturepart
	/// The part of the picture that is used as a texture for the LevelObject.
	/// \param screenNumber
	/// The screen on which the LevelObject is drawn.
	/// \param repeated
	/// A boolean that decides if the picture is repeated default is false.
	LevelObject(const std::string& filename, const sf::Vector2f& position, const sf::Vector2f& size,
		const sf::IntRect& picturepart, int screenNumber, bool repeated = false);

	/// \brief
	/// Constructor for LevelObject.
	/// \details
	/// Constructs a LevelObject based on the given parameters.
	/// \param filename
	/// Filename of the picture that is used as a texture for the LevelObject.
	/// \param position
	/// The position where the LevelObject is drawn (x/y).
	/// \param size
	/// The size of the LevelObject (width/height).
	/// \param screenNumber
	/// The screen on which the LevelObject is drawn.
	/// \param repeated
	/// A boolean that decides if the picture is repeated default is false.
	LevelObject(const std::string& filename, const sf::Vector2f& position, const sf::Vector2f& size,
		int screenNumber, bool repeated = false);

	virtual ~LevelObject();

	void matchSizeWithSprite();

	/// \brief
	/// Changes the size of the LevelObject.
	void resize(float width, float height);

	/// \brief
	/// Changes the size of the LevelObject.
	void resize(const sf::Vector2f& newSize);

	/// \brief
	/// Changes the width of the LevelObject.
	void resizeWidth(float width);

	/// \brief
	/// Changes the height of the LevelObject.
	void resizeHeight(float height);

	virtual void setPosition(const sf::Vector2f& newPosition) override;

	/// \brief
	/// Draws the LevelObject in the given window.
	virtual void draw(sf::RenderWindow& window) override;

	/// \brief
	/// Draws the LevelObject in the given window.
	virtual void draw(ViewManager& window) override;

	/// \brief
	/// Updates the position of the LevelObject.
	virtual void update(const sf::Time& deltaTime) override;

	/// \brief
	/// Return the position of the LevelObject.
	virtual sf::Vector2f getPosition() const override;

	/// \brief
	/// Returns the outline of the LevelObject.
	virtual sf::FloatRect getGlobalBounds() const override;
};

#endif /* LEVELOBJECT_HPP */