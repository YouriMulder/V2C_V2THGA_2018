#ifndef HUD_HPP
#define HUD_HPP

#include <vector>
#include <memory>
#include <string>
#include "Entity/EntityBase.hpp"
#include "Entity/LevelObject.hpp"
#include "Entity/Text.hpp"
#include "ViewManager.hpp"

class HUD {
private:
	int mCurrentHealth = 10;
	int mCurrentEnergy = 10;
	int mCurrentDeathCount = 0;
	std::vector<std::unique_ptr<EntityBase>> mHearts = {};
	std::vector<std::unique_ptr<EntityBase>> mEnergy = {};
	std::vector<std::unique_ptr<Text>> mTexts = {};

	int sizeOffset = 17;
	int textOffset = 65;
	sf::Color mHealthColor = sf::Color(255, 32, 1);

	std::string mPathHUD = "../res/Textures/HUD/";
	std::string mBaseDeath = "DEATHS: ";

public:
	HUD();
	~HUD();
	void updateHealth(int newHealth);
	void updateDeathCount(int newDeathCount);
	void updateEnergy(int newEnergy);
	void draw(ViewManager & window);
};

#endif /*HUD_HPP*/

