#ifndef FACTORY_HPP 
#define FACTORY_HPP
#include "Entity/EntityBase.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include <memory>


struct SettingsData {
	int noOfScreens;
	int gameDuration;
	std::string songName;
};

struct ObjectData {
	std::vector<std::unique_ptr<EntityBase>> & staticObjects;
	std::vector<std::unique_ptr<EntityBase>> & movableObjects;
};

struct FactoryData {
	SettingsData settings;
	ObjectData objects;
};

class Factory {
private:

public:
	Factory(){}

	SettingsData readSettings(std::ifstream& text);//soundtrack, gametime, number of screens
	void readObjects(std::ifstream& text, int amountOfScreens, std::vector<std::unique_ptr<EntityBase>> & staticObjects, std::vector<std::unique_ptr<EntityBase>> & movableObjects);
};

#endif /*FACTORY_HPP*/