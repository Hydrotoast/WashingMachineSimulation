#include "Debug.h"
#include "CleaningMachines.h"
#include "ServiceLocator.h"
#include "TracerService.h"
#include "Event.h"
#include "EventHandler.h"
#include "SimulationState.h"
#include <sstream>

using namespace std;

using namespace std;

CleaningMachines::CleaningMachines(size_t sz) :
	ResourcePool(sz)
{}

void CleaningMachines::processWaitingList(SimulationState& state) {
	if (state.cleaningMachines().empty() || state.employees().empty())
		return;

	TracerService* tracer = ServiceLocator::instance().findTracerService();
	EventDispatcher* dispatcher = ServiceLocator::instance().findDispatcherService();

	CleaningMachine m = state.cleaningMachines().acquire();
	while (m.numGarments != state.config().cleaningMachines.maxGarments
		&& state.cleaningMachines().waiting()) {
		state.cleaningMachines().dequeue();
		m.numGarments++;
	}
	if (m.numGarments != state.config().cleaningMachines.maxGarments
		&& !state.preTreatmentStations().empty()) {
		state.cleaningMachines().release(m);
		return;
	}

	ostringstream oss;
	oss << "Machine begins cleaning " << m.numGarments << " garments.";
	tracer->log(state.clock().now(), oss.str());

	Event event(state.clock().now() + state.config().cleaningMachines.procTime);
	event.setHandler(new CleaningEndHandler(m));
	dispatcher->dispatch(event);
}

bool CleaningMachines::unloadMachines(SimulationState& state) {
	if (state.employees().empty())
		return false;

	EventDispatcher* dispatcher = ServiceLocator::instance().findDispatcherService();
	TracerService* tracer = ServiceLocator::instance().findTracerService();

	while (!loadedMachines_.empty()) {
		CleaningMachine m = loadedMachines_.front();
		loadedMachines_.pop_front();

		state.finishingStations().enqueue(m.numGarments);

		ostringstream oss;
		oss << "Employee unloads machine with " << m.numGarments << " garments.";
		tracer->log(state.clock().now(), oss.str());

		m.numGarments = 0;
		release(m);
	}
	return true;
}

void CleaningMachines::enqueueUnload(CleaningMachine m) {
	loadedMachines_.push_back(m);
}