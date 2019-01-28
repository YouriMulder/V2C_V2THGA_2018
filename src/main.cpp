#include "GameManager.hpp"

int main() {
	sf::VideoMode target;
	auto fsModes = sf::VideoMode::getFullscreenModes();
	for (const auto & fsMode : fsModes) {
		if (fsMode == sf::VideoMode(1920, 1080)) {
			target = fsMode;
			break;
		} else {
			target = sf::VideoMode::getDesktopMode();
		}
	}
	GameManager game("../res/levels/all.txt",target);
	game.runGame();
}