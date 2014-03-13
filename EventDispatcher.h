/// Gio Carlo Cielo Borje
/// 41894135

#ifndef EVENT_DISPATCHER_H
#define EVENT_DISPATCHER_H

#include "PriorityQueue.h"
#include "Event.h"

#include <functional>
#include <queue>
#include <map>

#include <typeinfo>
#include <typeindex>

class SimulationState;

class EventDispatcher {
public:
	EventDispatcher(SimulationState& state);

	void dispatch(const Event evt);
	void run();
	void processConditionalEvents();
	void printStatistics();
private:
	EventDispatcher(const EventDispatcher&);
	EventDispatcher& operator=(const EventDispatcher&);

	SimulationState& state;
	PriorityQueue<Event> pendingQueue;
};

#endif