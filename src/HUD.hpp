#ifndef HUD_HPP
#define HUD_HPP

#include <vector>
#include <memory>
#include <string>
#include "Entity/EntityBase.hpp"
#include "Entity/LevelObject.hpp"
#include "Entity/Text.hpp"
#include "ViewManager.hpp"

/// \brief
/// Class to display all the information to screen(health,energy,deathcount).
class HUD {
private:
	/// \brief
	/// The current health that needs to be displayed.
	int mCurrentHealth = 10;

	/// \brief
	/// The current energy that needs to be displayed.
	int mCurrentEnergy = 10;

	/// \brief
	/// The current amount of deaths that needs to be displayed.
	int mCurrentDeathCount = 0;

	/// \brief
	/// Vector that contains all the hearts for displaying health.
	std::vector<std::unique_ptr<EntityBase>> mHearts = {};

	/// \brief
	/// Vector that contains all the energy bolts for displaying energy.
	std::vector<std::unique_ptr<EntityBase>> mEnergy = {};

	/// \brief
	/// Vector that contains all the texts that needs to be displayed.
	std::vector<std::unique_ptr<Text>> mTexts = {};
	
	/// \brief
	/// The offset for the size of the heart/energy sprites.
	float sizeOffset = 17;

	/// \brief
	/// The offset for the size of the text.
	float textOffset = 65;

	/// \brief
	/// Offset to place the hud a bit from the top and left of the screen.
	sf::Vector2f startOffset = sf::Vector2f(4.f, 4.f);

	/// \brief
	/// Color for the health text.
	sf::Color mHealthColor = sf::Color(255, 32, 1);

	/// \brief
	/// The path where all the hud sprites can be found.
	std::string mPathHUD = "../res/Textures/HUD/";

	/// \brief
	/// The base string for printing deaths.
	std::string mBaseDeath = "DEATHS: ";

public:
	/// \brief
	/// Constructor for HUD.
	HUD();

	~HUD();

	/// \brief
	/// Function to update the health.
	/// \details
	/// \param newHealth
	/// The new Health value.
	void updateHealth(int newHealth);

	/// \brief
	/// Function to update the deathcount.
	/// \details
	/// \param newDeathCount
	/// The new Death count value.
	void updateDeathCount(int newDeathCount);

	/// \brief
	/// Function to update the energy.
	/// \details
	/// \param newEnergy
	/// The new energy value.
	void updateEnergy(int newEnergy);

	/// \brief
	/// Function to draw the hud.
	/// \details
	/// \param window
	/// The viewManager on which the hud needs to be drawn.
	void draw(ViewManager & window);
};

#endif /*HUD_HPP*/

