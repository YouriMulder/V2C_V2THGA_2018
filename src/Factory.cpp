#include "Factory.hpp"
#include <iostream>
#include <typeinfo>

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

/*
std::ifstream & operator>>(std::ifstream & input, sf::IntRect & rhs) {
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
			rhs.left *= 10;
			rhs.left += (int)s[index] - '0';
		}
		else if (s[index] >= '0' && s[index] <= '9' && x_fetched == true) {
			rhs.top *= 10;
			rhs.top += (int)s[index] - '0';
		}
		else if (s[index] >= '0' && s[index] <= '9' && x_fetched == true) {
			rhs.width *= 10;
			rhs.width += (int)s[index] - '0';
		}
		else if (s[index] >= '0' && s[index] <= '9' && x_fetched == true) {
			rhs.height *= 10;
			rhs.height += (int)s[index] - '0';
		}
		else if (s[index] == ')') {
			return input;
		}
		else {
			input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			throw incorrect_coordinate(s);
		
	}
	return input;
}
*/

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
		std::cout << rhs.left << "\n";
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
	text.close();
	return temp;
}

std::vector<std::vector<int>> Factory::readObjects(std::ifstream& text) {
	std::string name;
	//std::vector<std::unique_ptr<EntityBase>> staticObjects;
	//std::vector<std::unique_ptr<EntityBase>> movableObjects;
	std::cout << "begin function \n";
	text >> name;
	while (name != "SCREEN1:") {
		text >> name;
		//std::cout << name << "\n";
	}

	//std::cout << "SCREEN1 \n";
	while (name != "SCREEN2:") {
		text >> name;
		std::cout << name << "\n";
		if (name == "platform") {
			std::string textureName;
			sf::Vector2f position;
			sf::Vector2f size;
			bool textureRepeat;

			text >> textureName;
			text >> position;
			text >> size;
			text >> textureRepeat;

			//staticObjects.push_back(std::make_unique <Platform>(textureName, position, size, 1, textureRepeat));
			std::cout << "platform" << " " << textureName << " " << position << " " << size << " " << "1" << " " << textureRepeat << "\n";

		}

		else if (name == "partPlatform") {
			std::string textureName;
			sf::Vector2f position;
			sf::Vector2f size;
			bool textureRepeat;

			text >> textureName;
			text >> position;
			text >> size;
			text >> textureRepeat;
			//std::cout << "above yes \n";
			sf::IntRect part;
			text >> part;
			//staticObjects.push_back(std::make_unique <Platform>(textureName, position, size, part, 1, textureRepeat));
			std::cout << "partplatform" << textureName << " " << position << " " << size << " " << part << " " << "1" << " " << textureRepeat << "\n";

		}

		else if (name == "movePlatform") {
			std::string textureName;
			sf::Vector2f position;
			sf::Vector2f size;
			bool textureRepeat;

			text >> textureName;
			text >> position >> size >> textureRepeat;
			text >> name;

			if (name == "yes") {
				sf::IntRect part;
				text >> part;
				//movableObjects.push_back(std::make_unique <movePlatform>(textureName, position, size, part, 1, textureRepeat));
				std::cout << "movepartplatform" << textureName << " " << position << " " << size << " " << part << " " << "1" << " " << textureRepeat << "\n";
			}
			else {
				//movableObjects.push_back(std::make_unique <movePlatform>(textureName, position, size, 1, textureRepeat));
				std::cout << "moveplatform" << textureName << " " << position << " " << size << " " << "1" << " " << textureRepeat << "\n";
			}
		}
		//break;

	}
	text.close();
	return { {0,0},{0,0} };
}