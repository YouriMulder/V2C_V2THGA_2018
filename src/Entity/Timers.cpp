#include "Timers.hpp"
#include <cstdint>
#include <SFML/System.hpp>

void Timers::addClock(uint_least64_t entityId) {
	for (const auto & clockPair : mClocks) {
		if (clockPair.first == entityId) {
			return;
		}
	}
	mClocks.push_back(
		std::make_pair(entityId, sf::Clock())
	);
}

void Timers::deleteExpired() {
	for(unsigned int i = 0; i < mClocks.size(); ++i) {
		if(mClocks[i].second.getElapsedTime() > mMaxTime) {
			mClocks.erase(mClocks.begin() + i);
		}
	}
}

bool Timers::isClocked(uint_least64_t entityId) {
	for(size_t i = 0; i < mClocks.size(); ++i) {
		if(mClocks[i].first == entityId) {
			if(mClocks[i].second.getElapsedTime() > mMaxTime) {
				mClocks.erase(mClocks.begin() + i);
				return false; 
			}
			return true;
		}
	}
	return false;
}