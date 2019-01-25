#include "GameManager.hpp"
#include "Entity/Player.hpp"
#include "Entity/Projectile.hpp"
#include <fstream>
#include <exception>

GameManager::GameManager(const std::string& levelFileName) :
	mCurrentLevel(0),
	mMainWindow(sf::VideoMode(1920, 1080), "MiNdF*cK",sf::Style::Fullscreen),
	mViewManager(mMainWindow, 1),
	mFactory(),
	mHUD(),
	mCollisionManager(mViewManager,mStaticItems, mDynamicItems)
{
	if (!readLevelFileNames(levelFileName)) {
		std::cerr << "levelFileNames not read" << std::endl ;
	}
}


GameManager::~GameManager() {}

bool GameManager::readLevelFileNames(const std::string & levelFileName) {
	std::ifstream input(levelFileName);
	std::string newFileName;
	if (!input) {
		return false;
	} else {
		input >> newFileName;
		while (newFileName != "END") {
			if (newFileName != "\n") {
				mLevelFileNames.push_back(newFileName);
			}
			input >> newFileName;
		}
	}
	input.close();
	return true;
}

void GameManager::createLevel(){
	clearLevel();
	readLevelInfo();
	applyLevelSettings();
	findPlayerIndexes();
	createBackgrounds();
}

void GameManager::readLevelInfo() {
	if (static_cast<unsigned int>(mCurrentLevel) >= mLevelFileNames.size()) {
		std::cerr << "no file names";
	} else {
		mCurrentSettings = mFactory.readLevelFile(mPathLevels + mLevelFileNames[mCurrentLevel], mStaticItems, mDynamicItems);
	}
	
}

void GameManager::applyLevelSettings() {
	mViewManager.changeAmountOfScreens(mCurrentSettings.noOfScreens);
	if (mViewManager.getAmountOfScreens() == 1) {
		mSelectedScreen[0] = true;
	} else if (mViewManager.getAmountOfScreens() == 2) {
		mSelectedScreen[0] = true;
		mSelectedScreen[1] = true;
	}
	mCurrentScreensNotFinished = mCurrentSettings.noOfScreens;
	Player::resetHealth();
	if (!mMusic.openFromFile(mPathMusic + mCurrentSettings.songName)) {
		std::cerr << "failed loading music";
	}
}

void GameManager::createBackgrounds() {
	for (const auto & textureName : mCurrentSettings.backgroundImages) {
		for (int i = 1; i <= mCurrentSettings.noOfScreens;i++) {
			mBackgrounds.push_back(std::make_unique<Background>(
				mPathBackgrounds + textureName,
				sf::Vector2f(0, 0),
				sf::Vector2f(384,216),
				mViewManager.getViewSize(i),
				i
			));
		}
	}
}

