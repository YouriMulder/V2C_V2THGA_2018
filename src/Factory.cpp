#include "Factory.hpp"
#include "Entity/Platform.hpp"
#include "Entity/Character.hpp"
#include "Entity/Player.hpp"
#include "Entity/NPC.hpp"
#include "Entity/MoveablePlatform.hpp"
#include "Entity/Spikes.hpp"
#include "Entity/EntityBase.hpp"
#include <iostream>
#include "operator.hpp"
#include <array>
#include <sstream>
#include <functional>
#include "Entity/Finish.hpp"
#include "Entity/Text.hpp"
#include "Entity/Drugs.hpp"
#include "Entity/EventTriggeredObject.hpp"
#include <cstdint>

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
				mAmountOfScreens = data;
			} else if (name == "gameTime") {
				int data;
				text >> data;
				temp.gameDuration = data;
			} else if (name == "songName") {
				std::string data;
				text >> data;
				temp.songName = data;
			} else if (name == "levelSize") {
				sf::Vector2f levelSizeTemp;
				for (int i = 0; i < temp.noOfScreens; ++i) {
					levelSizeTemp = sf::Vector2f(0, 0);
					text >> levelSizeTemp;
					temp.totalLevelSize[i] = levelSizeTemp;
				}
			} else if (name == "finishPoints") {
				sf::Vector2f finishPointsTemp;
				for (int i = 0; i < temp.noOfScreens; ++i) {
					finishPointsTemp = sf::Vector2f(0, 0);
					text >> finishPointsTemp;
					temp.finishPoints[i] = finishPointsTemp;
					mFinishPoints[i] = finishPointsTemp;
				}
			} else if (name == "backgroundImages") {
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
			} else if (name == "energy") {
				int spawnEnergy;
				text >> spawnEnergy;
				temp.energy = spawnEnergy;
			} else if (text.eof()) {
				return temp;
			}
		}
	}
	return temp;
}

void Factory::readObjects(std::ifstream& text, int amountOfScreens, std::vector<std::unique_ptr<EntityBase>> & staticObjects,
	std::vector<std::unique_ptr<EntityBase>> & movableObjects) {
	std::string name;
	int currentNoLine = 0;

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
			}
			else if (name == "movePlatform") {
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
				}
				else {
					movableObjects.push_back(std::make_unique <MoveablePlatform>(textureName, position, size, i, range, steps, textureRepeat));
				}
			} else if (name == "textBox") {
				sf::Vector2f position;
				sf::Vector2f size;
				std::string s;
				int fontSize;
				std::string fontFile;
				char c;

				text >> position >> size;
				c = text.get();
				c = text.get();
				if (c == '\"') {
					c = text.get();
					while (c != '\"') {
						s += c;
						c = text.get();
					}
				}

				text >> fontSize >> fontFile;
				staticObjects.push_back(std::make_unique <Text>(position, size, i, s, fontSize, fontFile));
			} else if (name == "NPC") {
				sf::Vector2f startPoint;
				float deltaXMovement;
				unsigned int health;
				unsigned int damage;
				text >> startPoint >> deltaXMovement >> health >> damage;
				movableObjects.push_back(std::make_unique<NPC>(startPoint, deltaXMovement, i, health, damage));
			}else if (name == "DRUG"){
				std::string textureName;
				sf::Vector2f position;
				sf::Vector2f size;
				bool textureRepeat;
				std::string eventName;
				text >> textureName;
				text >> position >> size >> textureRepeat >> eventName;
				movableObjects.push_back(std::make_unique<EventTriggeredObject>(mPathDrugs + textureName, position, size,i, checkDrugName(eventName), true,position,size, textureRepeat));
			} else if (name == "tutorial") {
				std::string textureName;
				sf::Vector2f position;
				sf::Vector2f size;
				sf::Vector2f hitPosition;
				sf::Vector2f hitSize;
				bool textureRepeat;
				text >> textureName;
				text >> position >> size >> textureRepeat;
				text >> hitPosition >> hitSize;
				movableObjects.push_back(std::make_unique<EventTriggeredObject>(mPathTutorial + textureName, position, size, i, [&]() {}, false, hitPosition,hitSize, textureRepeat,false));
			} else if (name == "CHARACTERS") {
				//std::cerr << "END OBJECTS FOUND\n";
				readCharacters(text, amountOfScreens, movableObjects);
				break;
			} else {
				text.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			currentNoLine++;
			if (currentNoLine > mNoOfLines) {
				std::cerr << "Exceded number of lines\n";
				break;
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
			text >> position;

			movableObjects.push_back(std::make_unique<Player>(position, i));
		}
	}
	//std::cerr << "END CHARACTERS FOUND\n";
}

void Factory::createFinishes(std::vector<std::unique_ptr<EntityBase>> & staticObjects) {
	for (int i = 0; i < mAmountOfScreens; i++) {
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
	mNoOfLines = getNoLines(fileName);
	std::ifstream text(fileName);
	SettingsData temp = readSettings(text);
	readObjects(text, temp.noOfScreens, staticObjects, movableObjects);
	text.close();
	return temp;

}

int Factory::getNoLines(std::string fileName) {
	int counter = 0;
	std::ifstream text(fileName);
	std::string line;
	while (std::getline(text, line)) {
		counter++;
	}
	text.close();
	return counter;
}

std::function<void()> Factory::checkDrugName(const std::string & eventName) {
	if (eventName == "healthReset") {
		return Drugs::health;
	} else if (eventName == "energyReset") {
		return Drugs::energy;
	} else if (eventName == "resetBoth") {
		return Drugs::both;
	} else if (eventName == "energy-2") {
		return Drugs::energySub2;
	} else if (eventName == "energy+1") {
		return Drugs::energyAdd1;
	}
	return [&](){};
}