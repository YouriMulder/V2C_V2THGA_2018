#include "Timer.hpp"

Timer::Timer():
	mIsSet(false)
{
	init();
}

Timer::~Timer() {}

void Timer::set(const sf::Time& countDownTime) {
	mIsSet = true;
	mTimer.restart();
	mMaxTime = countDownTime;
}

void Timer::init() {
	set(sf::seconds(0));
}

bool Timer::isSet() const {
	return mIsSet;
}

bool Timer::isExpired() {
	if(mIsSet) {
		if(mTimer.getElapsedTime() >= mMaxTime) {
			return true;
		}
	}
	return false;
}
