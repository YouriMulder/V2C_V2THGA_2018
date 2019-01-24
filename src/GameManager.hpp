#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include <memory>
#include <vector>
#include <array>
#include <iostream>
#include <SFML/Graphics.hpp>
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
	int mCurrentLevel;
	int mCurrentDeathCount = 0;
	bool mPlayingLevel = false;
	bool mPlayerRespawn = false;
	sf::RenderWindow mMainWindow;
	ViewManager mViewManager;
	Factory mFactory;
	HUD mHUD;
	Collision mCollisionManager;

	SettingsData mCurrentSettings;

	sf::Clock mUpdateClock;
	sf::Time mPassedTime;
	const sf::Time mFrameTime = sf::milliseconds(10);
	
	std::vector<std::unique_ptr<EntityBase>>  mStaticItems = {};
	std::vector<std::unique_ptr<EntityBase>>  mDynamicItems = {};

	std::vector<std::unique_ptr<EntityBase>> mBackgrounds  = {};
	std::vector<std::unique_ptr<EntityBase>> mFinishTexts = {};
	std::vector<std::string> mLevelFileNames;

	std::string mPathLevels = "../res/levels/";
	std::string mPathBackgrounds = "../res/Textures/Background/";
	std::string mPathFinish = "../res/Textures/Finish/";
	std::string mPathOverlay = "../res/Textures/Overlay/";

	std::vector<int> mPlayerIndexes = {};

	std::array<bool, 4> mSelectedScreen = { false,false,false,false };
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



	EventManager actions[4] = {
	EventManager(sf::Keyboard::Num1, 	[&] {selectScreen(1); }),
	EventManager(sf::Keyboard::Num2, 	[&] {selectScreen(2); }),
	EventManager(sf::Keyboard::Num3, 	[&] {selectScreen(3); }),
	EventManager(sf::Keyboard::Num4, 	[&] {selectScreen(4); })
	};

public:
	GameManager(const std::string& levelFileName);
	
	virtual ~GameManager();
	void runGame();

};

#endif /*GAME_MANAGER_HPP*/