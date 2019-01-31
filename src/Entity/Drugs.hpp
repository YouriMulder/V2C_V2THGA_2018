#ifndef DRUGS_HPP
#define DRUGS_HPP
#include <functional>
#include "Player.hpp"
#include "../SoundPlayer.hpp"
/// \brief
/// Namespace containing the lambda's corresponding to drug names.
namespace Drugs {
	/// \brief
	/// Lambda for a health reset drug.
	std::function<void()> health = [&]() {Player::resetHealth();};

	/// \brief
	/// Lambda for a energy reset drug.
	std::function<void()> energy = [&]() {Player::resetEnergy(); };

	/// \brief
	/// Lambda for a energy and health reset drug.
	std::function<void()> both	 = [&]() {Player::reset(); };

	/// \brief
	/// Lambda for a energy -2 drug.
	std::function<void()> energySub2 = [&]() {Player::addEnergy(-2); };

	/// \brief
	/// Lambda for a energy +1 drug.
	std::function<void()> energyAdd1 = [&]() {Player::addEnergy(1); };
}
#endif /*DRUGS_HPP*/