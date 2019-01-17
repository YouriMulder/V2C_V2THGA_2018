#include "GameManager.hpp"
int main() {
	GameManager game = GameManager("../res/levels/all.txt");
	game.runGame();
}