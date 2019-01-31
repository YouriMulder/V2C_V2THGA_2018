#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Character.hpp"
#include "../SoundPlayer.hpp"

/// \brief
/// This is the Player class.
/// \details
/// This class is used to make playable characters for a game.
/// These playable characters move through the levels using the user's input.
class Player : public Character {
private:
	SoundPlayer mSoundPlayer;
protected:
	/// \brief
	/// The maximum health the player is able to have.
	static uint_least8_t maxHealth;
	
	/// \brief
	/// The current health the player has.
	static uint_least8_t health;
	
	/// \brief
	/// The maximum energy the player is able to have.
	static uint_least8_t maxEnergy;
	
	/// \brief
	/// The current energy the player has.
	static uint_least8_t energy;

public:
	/// \brief
	/// Returns the current health.
	/// \return
	/// A uint_least8_t containing the current health.
	static uint_least8_t getHealth();
	
	/// \brief
	/// Sets the maxHealth to the value of newMaxHealth.
	/// \param newMaxHealth
	/// The health maxHealth will be set to.
	static void setMaxHealth(uint_least8_t newMaxHealth);

	/// \brief
	/// Sets the health to the value of newhealth.
	/// \param newHealth
	/// The health value you want to set in health.
	static void setHealth(uint_least8_t newHealth);
	
	/// \brief
	/// Adds the deltaHealth to the value of health.
	/// \param deltaHealth
	/// The health value you want to add to health.
	static void addHealth(int_least8_t deltaHealth);
	
	/// \brief
	/// Sets the health back to the maxHealth.
	static void resetHealth();
	
	/// \brief
	/// Returns the current health.
	/// \return
	/// A uint_least8_t containing the current health.
	static uint_least8_t getEnergy();

	/// \brief
	/// Sets the maxEnergy to the value of newMaxEnergy.
	/// \param newMaxEnergy
	/// The energy maxEnergy will be set to.
	static void setMaxEnergy(uint_least8_t newMaxEnergy);

	/// \brief
	/// Sets the energy to the value of newEnergy.
	/// \param newEnergy
	/// The energy value you want to set in energy.
	static void setEnergy(uint_least8_t newEnergy);

	/// \brief
	/// Adds the deltaEnergy to the value of energy.
	/// \param deltaEnergy
	/// The energy value you want to add to energy.
	static void addEnergy(int_least8_t deltaEnergy);
	
	/// \brief
	/// Sets the health back to the maxHealth.
	static void resetEnergy();

	/// \brief
	/// Resets both the health and energy.
	static void reset();

	/// \brief
	/// Returns if the player's health is 0.
	static bool isDead();
	
	/// \brief
	/// Returns if the player's health is greater than 0.
	static bool isAlive();
	
	/// \brief
	/// This is the constructor for the Player class.
	Player(const sf::Vector2f& position, int screenNumber);
	virtual ~Player();

	/// \brief
	/// This method is used to shoot a lightning bolt.
	/// \details
	/// In this method the Character::shoot is called to start shooting the bolt.
	/// In this class the energy will be decreased.
	/// \return
	/// A bool containing whether or not the player was able to shoot.
	virtual bool shoot() override;

	/// \brief
	/// This method hurts the player and display this to the screen.
	/// \details
	/// The character startHurtAnimation is called 
	/// to make de Player look like it's getting hurt
	/// \param damage
	/// The amount of damage the Player took.
	virtual void hurt(uint_least8_t damage) override;

	/// \brief
	/// This method binds all the key pressed to the correct actions.
	/// \details
	/// This binds all the keys to the right actions 
	/// in the Character class using the bindAction method.
	/// This method should be called while initializing.
	virtual void bindActions() override;

	/// \brief
	/// This method binds the animations to the Character states.
	/// \details
	/// The Player animations will be bind using the Character bindAnimation method.
	/// This method should be called while initializing.
	virtual void bindAnimations() override;

	/// \brief
	/// This method handles the collision for the Player.
	/// \details
	/// In this method there will be checked if the finished is reached.
	/// All the other collision handeling in doen inside the Character class.
	virtual void handleCollision(
		std::vector<std::unique_ptr<EntityBase>*> top, 
		std::vector<std::unique_ptr<EntityBase>*> bottom, 
		std::vector<std::unique_ptr<EntityBase>*> left, 
		std::vector<std::unique_ptr<EntityBase>*> right, 
		CollisionSides hitSides
	);
};

#endif /* PLAYER_HPP */ 