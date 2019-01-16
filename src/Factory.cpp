#include "Factory.hpp"
#include <iostream>
#include <typeinfo>


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