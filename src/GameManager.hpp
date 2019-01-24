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
	/// Is the player currently respawning
	bool mPlayerRespawn = false;

	/// \brief
	/// The main RenderWindow for the game
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
	/// Vector with all the names of the level files
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

	bool readLevelFileNames(const std::string & levelFileName);

	void readLevelInfo();
	void applyLevelSettings();
	void createLevel();

	void createBackgrounds();
	
	void moveScreens();
	void findPlayerIndexes();
	void selectScreen(int screenNumber);

	void clearLevel();

	bool checkPlayerOutView();
	bool checkLevelFinished();
	bool checkLosingConditions();
	bool check2Selected();



	EventManager actions[5] = {
		EventManager(sf::Keyboard::Num1, 	[&] {selectScreen(1); }, sf::Event::KeyReleased),
		EventManager(sf::Keyboard::Num2, 	[&] {selectScreen(2); }, sf::Event::KeyReleased),
		EventManager(sf::Keyboard::Num3, 	[&] {selectScreen(3); }, sf::Event::KeyReleased),
		EventManager(sf::Keyboard::Num4, 	[&] {selectScreen(4); }, sf::Event::KeyReleased),
		EventManager(sf::Keyboard::Escape, 	[&] {mViewManager.close(); })
	};

public:
	GameManager(const std::string& levelFileName);
	
	virtual ~GameManager();
	void runGame();

};

#endif /*GAME_MANAGER_HPP*/