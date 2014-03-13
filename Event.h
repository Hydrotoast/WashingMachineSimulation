/// Gio Carlo Cielo Borje
/// 41894135

#ifndef EVENT_H
#define EVENT_H

#include "DiscreteClock.h"
#include "SimulationState.h"

#include <functional>

class EventHandler;

class Event {
public:
	Event();
	Event(discrete_time::time_point time);
	~Event();
	Event(const Event& evt);
	Event& operator=(const Event& evt);

	discrete_time::time_point time() const;
	void setHandler(EventHandler* handler);

	void execute(SimulationState& state) const;

	friend bool operator<(const Event& op1, const Event& op2);
	friend bool operator==(const Event& op1, const Event& op2);
protected:
	discrete_time::time_point time_;
	EventHandler* handler;
};

#endif