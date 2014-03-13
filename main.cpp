/// Gio Carlo Cielo Borje
/// 41894135

#include "Debug.h"
#include "ServiceLocator.h"
#include "SimulationState.h"
#include "ConfigParser.h"

#include "EventDispatcher.h"
#include "RandomService.h"
#include "TracerService.h"

#include <iostream>
#include <typeinfo>

using namespace std;

int main(int argc, char* argv[]) {
	ConfigParser::instance().parse();
	SimulationState state(ConfigParser::instance().build());
	EventDispatcher* dispatcher = new EventDispatcher(state);
	RandomService<int>* random = new RandomService<int>(random_device());
	TracerService* tracer = new TracerService();

	ServiceLocator::instance().registerDispatcherService(dispatcher);
	ServiceLocator::instance().registerRandomService(random);
	ServiceLocator::instance().registerTracerService(tracer);

	ServiceLocator::instance().findDispatcherService()->run();
	ServiceLocator::instance().findDispatcherService()->printStatistics();

	_CrtDumpMemoryLeaks();

	delete dispatcher;
	delete random;
	delete tracer;
	system("pause");
	return EXIT_SUCCESS;
}