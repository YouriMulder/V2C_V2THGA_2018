#include "Factory.hpp"
#include "Entity/Platform.hpp"
#include "Entity/Character.hpp"
#include "Entity/MoveablePlatform.hpp"
#include "Entity/EntityBase.hpp"
#include <iostream>
#include <typeinfo>
#include <memory>

std::ifstream & operator>>(std::ifstream & input, sf::Vector2f & rhs) {
	std::string s;
	input >> s;
	bool x_fetched = false;
	for (unsigned int index = 0; index < s.length(); index++) {
		if (s[index] == '(') {
			x_fetched = false;
		}
		else if (s[index] == ',') {
			x_fetched = true;
		}
		else if ((s[index] >= '0' && s[index] <= '9') && x_fetched == false) {
			rhs.x *= 10;
			rhs.x += (int)s[index] - '0';
		}
		else if (s[index] >= '0' && s[index] <= '9' && x_fetched == true) {
			rhs.y *= 10;
			rhs.y += (int)s[index] - '0';
		}
		else if (s[index] == ')') {
			return input;
		}
		/*else {
			input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			throw incorrect_coordinate(s);
		*/
	}
	return input;
}

std::ifstream & operator>>(std::ifstream & input, sf::IntRect & rhs) {
	char c;
	if (!(input >> c)) { /*throw endOfFile(_FILE, __LINE_);*/ }
	if (c != '(') { /*throw invalidPosition(c, _FILE, __LINE_);*/ }

	if (!(input >> rhs.left)) { /*throw invalidPosition(c, _FILE, __LINE_);*/ }
	if (!(input >> c)) { /*throw invalidPosition(c, _FILE, __LINE_); */}
	if (!(input >> rhs.top)) { /*throw invalidPosition(c, _FILE, __LINE_); */}
	if (!(input >> c)) { /*throw invalidPosition(c, _FILE, __LINE_); */}
	if (!(input >> rhs.width)) { /*throw invalidPosition(c, _FILE, __LINE_); */}
	if (!(input >> c)) { /*throw invalidPosition(c, _FILE, __LINE_); */}
	if (!(input >> rhs.height)) { /*throw invalidPosition(c, _FILE, __LINE_); */}


	if (!(input >> c)) { /*throw invalidPosition(c, _FILE, __LINE_); */}
	if (c != ')') { /*throw invalidPosition(c, _FILE, __LINE_); */}
	return input;
}

std::ostream &operator<<(std::ostream & lhs, const sf::Vector2f & rhs) {
	return lhs << "(" << rhs.x << "," << rhs.y << ") ";
}

std::ostream &operator<<(std::ostream & lhs, const sf::IntRect & rhs) {
	return lhs << "(" << rhs.left << "," << rhs.top << "," << rhs.width << "," << rhs.height << ") ";
}

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
					//staticObjects.push_back(std::make_unique<Spike>(textureName, position, size, part, i, damage, textureRepeat));
				}
				else {
					//staticObjects.push_back(std::make_unique<Spike>(textureName, position, size, i, damage, textureRepeat));
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
				textureName = "../res/Textures/Platform/" + textureName;

				if (partBool) {
					sf::IntRect part;
					text >> part;
					movableObjects.push_back(std::make_unique <MoveablePlatform>(textureName, position, size, part, i, range, steps, textureRepeat));
				} else {
					movableObjects.push_back(std::make_unique <MoveablePlatform>(textureName, position, size, i, range, steps, textureRepeat));
				}
			} else if (name == "CHARACTERS") {
				std::cout << " END OBJECTS FOUND\n";
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
			std::cout << "character constructor: " << position << ", " << size << ", " << i << ", " << maxVelocity << ", " << acceleration << "\n";
		}
	}
	std::cout << "END CHARACTERS FOUND\n";
}