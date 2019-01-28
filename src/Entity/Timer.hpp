#ifndef TIMER_HPP
#define TIMER_HPP

#include <SFML/System/Clock.hpp>

class Timer {
private:
	sf::Clock mTimer;
	sf::Time mMaxTime;
	bool mIsSet;

public:
	Timer();
	virtual ~Timer();

	void set(const sf::Time& countDownTime);
	void init();
	bool isSet() const;
	bool isExpired();
};

#endif /* TIMER_HPP */