void GameManager::moveScreens() {

	for (const auto & currentPlayer : mPlayerIndexes) {
		sf::Vector2f currentPlayerPosition = mDynamicItems[currentPlayer]->getPosition();
		sf::Vector2f currentPlayerSize = mDynamicItems[currentPlayer]->getSize();
		currentPlayerPosition.x = currentPlayerPosition.x + currentPlayerSize.x / 2;
		currentPlayerPosition.y = currentPlayerPosition.y + currentPlayerSize.y / 2;
		int currentScreenNo = mDynamicItems[currentPlayer]->getScreenNumber();
		sf::Vector2f relativeScreenPosition(mViewManager.getViewPosition(currentScreenNo).x + mViewManager.getViewSize(currentScreenNo).x / 2,
			mViewManager.getViewPosition(currentScreenNo).y + mViewManager.getViewSize(currentScreenNo).y / 2);
		mViewManager.selectMoveScreen(currentScreenNo);
		//move x
		if (!mFinishedScreen[currentScreenNo - 1]) {
			if (currentPlayerPosition.x > relativeScreenPosition.x && !(mViewManager.getViewPosition(currentScreenNo).x + mViewManager.getViewSize(currentScreenNo).x >= mCurrentSettings.totalLevelSize[currentScreenNo - 1].x)) {
				sf::Vector2f offset(currentPlayerPosition.x - relativeScreenPosition.x, 0);
				mViewManager.move(offset);
				for (auto & background : mBackgrounds) {
					if (background->getScreenNumber() == currentScreenNo) {
						background->move(offset);
					}
				}

			} else if (currentPlayerPosition.x < relativeScreenPosition.x && !(mViewManager.getViewPosition(currentScreenNo).x <= 0)) {
				sf::Vector2f offset((currentPlayerPosition.x - relativeScreenPosition.x), 0);
				mViewManager.move(offset);
				for (auto & background : mBackgrounds) {
					if (background->getScreenNumber() == currentScreenNo) {
						background->move(offset);
					}
				}
			}
			//move y
			if (currentPlayerPosition.y > relativeScreenPosition.y && !(mViewManager.getViewPosition(currentScreenNo).y + mViewManager.getViewSize(currentScreenNo).y >= mCurrentSettings.totalLevelSize[currentScreenNo - 1].y)) {
				sf::Vector2f offset(0, (currentPlayerPosition.y - relativeScreenPosition.y) / 25);
				mViewManager.move(offset);
				for (auto & background : mBackgrounds) {
					if (background->getScreenNumber() == currentScreenNo) {
						background->move(offset);
					}
				}
			} else if (currentPlayerPosition.y < relativeScreenPosition.y && !(mViewManager.getViewPosition(currentScreenNo).y <= 0)) {
				sf::Vector2f offset(0, (currentPlayerPosition.y - relativeScreenPosition.y) / 25);
				mViewManager.move(offset);
				for (auto & background : mBackgrounds) {
					if (background->getScreenNumber() == currentScreenNo) {
						background->move(offset);
					}
				}
			}
			
		}
		mViewManager.selectMoveScreen(currentScreenNo);
	}
}

void GameManager::clearLevel() {
	mDynamicItems.clear();
	mStaticItems.clear();
	mBackgrounds.clear();
	mFinishTexts.clear();
	for (auto & screen : mSelectedScreen) {
		screen = false;
	}
	for (auto & finish :mFinishedScreen) {
		finish = false;
	}
	mPlayerIndexes.clear();
}
bool GameManager::checkLosingConditions() {
	if (checkPlayerOutView() || Player::isDead()) {
		return true;
	}
	return false;
}

bool GameManager::checkPlayerOutView() {
	for (const auto & currentPlayer : mPlayerIndexes) {
		sf::Vector2f currentPlayerPosition = mDynamicItems[currentPlayer]->getPosition();
		int screenNumber = mDynamicItems[currentPlayer]->getScreenNumber();
		if (currentPlayerPosition.y > mCurrentSettings.totalLevelSize[screenNumber-1].y) {
			return true;
		}
	}
	return false;
}


bool GameManager::checkLevelFinished() {
	for (const auto & currentIndex : mPlayerIndexes){
		int currentScreen = mDynamicItems[currentIndex] ->getScreenNumber();
		sf::Vector2f relativeScreenPosition(mViewManager.getViewPosition(currentScreen).x + mViewManager.getViewSize(currentScreen).x / 2,
			mViewManager.getViewPosition(currentScreen).y + mViewManager.getViewSize(currentScreen).y / 2);

		if (mDynamicItems[currentIndex]->isFinished() && !mFinishedScreen[currentScreen-1]) {
			mFinishedScreen[currentScreen - 1] = true;
			mSelectedScreen[currentScreen - 1] = false;
			mFinishTexts.push_back(std::make_unique<Text>(
				relativeScreenPosition,
				sf::Vector2f(0, 0),
				currentScreen,
				"Finished good job",
				30,
				"arial.ttf"));
			auto currentTextRect = mFinishTexts[mFinishTexts.size() - 1]->getGlobalBounds();
			mFinishTexts[mFinishTexts.size() - 1]->move(sf::Vector2f(-(currentTextRect.width / 2),-( currentTextRect.height / 2)));
			mStaticItems.push_back(std::make_unique<Background>(
				mPathOverlay + "transparantGrey.png",
				mViewManager.getViewPosition(currentScreen),
				mViewManager.getViewSize(currentScreen),
				mViewManager.getViewSize(currentScreen),
				currentScreen
				));
			mCurrentScreensNotFinished--;
			mStaticItems[mStaticItems.size() - 1]->draw(mViewManager);
			for (const auto& finishText : mFinishTexts) {
				finishText->draw(mViewManager);
			}
			mViewManager.display();
		}
	}
	int finishCounter = 0;
	for (const auto & finished : mFinishedScreen) {
		if (finished) {
			finishCounter++;
		}
	}
	if (finishCounter == mCurrentSettings.noOfScreens) {
		sf::sleep(sf::milliseconds(1000));
		return true;
	}
	return false;
}

