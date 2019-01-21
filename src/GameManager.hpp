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
#include "Factory.hpp"

class GameManager {
private:
	int mCurrentLevel;
	bool playingLevel = false;
	sf::RenderWindow mMainWindow;
	ViewManager mViewManager;
	Factory mFactory;

	Collision mCollisionManager;

	SettingsData mCurrentSettings;

	sf::Clock mUpdateClock;
	sf::Time mPassedTime;
	const sf::Time mFrameTime = sf::milliseconds(10);
	
	std::vector<std::unique_ptr<EntityBase>>  mStaticItems = {};
	std::vector<std::unique_ptr<EntityBase>> mDynamicItems = {};

	std::vector<std::unique_ptr<EntityBase>> mBackgrounds = {};

	std::vector<std::string> mLevelFileNames;

	std::string mPathLevels = "../res/levels/";
	std::string mPathBackgrounds = "../res/Textures/Background/";

	std::vector<int> mPlayerIndexes = {};

	std::array<bool, 4> mSelectedScreen = { false,false,false,false };

	bool readLevelFileNames(const std::string & levelFileName);

	void readLevelInfo();
	void applyLevelSettings();

	void createBackgrounds();
	
	void moveScreens();
	void findPlayerIndexes();
	void selectScreen(int screenNumber);

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