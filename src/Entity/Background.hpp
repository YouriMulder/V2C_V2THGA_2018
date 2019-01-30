#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP
#include "LevelObject.hpp"

/// \brief
/// This is the background class.
class Background : public LevelObject {
public:
/// \brief
/// This is the constructor for the background class.
/// \param filename
/// This parameter is the name of the sprite.
/// \param position
/// This parameter is the position where the background will be at.
/// \param sizeTexture
/// This parameter is the size of the background image.
/// \param wantedSize
/// This parameter is the size you want the background to be.
/// \param screenNumber
/// This parameter is the screen the background will be drawn on.
/// \param repeated
/// This parameter determines whether the texture will be repeated multiple times or not.
	Background(const std::string& filename, const sf::Vector2f& position, const sf::Vector2f& sizeTexture, const sf::Vector2f & wantedSize,
		int screenNumber, bool repeated = false);
	virtual ~Background();
};

#endif /*BACKGROUND_HPP*/
