#include "Factory.hpp"
#include "Entity/Platform.hpp"
#include "Entity/Character.hpp"
#include "Entity/MoveablePlatform.hpp"
#include "Entity/Spikes.hpp"
#include "Entity/EntityBase.hpp"
#include <iostream>
#include "operator.hpp"
#include <array>
#include <sstream>
#include "Entity/Finish.hpp"

SettingsData Factory::readSettings(std::ifstream& text) {
	std::string name;
	SettingsData temp;
	std::array<sf::Vector2f, 4> finishPoint;
	std::array<sf::Vector2f, 4> totalLevelSizes;

	
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
				sf::Vector2f levelSizeTemp;
				for (int i = 0; i < temp.noOfScreens; ++i) {
					levelSizeTemp = sf::Vector2f(0, 0);
					text >> levelSizeTemp;
					temp.totalLevelSize[i] = levelSizeTemp;
				}
			}
			else if (name == "finishPoints") {
				sf::Vector2f finishPointsTemp;
				for (int i = 0; i < temp.noOfScreens; ++i) {
					finishPointsTemp = sf::Vector2f(0, 0);
					text >> finishPointsTemp;
					temp.finishPoints[i] = finishPointsTemp;
					finishPoint[i] = finishPointsTemp;
				}
			}
			else if (name == "backgroundImages") {
				std::string imagesTemp;
				text.get();
				char c = text.get();
				while (c != '\n') {
					imagesTemp += c;
					c = text.get();
				}
				std::stringstream s(imagesTemp);
				std::string token;
				while (std::getline(s, token, ',')) {
					temp.backgroundImages.push_back(token);
				}
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

	createFinishes(staticObjects);

	for (int i = 1; i < amountOfScreens + 1; i++) {
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
				textureName = mPathPlatform + textureName;

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
				textureName = mPathSpike + textureName;

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
				textureName = mPathPlatform + textureName;


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
		}
	}
	std::cerr << "END CHARACTERS FOUND\n";
}

void Factory::createFinishes(std::vector<std::unique_ptr<EntityBase>> & staticObjects) {
	for (int i = 0; i < mFinishPoints.size(); i++) {
		staticObjects.push_back(std::make_unique<Finish>(
			mPathFinish + "finish2.png",
			mFinishPoints[i],
			sf::Vector2f(65, 72),
			i + 1
			));
	}
}

SettingsData Factory::readLevelFile(std::string fileName, std::vector<std::unique_ptr<EntityBase>> & staticObjects,
	std::vector<std::unique_ptr<EntityBase>> & movableObjects) {

	std::ifstream text(fileName);
	SettingsData temp = readSettings(text);
	readObjects(text, temp.noOfScreens, staticObjects, movableObjects);
	text.close();
	return temp;

}