#ifndef FACTORY_HPP 
#define FACTORY_HPP
#include "Entity/EntityBase.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include <memory>
#include <array>

struct SettingsData {
	int noOfScreens;
	int gameDuration;
	std::string songName;
	std::array<sf::Vector2f, 4> finishPoints;
	std::array<sf::Vector2f, 4> totalLevelSize;
	std::vector<std::string> backgroundImages;
};

class Factory {
private:
	std::string mPathPlatform = "../res/Textures/Platform/";
	std::string mPathSpike = "../res/Textures/Spike/";
	void readCharacters(std::ifstream& text, int amountOfScreens, std::vector<std::unique_ptr<EntityBase>> & movableObjects);
public:
	Factory(){}

	SettingsData readSettings(std::ifstream& text);//soundtrack, gametime, number of screens
	void readObjects(std::ifstream& text, int amountOfScreens, std::vector<std::unique_ptr<EntityBase>> & staticObjects, std::vector<std::unique_ptr<EntityBase>> & movableObjects);
};

#endif /*FACTORY_HPP*/