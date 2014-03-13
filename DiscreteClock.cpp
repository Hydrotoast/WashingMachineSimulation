#include "DiscreteClock.h"

using namespace discrete_time;

Clock::Clock(time_point epoch) : 
	epoch_(epoch), currentTime_(epoch)
{}

time_point Clock::epoch() const {
	return epoch_;
}

time_point Clock::now() const {
	return currentTime_;
}

time_point Clock::previousTime() const {
	return previousTime_;
}

duration_t Clock::recentAdvance() const {
	return recentAdvance_;
}

void Clock::advance(duration_t duration) {
	previousTime_ = currentTime_;
	currentTime_ += duration;
	recentAdvance_ = duration;
}

void Clock::advanceTo(time_point time) {
	if (currentTime_ == time)
		return;
	previousTime_ = currentTime_;
	currentTime_ = time;
	recentAdvance_ = currentTime_ - previousTime_;
}