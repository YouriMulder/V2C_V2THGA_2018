#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Entity/Character.hpp"
#include "Entity/EntityBase.hpp"
#include <iostream>
#include <memory>
#include <vector>
#include "Collision.hpp"
#include "ViewManager.hpp"
#include "action.hpp"
#include "GameManager.hpp"
int main() {
	GameManager game = GameManager("../dependencies/levels/all.txt");
	game.runGame();
}