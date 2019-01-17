#include "GameManager.hpp"
int main() {
	GameManager game = GameManager("../dependencies/levels/all.txt");
	game.runGame();
}