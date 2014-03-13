/// Gio Carlo Cielo Borje
/// 41894135

#ifndef SIMULATION_STATISTICS_H
#define SIMULATION_STATISTICS_H

#include <ostream>

struct SimulationStatistics {
	size_t numGarmentsProcessed ;
	size_t numGarmentsIncomplete;
	size_t numMachineBatches;
	size_t idleEmployeeTime;

	SimulationStatistics();
};

#endif