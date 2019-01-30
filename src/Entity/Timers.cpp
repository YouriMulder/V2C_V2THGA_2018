#include "Timers.hpp"
#include <cstdint>
#include <SFML/System.hpp>

void Timers::addTimer(uint_least64_t entityId) {
	for (const auto & clockPair : mTimers) {
		if (clockPair.first == entityId) {
			return;
		}
	}
	Timer timer;
	timer.set(mMaxTime);
	mTimers.push_back(
		std::make_pair(entityId, timer)
	);
}

void Timers::deleteExpired() {
	for(unsigned int i = 0; i < mTimers.size(); ++i) {
		if(mTimers[i].second.isExpired()) {
			mTimers.erase(mTimers.begin() + i);
		}
	}
}

bool Timers::isClocked(uint_least64_t entityId) {
	for(size_t i = 0; i < mTimers.size(); ++i) {
		if(mTimers[i].first == entityId) {
			if(mTimers[i].second.isExpired()) {
				mTimers.erase(mTimers.begin() + i);
				return false; 
			}
			return true;
		}
	}
	return false;
}