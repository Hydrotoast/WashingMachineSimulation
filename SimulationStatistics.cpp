#include "Debug.h"
#include "SimulationStatistics.h"

using namespace std;

SimulationStatistics::SimulationStatistics() :
	numGarmentsProcessed(0),
	numGarmentsIncomplete(0),
	numMachineBatches(0),
	idleEmployeeTime(0)
{}
