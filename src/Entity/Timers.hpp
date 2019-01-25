#ifndef TIMERS_HPP
#define TIMERS_HPP

#include <cstdint>
#include <vector>
#include <SFML/System.hpp>

class Timers {
private:
	sf::Time mMaxTime = sf::seconds(1);

	std::vector<
		std::pair<uint_least64_t, sf::Clock>
	> mClocks = {};
public:
	void addClock(uint_least64_t id);
	void deleteExpired();
	bool isClocked(uint_least64_t id);
};


#endif /* TIMERS_HPP */