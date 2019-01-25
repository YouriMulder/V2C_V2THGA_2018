#ifndef MOVEABLEPLATFORM_HPP
#define MOVEABLEPLATFORM_HPP

#include "SFML/Graphics.hpp"
#include "Platform.hpp"
#include <string>

class MoveablePlatform : public Platform {
private:
	/// \brief
	/// The beginpoint of the MoveablePlatform.
	sf::Vector2f mBeginpoint;

	/// \brief
	/// The endpoint of the MoveablePlatform.
	sf::Vector2f mEndpoint;

	/// \brief
	/// The speed of the MoveablePlatform.
	/// \details
	/// The distance the Moveableplatform travels each update.
	sf::Vector2f mSpeed;

	/// \brief
	/// A boolean that decides if the platform is moving forwards.
	bool mGoingForward = true;

	/// \brief
	/// A boolean that decides the starting direction.
	bool mReverse;
public:
	/// \brief
	/// Constructor for MoveablePlatform.
	/// \details
	/// Constructs a MoveablePlatform based on the given parameters.
	/// \param filename
	/// Filename of the picture that is used as a texture for the MoveablePlatform.
	/// \param position
	/// The position where the MoveablePlatform is drawn (x/y).
	/// \param size
	/// The size of the MoveablePlatform (width/height).
	/// \param picturepart
	/// The part of the picture that is used as a texture for the MoveablePlatform.
	/// \param screenNumber
	/// The screen on which the MoveablePlatform is drawn.
	/// \param moveRange
	/// The range the Moveableplatform has to move.
	/// \param amountOfSteps
	/// The amount of steps (updates) it will take to move the given distance.
	/// \param repeated
	/// A boolean that decides if the picture is repeated default is false.
	MoveablePlatform(const std::string& filename, const sf::Vector2f& position, const sf::Vector2f& size,
		const sf::IntRect& picturepart, int screenNumber, const sf::Vector2f& moveRange, int amountOfSteps, bool repeated = false);

	/// \brief
	/// Constructor for MoveablePlatform.
	/// \details
	/// Constructs a MoveablePlatform based on the given parameters.
	/// \param filename
	/// Filename of the picture that is used as a texture for the MoveablePlatform.
	/// \param position
	/// The position where the MoveablePlatform is drawn (x/y).
	/// \param size
	/// The size of the MoveablePlatform (width/height).
	/// \param picturepart
	/// The part of the picture that is used as a texture for the MoveablePlatform.
	/// \param screenNumber
	/// The screen on which the MoveablePlatform is drawn.
	/// \param moveRange
	/// The range the Moveableplatform has to move.
	/// \param amountOfSteps
	/// The amount of steps (updates) it will take to move the given distance.
	/// \param repeated
	/// A boolean that decides if the picture is repeated default is false.
	MoveablePlatform(const std::string& filename, const sf::Vector2f& position, const sf::Vector2f& size,
		int screenNumber, const sf::Vector2f& moveRange, int amountOfSteps, bool repeated = false);
	
	/// \brief
	/// Function for the next position
	/// \details
	/// This function returns the position of the MoveablePlatform after the next update.
	virtual sf::Vector2f getNextPosition() const override;

	/// \brief
	/// Updates the position of the platform.
	virtual void update(const sf::Time& deltaTime) override;
};

#endif