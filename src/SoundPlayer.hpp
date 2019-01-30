#ifndef SOUNDPLAYER_HPP 
#define SOUNDPLAYER_HPP
#include <string>
#include <SFML/Audio.hpp>

/// \brief
/// This namespace holds the paths for the sound effects.
namespace Sounds {
	extern const std::string hurt;
	extern const std::string death;
	extern const std::string slurp;
}
/// \brief
/// This class is used to play sounds.
class SoundPlayer {
private:
/// \brief
/// This string holds the path to the base path to the sound effects folder.
	const std::string mPathSound = "../res/Sounds/SFX/";
/// \brief
/// This sf::Sound is the last played sound.
	sf::Sound mCurrentSound;
/// \brief
/// This sf::SoundBuffer is the last soundfile that was opened.
	sf::SoundBuffer mBuffer;
/// \brief
/// This method sets the mBuffer with the given filename.
/// \param filename
/// This string is the filename of the sound file you want to open.
	void makeBuffer(const std::string &filename);
public:
/// \brief
/// Constructor for the SoundPlayer class.
	SoundPlayer() {}
/// \brief
/// This method plays a soundfile.
/// \param filename
/// This string is the filename of the sound file you want to play.
	void play(const std::string &filename);
};

#endif /*SOUNDPLAYER_HPP*/