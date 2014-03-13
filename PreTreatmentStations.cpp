#include "Debug.h"
#include "PreTreatmentStations.h"
#include "ServiceLocator.h"
#include "TracerService.h"
#include "Event.h"
#include "EventHandler.h"
#include "SimulationState.h"
#include <sstream>

using namespace std;

PreTreatmentStations::PreTreatmentStations(size_t sz) :
	ObjectPool(sz)
{}

void PreTreatmentStations::processWaitingList(SimulationState& state) {
	TracerService* tracer = ServiceLocator::instance().findTracerService();
	EventDispatcher* dispatcher = ServiceLocator::instance().findDispatcherService();
	RandomService<int>* random = ServiceLocator::instance().findRandomService();

	size_t preTreatmentsStarted = 0;
	while (!state.employees().empty() 
		&& !state.preTreatmentStations().empty() 
		&& state.preTreatmentStations().waiting()) {
		state.employees().acquire();
		state.preTreatmentStations().dequeue();
		state.preTreatmentStations().acquire();

		Event event = Event(state.clock().now() + random->next(state.preTreatmentProcTimeDist()));
		event.setHandler(new PreTreatmentEndHandler());
		dispatcher->dispatch(event);

		preTreatmentsStarted++;
	}
	if (preTreatmentsStarted > 0) {
		ostringstream oss;
		oss << preTreatmentsStarted << " garments started pre-treatment.";
		tracer->log(state.clock().now(), oss.str());
	}
}