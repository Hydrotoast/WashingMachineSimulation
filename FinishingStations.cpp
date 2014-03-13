#include "FinishingStations.h"
#include "ServiceLocator.h"
#include "TracerService.h"
#include "Event.h"
#include "EventHandler.h"
#include "SimulationState.h"

FinishingStations::FinishingStations(size_t sz) :
	ObjectPool(sz)
{}

void FinishingStations::processWaitingList(SimulationState& state) {
	while (!state.employees().empty() 
		&& !empty()
		&& waiting()) {
		state.employees().acquire();
		dequeue();
		acquire();

		TracerService* tracer = ServiceLocator::instance().findTracerService();
		tracer->log(state.clock().now(), "1 garment begins finishing treatment.");

		EventDispatcher* dispatcher = ServiceLocator::instance().findDispatcherService();
		RandomService<int>* random = ServiceLocator::instance().findRandomService();

		Event event(state.clock().now() + random->next(state.finishingProcTimeDist()));
		event.setHandler(new FinishingEndHandler());
		dispatcher->dispatch(event);
	}
}