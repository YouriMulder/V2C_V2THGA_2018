#include "Factory.hpp"
#include "Entity/Platform.hpp"
#include "Entity/Character.hpp"
#include "Entity/MoveablePlatform.hpp"
#include "Entity/Spikes.hpp"
#include "Entity/EntityBase.hpp"
#include <iostream>
#include "operator.hpp"

SettingsData Factory::readSettings(std::ifstream& text) {
	std::string name;
	SettingsData temp;
	
	text >> name;
	if (name == "SETTINGS:") {
		while (name != "SCREEN1") {
			text >> name;
			if (name == "noOfScreens") {
				int data;
				text >> data;
				temp.noOfScreens = data;
			}
			else if (name == "gameTime") {
				int data;
				text >> data;
				temp.gameDuration = data;
			}
			else if (name == "songName") {
				std::string data;
				text >> data;
				temp.songName = data;
			}
			else if (name == "levelSize") {
				sf::Vector2f data;
				text >> data;
				temp.levelSize = data;
			}
			else if (text.eof()) {
				return temp;
			}
		}
	}
	return temp;
}

void Factory::readObjects(std::ifstream& text, int amountOfScreens, std::vector<std::unique_ptr<EntityBase>> & staticObjects,
	std::vector<std::unique_ptr<EntityBase>> & movableObjects) {
	std::string name;
	text >> name;
	while (name != "SCREEN1") {
		text >> name;
	}

	for (int i = 1; i < amountOfScreens + 1; i++) {
		int errorCounter = 0;
		name = "skip";
		while (name != "SCREEN") {
			text >> name;
			if (name == "platform") {
				std::string textureName;
				sf::Vector2f position;
				sf::Vector2f size;
				bool textureRepeat;
				bool partBool;

				text >> textureName;
				text >> position >> size >> textureRepeat >> partBool;
				textureName = "../res/Textures/Platform/" + textureName;

				if (partBool) {
					sf::IntRect part;
					text >> part;
					staticObjects.push_back(std::make_unique<Platform>(textureName, position, size, part, i, textureRepeat));
				} else {
					staticObjects.push_back(std::make_unique<Platform>(textureName, position, size, i, textureRepeat));
				}
			} else if (name == "spike") {
				std::string textureName;
				sf::Vector2f position;
				sf::Vector2f size;
				int damage;
				bool textureRepeat;
				bool partBool;

				text >> textureName;
				text >> position >> size >> damage >> textureRepeat >> partBool;

				if (partBool) {
					sf::IntRect part;
					text >> part;
					staticObjects.push_back(std::make_unique<Spikes>(textureName, position, size, part, i, damage, textureRepeat));
				}
				else {
					staticObjects.push_back(std::make_unique<Spikes>(textureName, position, size, i, damage, textureRepeat));
				}
			} else if (name == "movePlatform") {
				std::string textureName;
				sf::Vector2f position;
				sf::Vector2f size;
				sf::Vector2f range;
				int steps;
				bool textureRepeat;
				bool partBool;

				text >> textureName;
				text >> position >> size >> range >> steps >> textureRepeat >> partBool;
				textureName = "../res/Textures/Spike/" + textureName;

				if (partBool) {
					sf::IntRect part;
					text >> part;
					movableObjects.push_back(std::make_unique <MoveablePlatform>(textureName, position, size, part, i, range, steps, textureRepeat));
				} else {
					movableObjects.push_back(std::make_unique <MoveablePlatform>(textureName, position, size, i, range, steps, textureRepeat));
				}
			} else if (name == "CHARACTERS") {
				std::cerr << "END OBJECTS FOUND\n";
				readCharacters(text, amountOfScreens, movableObjects);
				break;
			} else {
				text.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		}
	}
}

void Factory::readCharacters(std::ifstream& text, int amountOfScreens, std::vector<std::unique_ptr<EntityBase>> & movableObjects) {
	std::string name;
	for (int i = 1; i <= amountOfScreens; i++) {
		text >> name;
		if (name == "player") {
			sf::Vector2f position;
			sf::Vector2f size;
			sf::Vector2f maxVelocity;
			sf::Vector2f acceleration;

			text >> position >> size >> maxVelocity >> acceleration;

			movableObjects.push_back(std::make_unique<Character>(position, size, i, maxVelocity, acceleration));
			//std::cout << "character constructor: " << position << ", " << size << ", " << i << ", " << maxVelocity << ", " << acceleration << "\n";
		}
	}
	std::cerr << "END CHARACTERS FOUND\n";
}