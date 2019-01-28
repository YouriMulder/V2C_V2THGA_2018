#include "Timer.hpp"

Timer::Timer() {}
Timer::~Timer() {}

void Timer::set(const sf::Time& countDownTime) {
	mIsSet = true;
	mTimer.restart();
	mMaxTime = countDownTime;
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