void GameManager::findPlayerIndexes() {
	for (unsigned int i = 0; i < mDynamicItems.size();i++) {
		if (dynamic_cast<Player*>(mDynamicItems[i].get())) {
			mPlayerIndexes.push_back(i);
		}
	}
}

void GameManager::selectScreen(int screenNumber) {
	if (!mFinishedScreen[screenNumber - 1]) {
		mSelectedScreen[screenNumber - 1] = !mSelectedScreen[screenNumber - 1];
	}
}

bool GameManager::check2Selected() {
	int count = 0;
	if (mCurrentScreensNotFinished <= 1) {
		return true;
	}
	for (auto & selected : mSelectedScreen) {
		if (selected) {
			count++;
		}
	}
	if (count >= 2) {
		return true;
	}
	return false;
}

void GameManager::runGame() {	
	sf::Event event;
	
	while (mViewManager.isOpen()) {
		if (!mPlayingLevel) {
			createLevel();
			if (!mMusic.openFromFile(mPathMusic + mCurrentSettings.songName)) {
				std::cerr << "faild loading music";
			}
			mMusic.play();
			mCurrentDeathCount = 0;
			mHUD.updateDeathCount(mCurrentDeathCount);
			mPlayingLevel = !mPlayingLevel;
		} else if (mPlayerRespawn) {
			mPlayerRespawn = false;
		}

		while (mViewManager.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				mViewManager.close();
			}

			for (auto & action : actions) {
				action(event);
			}
		}
		
		mPassedTime += mUpdateClock.restart();
		int numUpdates = 0;
	
		while(mPassedTime >= mFrameTime) {
			if (numUpdates++ < 10) {
				mCollisionManager.checkCollisions();
				
				for(const auto& playerIndex : mPlayerIndexes) {
					if(dynamic_cast<Player*>(mDynamicItems[playerIndex].get())) {
						auto player = dynamic_cast<Player*>(mDynamicItems[playerIndex].get());
						if(auto projectile = player->getProjectile()) {
							mDynamicItems.push_back(std::move(projectile.value()));
						}
					}
				}
				
				for(const auto& dynamicObject : mDynamicItems) {
					if (mSelectedScreen[dynamicObject->getScreenNumber() - 1] && check2Selected()) {
						dynamicObject->update(mPassedTime);
					}
				}
				moveScreens();
				for (const auto & background : mBackgrounds) {
					background->update(mPassedTime);
				}
				if (checkLosingConditions()) {
					mPlayerRespawn = true;
					createLevel();
					mCurrentDeathCount++;
					mHUD.updateDeathCount(mCurrentDeathCount);
					break;
				}
				if (checkLevelFinished()) {
					mPlayingLevel = false;
				 	mCurrentLevel++;
					EntityBase::backToStartId();
					break;
				}
				
			}
			mPassedTime -= mFrameTime;
    	}

		mHUD.updateHealth(Player::getHealth());
		mViewManager.clear();
		int count = 1;
		for (const auto & selected : mSelectedScreen) {
			if (selected) {
				mViewManager.setBordorColor(count);
			} else {
				mViewManager.resetBordorColor(count);
			}
			count++;
		}
		if (!mPlayerRespawn && mPlayingLevel) {
			for (const auto& background : mBackgrounds) {
				background->drawIfVisible(mViewManager);
			}
			for (const auto& dynamicObject : mDynamicItems) {
				dynamicObject->drawIfVisible(mViewManager);
			}

			for (const auto& staticObject : mStaticItems) {
				staticObject->drawIfVisible(mViewManager);
			}

			for (const auto& finishText : mFinishTexts) {
				finishText->drawIfVisible(mViewManager);
			}	
			mHUD.draw(mViewManager);
		}
		mViewManager.display();
	}
}
