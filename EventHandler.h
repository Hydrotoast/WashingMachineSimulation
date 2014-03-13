/// Gio Carlo Cielo Borje
/// 41894135

#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "ServiceLocator.h"
#include "EventDispatcher.h"
#include "RandomService.h"
#include "SimulationState.h"
#include "Event.h"

class EventHandler {
public:
	virtual EventHandler* clone() const = 0;
	virtual void operator()(const Event* evt, SimulationState& state) = 0;
};

class CustomerArrivalHandler : public EventHandler {
public:
	CustomerArrivalHandler(size_t numGarments);
	virtual CustomerArrivalHandler* clone() const;

	virtual void operator()(const Event* evt, SimulationState& state);
private:
	size_t numGarments;
};

class PreTreatmentStartHandler : public EventHandler {
public:
	virtual PreTreatmentStartHandler* clone() const;
	virtual void operator()(const Event* evt, SimulationState& state);
};

class PreTreatmentEndHandler : public EventHandler {
public:
	virtual PreTreatmentEndHandler* clone() const;
	virtual void operator()(const Event* evt, SimulationState& state);
};

class CleaningEndHandler : public EventHandler {
public:
	CleaningEndHandler(CleaningMachine m);
	virtual CleaningEndHandler* clone() const;
	virtual void operator()(const Event* evt, SimulationState& state);
private:
	CleaningMachine m;
};

class FinishingEndHandler : public EventHandler {
public:
	virtual FinishingEndHandler* clone() const;
	virtual void operator()(const Event* evt, SimulationState& state);
};

#endif