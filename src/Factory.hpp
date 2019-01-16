#pragma once
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

struct FactoryData {
	SettingsData Settings;
	std::vector<std::unique_ptr<EntityBase>> staticObjects;
	std::vector<std::unique_ptr<EntityBase>> movableObjects;
};


class Factory {
private:

public:
	Factory(){}

	SettingsData readSettings(std::ifstream& text);//soundtrack, gametime, number of screens

};