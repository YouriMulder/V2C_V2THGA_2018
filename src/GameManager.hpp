#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include <memory>
#include <vector>
#include <array>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "EventManager.hpp"
#include "ViewManager.hpp"
#include "Entity/Collision.hpp"
#include "Entity/EntityBase.hpp"
#include "Entity/Background.hpp"
#include "Entity/Player.hpp"
#include "Entity/Text.hpp"
#include "Factory.hpp"
#include "HUD.hpp"
#include "SoundPlayer.hpp"

/// \brief
/// Main game class that manages every aspect of the game.
class GameManager {
private:
	/// \brief
	/// The current Level that is playing.
	int mCurrentLevel;

	/// \brief
	/// The current amount of deaths.
	int mCurrentDeathCount = 0;

	/// \brief
	/// How many of the screens are finished already.
	int mCurrentScreensNotFinished;

	/// \brief
	/// Is there currently a level playing. 
	bool mPlayingLevel = false;

	/// \brief
	/// Is the player currently respawning.
	bool mPlayerRespawn = false;

	/// \brief
	/// The main RenderWindow for the game.
	sf::RenderWindow mMainWindow;

	/// \brief
	/// The ViewManager needed to draw to mulitple screens see ViewManager doucmentation for more info.
	ViewManager mViewManager;

	/// \brief
	/// The factory needed to read all the level information.
	Factory mFactory;

	/// \brief
	/// The HUD that displays the healt/energy and death.
	HUD mHUD;

	SoundPlayer mSoundPlayer;

	Collision mCollisionManager;

	/// \brief 
	/// The struct that contains the settings for the current level.
	SettingsData mCurrentSettings;

	/// \brief
	/// The game music.
	sf::Music mMusic;

	/// \brief
	/// Clock used for deltaTime.
	sf::Clock mUpdateClock;

	/// \brief
	/// Time Passed between updates.
	sf::Time mPassedTime;

	/// \brief
	/// Time between each frame.
	const sf::Time mFrameTime = sf::milliseconds(10);
	
	/// \brief
	/// Vector with all the static game objects such as platforms.
	std::vector<std::unique_ptr<EntityBase>>  mStaticItems = {};

	/// \brief
	/// Vector with all the static game objects such as movable platforms and players.
	std::vector<std::unique_ptr<EntityBase>>  mDynamicItems = {};

	/// \brief
	/// Vector with all the backgrounds.
	std::vector<std::unique_ptr<EntityBase>> mBackgrounds  = {};

	/// \brief
	/// Vector with all the Finish texts.
	std::vector<std::unique_ptr<EntityBase>> mFinishTexts = {};

	/// \brief
	/// Vector with all the names of the level files.
	std::vector<std::string> mLevelFileNames;

	/// \brief
	/// Path to all the level files.
	std::string mPathLevels = "../res/levels/";

	/// \brief
	/// Path to all the backgrounds.
	std::string mPathBackgrounds = "../res/Textures/Background/";

	/// \brief
	/// Path to all the Finish sprites.
	std::string mPathFinish = "../res/Textures/Finish/";

	/// \brief
	/// Path to all the overlay sprites.
	std::string mPathOverlay = "../res/Textures/Overlay/";

	/// \brief
	/// Path to all the music files.
	std::string mPathMusic = "../res/Sounds/Music/";

	/// \brief
	/// Vector with the indexes of the players in the mDynamicItems.
	std::vector<int> mPlayerIndexes = {};

	/// \brief
	/// Array to see which screens are selected.
	std::array<bool, 4> mSelectedScreen = { false,false,false,false };

	// \brief
	/// Array to see which screens are finished.
	std::array<bool, 4> mFinishedScreen = { false,false,false,false };

	/// \brief
	/// Delete a object from dynamicItems
	/// \details
	/// \param index
	/// The index at which the object needs to be deleted
	void dynamicItemsErase(unsigned int index);
	
