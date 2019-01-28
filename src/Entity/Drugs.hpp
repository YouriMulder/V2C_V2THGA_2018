#ifndef DRUGS_HPP
#define DRUGS_HPP
#include <functional>
#include "Player.hpp"

namespace Drugs {
	std::function<void()> health = [&]() {Player::resetHealth();};
	std::function<void()> energy = [&]() {Player::resetEnergy();};
	std::function<void()> both	 = [&]() {Player::reset();};
}
#endif /*DRUGS_HPP*/