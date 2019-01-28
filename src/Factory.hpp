#ifndef FACTORY_HPP 
#define FACTORY_HPP
#include "Entity/EntityBase.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include <memory>
#include <array>
#include <functional>

/// \brief
/// This struct contains all of the settings for a level.
struct SettingsData {
	/// \brief
	/// This int contains the number of screens of a level.
	int noOfScreens = 0;

	/// \brief
	/// This int contains the amount of time the player has for a level.
	int gameDuration = 0;

	int energy = 0;

	/// \brief
	/// This string contains the songname for the level.
	std::string songName;

	/// \brief
	/// This array holds the coordinates for each screen of a level.
	std::array<sf::Vector2f, 4> finishPoints;

	/// \brief
	/// This array holds the levelSize for each screen of a level.
	std::array<sf::Vector2f, 4> totalLevelSize;

	/// \brief
	/// This vector holds the background images for a level.
	std::vector<std::string> backgroundImages;
};

class Factory {
private:
	/// \brief
	/// This array holds the finish points for all screens of every level.
	std::array<sf::Vector2f, 4> mFinishPoints;
	/// \brief
	/// This string holds the path to the Platform textures.
	std::string mPathPlatform = "../res/Textures/Platform/";
	/// \brief
	/// This string holds the path to the Spike textures.
	std::string mPathSpike = "../res/Textures/Spike/";
	/// \brief
	/// This string holds the path to the Finish textures.
	std::string mPathFinish = "../res/Textures/Finish/";

	std::string mPathDrugs = "../res/Textures/Drugs/";
	std::string mPathTutorial = "../res/Textures/Tutorial/";
	/// \brief
	/// Method to read the characters from the input file.
	/// \details
	/// This method is used in the readObjects method. It is called when "CHARACTERS" is found in the input file;
	/// \param text
	/// This is a opened text file.
	/// \param amountOfScreens
	/// This is the amount of screens that have been specified in the level file.
	/// \param movableOjects
	/// This vector holds all the movable objects of the level.
	void readCharacters(std::ifstream& text, int amountOfScreens, std::vector<std::unique_ptr<EntityBase>> & movableObjects);
	/// \brief
	/// Method to create finish point.
	/// \details
	/// Uses the contents of mFinishPoints to create finishPoint objects and puts them in the given vector.
	/// \param staticObjects
	/// A vector used to hold the static objects for the level.
	void createFinishes(std::vector<std::unique_ptr<EntityBase>> & staticObjects);
	/// \brief
	/// Method used for reading all the game objects from a level file.
	/// \details
	/// This function goes through a text file line by line, and constructs game objects from it.
	/// \param text
	/// An opened text file, it contains all the game objects.
	/// \param amountOfScreens
	/// This is the amount of screens that have been specified in the level file.
	/// \param staticObjects
	/// A vector that gets filled with the static game objects from the levvel file.
	/// \param movableObjects
	/// A vector that gets filled with the movable game objects from the levvel file.
	void readObjects(std::ifstream& text, int amountOfScreens, std::vector<std::unique_ptr<EntityBase>> & staticObjects, std::vector<std::unique_ptr<EntityBase>> & movableObjects);
	/// \brief
	/// A method that reads the settings for the level.
	/// \param text
	/// An opened text file, it contains all the game objects.
	SettingsData readSettings(std::ifstream& text);

	/// \brief
	/// Method used to get the number of lines from a text file;
	/// \param filename
	/// A string that contains the name of the file or the path to the file.
	/// \return Returns the number of lines.
	int getNoLines(std::string fileName);

	/// \brief
	/// An int used to store the amount of screens from a level file.
	int mAmountOfScreens = 0;

	/// \brief
	/// An int used to store the number of lines of a text file.
	int mNoOfLines = 0;

	std::function<void()> checkDrugName(const std::string & eventName);


public:
	/// \brief
	/// Constructor for Factory class.
	Factory(){}

	/// \brief 
	/// Method for the user to interact with the factory.
	/// \details
	/// This method uses all the other reading methods to give all the data from a level file in one go.
	/// It also handles the opening and closing of the file.
	/// \param filename
	/// A string that contains the name of the file or the path to the file.
	/// \param staticObjects
	/// A vector that gets filled with the static game objects from the levvel file.
	/// \param movableObjects
	/// A vector that gets filled with the movable game objects from the levvel file.
	/// \returns
	/// This method returns a SettingData struct and also filles both of the given vectors.
	SettingsData readLevelFile(std::string fileName, std::vector<std::unique_ptr<EntityBase>> & staticObjects,
		std::vector<std::unique_ptr<EntityBase>> & movableObjects);
};

#endif /*FACTORY_HPP*/