	/// \brief
	/// Function to read all the levelfile names form a all file.
	/// \details
	/// \param levelFileName 
	/// The file Name of the all file.
	/// \return
	/// Returns false when error has occured.
	bool readLevelFileNames(const std::string & levelFileName);

	/// \brief
	/// Function to read all the level information using the factory.
	void readLevelInfo();

	/// \brief
	/// Function to apply all the settings.
	/// \details
	/// Applies settings such as amount of screens and resets the Health.
	void applyLevelSettings();

	/// \brief
	/// Function to create a level.
	/// \details
	/// Uses other functions such as clearLevel and readLevelInfo.
	void createLevel();

	/// \brief
	/// Function to create all the backgrounds.
	void createBackgrounds();
	
	/// \brief
	/// Function to move the screens according to player position.
	void moveScreens();

	/// \brief
	/// Function to search where the players are in the mDynamic items.
	void findPlayerIndexes();

	/// \brief
	/// Function to select a screen.
	/// \details
	/// \param screenNumber
	/// The screen you want to select.
	void selectScreen(int screenNumber);

	/// \brief
	/// Function to clear all the level information.
	/// \details
	/// Clears all the level information.
	void clearLevel();

	/// \brief
	/// Funcion te check if a player falls beyond the maximum size of a level.
	/// \details
	/// \return returs true if player is out of bounds.
	bool checkPlayerOutView();

	/// \brief
	/// Function to check if the level is Finished.
	/// \details
	/// Checks if all the finishpoints are reached.
	/// \return Returns true if level is finished.
	bool checkLevelFinished();

	/// \brief
	/// Function to check if the player is death.
	/// \details
	/// \return Returns true if player lost.
	bool checkLosingConditions();

	/// \brief
	/// Function te check if player selecter 2 or more screens.
	/// \details
	/// This function checks if 2 screens or more are selected.\n
	/// If there is only one or 2 screen(s) both are selected.
	/// \return Returns true if contions are met.
	bool check2Selected();


	/// \brief
	/// Function to go to the next level
	void gotoNextLevel();

	/// \brief
	/// Function to go to the previous level
	void gotoPreviousLevel();

	/// \brief
	/// Function to respawn (restart a level while keeping death count)
	void respawn();

	/// \brief
	/// Array of actions.
	/// \details
	/// This array contains all the key bindings nessecary.\n
	/// Numbers 1-4 for selecting screens 1-4.\n
	/// Escape for closing the game.\n
	/// nuped6/4 to change level.\n
	/// backspace to respawn.\n
	EventManager actions[8] = {
		EventManager(sf::Keyboard::Num1, 	[&]() {selectScreen(1); }, sf::Event::KeyReleased),
		EventManager(sf::Keyboard::Num2, 	[&]() {selectScreen(2); }, sf::Event::KeyReleased),
		EventManager(sf::Keyboard::Num3, 	[&]() {selectScreen(3); }, sf::Event::KeyReleased),
		EventManager(sf::Keyboard::Num4, 	[&]() {selectScreen(4); }, sf::Event::KeyReleased),
		EventManager(sf::Keyboard::Numpad6, [&]() {gotoNextLevel(); }, sf::Event::KeyReleased),
		EventManager(sf::Keyboard::Numpad4, [&]() {gotoPreviousLevel();},sf::Event::KeyReleased),
		EventManager(sf::Keyboard::BackSpace, [&]() {respawn();},sf::Event::KeyReleased),
		EventManager(sf::Keyboard::Escape, 	[&]() {mViewManager.close(); })
	};

public:
	/// \brief
	/// Constructor for GameManager class.
	/// \details
	/// This constructor constructs a GameManager using the given txt file.
	/// \param levelFileName
	/// This parameter contains the file name of the all text file.
	GameManager(const std::string& levelFileName);
	
	virtual ~GameManager();

	/// \brief
	/// Function to start the game.
	void runGame();

};

#endif /*GAME_MANAGER_HPP*/
