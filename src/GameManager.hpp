#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include <memory>
#include <vector>
#include <iostream>
#include "ViewManager.hpp"
#include "Entity/Collision.hpp"
#include "Entity/EntityBase.hpp"

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
	
	std::vector<std::unique_ptr<EntityBase>>  mStaticItems = {};
	std::vector<std::unique_ptr<EntityBase>> mDynamicItems = {};

	std::vector<std::string> mLevelFileNames;
	std::string mPath = "../res/levels/";

	void readLevelInfo();
	void applyLevelSettings();

public:
	GameManager(const std::string& levelFileName);
	
	virtual ~GameManager();
	void runGame();

};

#endif /*GAME_MANAGER_HPP*/