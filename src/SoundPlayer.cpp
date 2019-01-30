#include "SoundPlayer.hpp"
#include <iostream>
#include <string>

const std::string Sounds::hurt = "hurt.ogg";
const std::string Sounds::death = "death.ogg";
const std::string Sounds::slurp = "slurp.ogg";



void SoundPlayer::play(const std::string &filename) {
	mCurrentSound.stop();
	makeBuffer(filename);
	mCurrentSound.setBuffer(mBuffer);
	mCurrentSound.play();
}

void SoundPlayer::makeBuffer(const std::string &filename) {
	mBuffer.loadFromFile(mPathSound + filename);
}