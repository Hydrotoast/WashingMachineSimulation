/// Gio Carlo Cielo Borje
/// 41894135

#ifndef DISCRETE_CLOCK_H
#define DISCRETE_CLOCK_H

namespace discrete_time {
	typedef unsigned int duration_t;
	typedef unsigned int time_point;

	class Clock {
	public:
		explicit Clock(time_point epoch);
		
		time_point epoch() const;
		time_point now() const;
		time_point previousTime() const;
		duration_t recentAdvance() const;

		void advance(duration_t duration);
		void advanceTo(time_point time);
	protected:
		time_point epoch_;
		time_point previousTime_;
		time_point currentTime_;
		duration_t recentAdvance_;
	};
}

#endif