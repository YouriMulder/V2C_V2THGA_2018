#ifndef FACTORY_HPP 
#define FACTORY_HPP
#include "Entity/EntityBase.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include <memory>
#include <array>

struct SettingsData {
	int noOfScreens = 0;
	int gameDuration = 0;
	std::string songName;
	std::array<sf::Vector2f, 4> finishPoints;
	std::array<sf::Vector2f, 4> totalLevelSize;
	std::vector<std::string> backgroundImages;
};

class Factory {
private:
	std::array<sf::Vector2f, 4> mFinishPoints;
	std::string mPathPlatform = "../res/Textures/Platform/";
	std::string mPathSpike = "../res/Textures/Spike/";
	std::string mPathFinish = "../res/Textures/Finish/";
	void readCharacters(std::ifstream& text, int amountOfScreens, std::vector<std::unique_ptr<EntityBase>> & movableObjects);
	void createFinishes(std::vector<std::unique_ptr<EntityBase>> & staticObjects);
	void readObjects(std::ifstream& text, int amountOfScreens, std::vector<std::unique_ptr<EntityBase>> & staticObjects, std::vector<std::unique_ptr<EntityBase>> & movableObjects);
	SettingsData readSettings(std::ifstream& text);


public:
	Factory(){}
	
	SettingsData readLevelFile(std::string fileName, std::vector<std::unique_ptr<EntityBase>> & staticObjects,
		std::vector<std::unique_ptr<EntityBase>> & movableObjects);
};

#endif /*FACTORY_HPP*/