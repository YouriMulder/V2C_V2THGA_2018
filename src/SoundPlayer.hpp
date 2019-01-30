#ifndef SOUNDPLAYER_HPP 
#define SOUNDPLAYER_HPP
#include <string>
#include <SFML/Audio.hpp>

namespace Sounds {
	extern const std::string hurt;
	extern const std::string death;
}

class SoundPlayer {
private:
	std::string mPathSound = "../res/Sounds/SFX/";
	sf::Sound mCurrentSound;
	sf::SoundBuffer mBuffer;
public:
	SoundPlayer() {}
	void play(const std::string &filename);
	void makeBuffer(const std::string &filename);
};

#endif /*SOUNDPLAYER_HPP*/