#include "Debug.h"
#include "Event.h"
#include "EventHandler.h"

using namespace std;

Event::Event() : time_(0u) {}

Event::Event(discrete_time::time_point time) : time_(time) {}

Event::~Event() {
	delete handler;
}

Event::Event(const Event& evt) :
	time_(evt.time_), handler(evt.handler->clone())
{}

Event& Event::operator=(const Event& evt) {
	if (this == &evt)
		return *this;
	delete handler;
	this->time_ = evt.time_;
	this->handler = evt.handler->clone();
	return *this;
}

discrete_time::time_point Event::time() const {
	return time_;
}

void Event::setHandler(EventHandler* handler) {
	this->handler = handler;
}

void Event::execute(SimulationState& state) const {
	(*handler)(this, state);
}

bool operator==(const Event& op1, const Event& op2) {
	return op1.time() == op2.time(); 
}

bool operator<(const Event& op1, const Event& op2) {
	return op1.time() < op2.time();
}
