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
	std::ifstream currentLevelFile(mPathLevels + mLevelFileNames[mCurrentLevel]);
	mCurrentSettings = mFactory.readSettings(currentLevelFile);
	currentLevelFile.close();
	currentLevelFile.open(mPathLevels + mLevelFileNames[mCurrentLevel]);
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
	findPlayerIndexes();
	createBackgrounds();
}


void GameManager::createBackgrounds() {
	mBackgrounds.push_back(std::make_unique<Background>(mPathBackgrounds+"plx-1.png",
		sf::Vector2f(0, 0),sf::Vector2f(384,216), mViewManager.getViewSize(1), 1));
	mBackgrounds.push_back(std::make_unique<Background>(mPathBackgrounds + "plx-2.png",
		sf::Vector2f(0, 0) , sf::Vector2f(384, 216), mViewManager.getViewSize(1), 1));
	mBackgrounds.push_back(std::make_unique<Background>(mPathBackgrounds + "plx-3.png",
		sf::Vector2f(0, 0), sf::Vector2f(384, 216), mViewManager.getViewSize(1), 1));
	mBackgrounds.push_back(std::make_unique<Background>(mPathBackgrounds + "plx-4.png",
		sf::Vector2f(0, 0), sf::Vector2f(384, 216), mViewManager.getViewSize(1), 1));
	mBackgrounds.push_back(std::make_unique<Background>(mPathBackgrounds + "plx-5.png",
		sf::Vector2f(0, 0), sf::Vector2f(384, 216), mViewManager.getViewSize(1), 1));
}

void GameManager::moveScreens() {

	for (const auto & currentPlayer : mPlayerIndexes) {
		sf::Vector2f currentPlayerPosition = mDynamicItems[currentPlayer]->getPosition();
		int currentScreenNo = mDynamicItems[currentPlayer]->getScreenNumber();
		sf::Vector2f relativeScreenPosition(mViewManager.getViewPosition(currentScreenNo).x + mViewManager.getViewSize(currentScreenNo).x / 2,
			mViewManager.getViewPosition(currentScreenNo).y + mViewManager.getViewSize(currentScreenNo).y / 2);
		mViewManager.selectMoveScreen(currentScreenNo);
		if (currentPlayerPosition.x > relativeScreenPosition.x) {
			sf::Vector2f offset(currentPlayerPosition.x - relativeScreenPosition.x, 0);
			mViewManager.move(offset);
			for (auto & background : mBackgrounds) {
				if (background->getScreenNumber() == currentScreenNo) {
					background->move(offset);
				}
			}

		} else if (currentPlayerPosition.x < relativeScreenPosition.x && mViewManager.getViewPosition(currentScreenNo).x != 0) {
			sf::Vector2f offset((currentPlayerPosition.x - relativeScreenPosition.x), 0);
			mViewManager.move(offset);
			for (auto & background : mBackgrounds) {
				if (background->getScreenNumber() == currentScreenNo) {
					background->move(offset);
				}
			}
		}
		mViewManager.selectMoveScreen(currentScreenNo);
	}
}

void GameManager::findPlayerIndexes() {
	for (unsigned int i = 0; i < mDynamicItems.size();i++) {
		if (dynamic_cast<Character*>(mDynamicItems[i].get())) {
			mPlayerIndexes.push_back(i);
			std::cout << i;
		}
	}
}

void GameManager::selectScreen(int screenNumber) {
	mSelectedScreen[screenNumber - 1] = !mSelectedScreen[screenNumber - 1];
}

void GameManager::runGame() {	
	while (mViewManager.isOpen()) {

		for (auto & action : actions) {
			action();
		}

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


		mPassedTime += mUpdateClock.restart();
		int numUpdates = 0;
	
		while(mPassedTime >= mFrameTime) {
			if (numUpdates++ < 10) {
				mCollisionManager.checkCollisions();
				for(auto& dynamicObject : mDynamicItems) {
					if (mSelectedScreen[dynamicObject->getScreenNumber() - 1]) {
						dynamicObject->update(mPassedTime);
					}
				}
				moveScreens();
				for (auto & background : mBackgrounds) {
					background->update(mPassedTime);
				}
			}
			mPassedTime -= mFrameTime;
    	}


		mViewManager.clear();
	
		for (auto& background : mBackgrounds) {
			background->draw(mViewManager);
		}

		for(auto& staticObject : mStaticItems) {
			staticObject->draw(mViewManager);
		}

		for(auto& dynamicObject : mDynamicItems) {
			dynamicObject->draw(mViewManager);
		}			
		mViewManager.display();
	}
}
