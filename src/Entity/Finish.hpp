#ifndef FINISH_HPP
#define FINISH_HPP
#include "LevelObject.hpp"

/// \brief
/// This class is used to create finish points.

class Finish : public LevelObject{
public:
/// \brief
/// This is the constructor for the Finish class.
/// \param filename
/// This parameter is the name of the sprite.
/// \param position
/// This parameter is the position where the finish will be at.
/// \param size
/// This parameter is the size of the finish.
/// \param screenNumber
/// This parameter is the screen the finish will be drawn on.
/// \param repeated
/// This parameter determines whether the texture will be repeated multiple times or not.
	Finish(const std::string& filename, const sf::Vector2f& position, const sf::Vector2f& size,
		int screenNumber, bool repeated = false);
	virtual ~Finish();
};

#endif /*FINISH_HPP*/