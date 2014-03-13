#include "Debug.h"
#include "EventDispatcher.h"
#include "SimulationState.h"
#include "ServiceLocator.h"
#include "RandomService.h"
#include "EventHandler.h"

#include <iostream>

using namespace std;

EventDispatcher::EventDispatcher(SimulationState& state) :
	state(state)
{}

void EventDispatcher::dispatch(const Event evt) {
	pendingQueue.push(evt);
}

void EventDispatcher::run() {
	SimulationConfig& config = state.config();
	discrete_time::Clock& clock = state.clock();
	RandomService<int>* random = ServiceLocator::instance().findRandomService();
	Event evt(random->next(state.customerInterArrivalTimeDist()));
	evt.setHandler(new CustomerArrivalHandler(random->next(state.customerGarmentDropoffCntDist())));
	pendingQueue.push(evt);
	while (!pendingQueue.empty() && clock.now() < config.simDuration) {
		Event evt = pendingQueue.min();
		pendingQueue.pop();
		clock.advanceTo(evt.time());
		if (clock.now() < config.simDuration) {
			evt.execute(state);
			processConditionalEvents();
		}
	}
}

void EventDispatcher::processConditionalEvents() {
	state.cleaningMachines().unloadMachines(state);
	state.finishingStations().processWaitingList(state);
	state.cleaningMachines().processWaitingList(state);
	state.preTreatmentStations().processWaitingList(state);
}

void EventDispatcher::printStatistics() {
	cout << endl << state << endl;
}