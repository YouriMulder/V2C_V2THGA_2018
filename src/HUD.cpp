#include "HUD.hpp"



HUD::HUD()
{
	mTexts.push_back(std::make_unique<Text> (
		sf::Vector2f(0, 0),
		sf::Vector2f(0, 0),
		0,
		"HEALTH: ",
		14,
		"arialbd.ttf"
		));
	mTexts[0]->setColor(mHealthColor);
	mTexts.push_back(std::make_unique<Text>(
		sf::Vector2f(0, 20),
		sf::Vector2f(0, 0),
		0,
		"ENERGY: ",
		14,
		"arial.ttf"
		));
	mTexts[1]->setColor(sf::Color::Cyan);
	mTexts.push_back(std::make_unique<Text>(
		sf::Vector2f(0, 40),
		sf::Vector2f(0, 0),
		0,
		mBaseDeath + std::to_string(mCurrentDeathCount),
		14,
		"arial.ttf"
		));
	mTexts[2]->setColor(sf::Color::White);
	for (int i = 0;i < mCurrentHealth;i++) {
		mHearts.push_back(std::make_unique<LevelObject>(
			mPathHUD + "heart.png",
			sf::Vector2f(textOffset + i*sizeOffset, 3),
			sf::Vector2f(sizeOffset, sizeOffset),
			0));
	}
	for (int i = 0;i < mCurrentEnergy;i++) {
		mEnergy.push_back(std::make_unique<LevelObject>(
			mPathHUD + "energy.png",
			sf::Vector2f(textOffset + i*sizeOffset, 20),
			sf::Vector2f(sizeOffset, sizeOffset),
			0));
	}

}


HUD::~HUD()
{
}


void HUD::updateEnergy(int newEnergy) {
	if (newEnergy > 10) {
		mCurrentEnergy = 10;
	} else if (newEnergy < 0) {
		mCurrentEnergy = 0;
	} else {
		mCurrentEnergy = newEnergy;
	}
}

void HUD::updateHealth(int newHealth) {
	if (newHealth > 10) {
		mCurrentHealth = 10;
	} else if (newHealth < 0) {
		mCurrentEnergy = 0;
	} else {
		mCurrentHealth = newHealth;
	}
}

void HUD::updateDeathCount(int newDeathCount) {
	mCurrentDeathCount = newDeathCount;
	mTexts[2]->setString(mBaseDeath + std::to_string(mCurrentDeathCount));
}

void HUD::draw(ViewManager & window) {
	window.resetDrawingScreen();
	for (int i = 0;i < mCurrentHealth;i++) {
		mHearts[i]->draw(window);
	}
	for (int i = 0;i < mCurrentEnergy;i++) {
		mEnergy[i]->draw(window);
	}
	for (const auto & text : mTexts) {
		text->draw(window);
	}
}