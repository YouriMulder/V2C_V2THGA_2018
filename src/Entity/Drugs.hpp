#ifndef DRUGS_HPP
#define DRUGS_HPP
#include <functional>
#include "Player.hpp"

namespace Drugs {
	std::function<void()> health = [&]() {Player::resetHealth();};
	std::function<void()> energy = [&]() {Player::resetEnergy();};
	std::function<void()> both	 = [&]() {Player::reset();};
	std::function<void()> energySub2 = [&]() {Player::addEnergy(-2);};
	std::function<void()> energyAdd1 = [&]() {Player::addEnergy(1);};
}
#endif /*DRUGS_HPP*/