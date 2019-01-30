#ifndef TIMERS_HPP
#define TIMERS_HPP

#include <cstdint>
#include <vector>
#include "Timer.hpp"

/// \brief
/// This is the timers class. Used to make multiple timers using an id.
class Timers {
private:
	/// \brief
	/// The time a timer lasts.
	sf::Time mMaxTime = sf::seconds(1);

	/// \brief 
	/// The vector where all the ids and timers are stored in.
	std::vector<
		std::pair<uint_least64_t, Timer>
	> mTimers = {};
public:
	/// \brief
	/// This method add a timer to mTimers with the given id.
	/// \param id
	/// The id you want to connect to the timer.
	void addTimer(uint_least64_t id);

	/// \brief
	/// Delets all the expired timers.
	void deleteExpired();

	/// \brief
	/// Checks if a timer exists with the given id.
	/// \param id.
	/// The id of the timer you want to check for existance.
	bool isClocked(uint_least64_t id);
};


#endif /* TIMERS_HPP */
