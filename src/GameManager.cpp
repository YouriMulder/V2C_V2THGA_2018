#include "GameManager.hpp"
#include <fstream>
#include "Entity/Character.hpp"


GameManager::GameManager(const std::string& levelFileName) :
	mCurrentLevel(0),
	mMainWindow(sf::VideoMode(1280, 720), "MiNdF*cK"),
	mViewManager(mMainWindow, 1),
	mFactory(),
	mCollisionManager(mViewManager,mStaticItems, mDynamicItems)
{
	if (!readLevelFileNames(levelFileName)) {
		std::cout << "levelFileNames not read" << std::endl ;
	}
}


GameManager::~GameManager()
{
}

bool GameManager::readLevelFileNames(const std::string & levelFileName) {
	std::ifstream input(levelFileName);
	std::string newFileName;
	if (!input) {
		return false;
	} else {
		input >> newFileName;
		while (newFileName != "END") {
			mLevelFileNames.push_back(newFileName);
			input >> newFileName;
		}
	}
	input.close();
	return true;
}

void GameManager::readLevelInfo() {
	std::ifstream currentLevelFile(mPath + mLevelFileNames[mCurrentLevel]);
	mCurrentSettings = mFactory.readSettings(currentLevelFile);
	currentLevelFile.close();
	currentLevelFile.open(mPath + mLevelFileNames[mCurrentLevel]);
	if (!currentLevelFile.is_open()) {
		std::cout << "error";
	} else {
		mFactory.readObjects(currentLevelFile, mCurrentSettings.noOfScreens, mStaticItems, mDynamicItems);
	}
	currentLevelFile.close();
	applyLevelSettings();
}

void GameManager::applyLevelSettings() {
	mViewManager.changeAmountOfScreens(mCurrentSettings.noOfScreens);
}

void GameManager::runGame() {
	sf::Clock updateClock; // Clock to monitor the time passed
	sf::Time passedTime; // Accumulated game time
	const sf::Time frameTime(sf::milliseconds(10));

	
	while (mViewManager.isOpen()) {
		if (!playingLevel) {
			readLevelInfo();
			playingLevel = !playingLevel;
		}

		mCollisionManager.checkCollisions();
		sf::Event event;
		while (mViewManager.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				mViewManager.close();
		}


		passedTime += updateClock.restart();
		int numUpdates = 0;
	
		while(passedTime >= frameTime) {
			if (numUpdates++ < 10) {
				mCollisionManager.checkCollisions();
				for(auto& dynamicObject : mDynamicItems) {

					dynamicObject->update(passedTime);
				}
			}
			passedTime -= frameTime;
    	}

		mViewManager.clear();
		for(auto& staticObject : mStaticItems) {
			staticObject->draw(mViewManager);
		}
		for(auto& dynamicObject : mDynamicItems) {
			dynamicObject->draw(mViewManager);
		}
			
		mViewManager.display();
	}
}
