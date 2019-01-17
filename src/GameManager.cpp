#include "GameManager.hpp"
#include <fstream>
#include "Entity/Character.hpp"


GameManager::GameManager(std::string levelFileName) :
	mCurrentLevel(0),
	mMainWindow(sf::RenderWindow(sf::VideoMode(1280, 720), "MiNdF*cK")),
	mViewManager(mMainWindow, 1),
	mFactory(Factory()),
	mCollisionManager(Collision(mViewManager,mStaticItems, mDynamicItems))
{
	std::ifstream input(levelFileName);
	std::string newFileName;
	if (!input) {
		"file not open";
	} else {
		input >> newFileName;
		while (newFileName != "END") {
			mLevelFileNames.push_back(newFileName);
			input >> newFileName;
		}
		for (unsigned int i = 0; i < mLevelFileNames.size(); i++) {
			std::cout << mLevelFileNames[i] << std::endl;
		}
	}
	input.close();
}


GameManager::~GameManager()
{
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
	

	while (mViewManager.isOpen()) {
		mViewManager.clear();
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
		for (auto & staticItem : mStaticItems) {
			staticItem->draw(mViewManager);
		}

		for (auto & dynaicItem : mDynamicItems) {
			dynaicItem->update();
			dynaicItem->draw(mViewManager);
		}
			
		mViewManager.display();
	}
}
