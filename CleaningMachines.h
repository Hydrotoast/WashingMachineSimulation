/// Gio Carlo Cielo Borje
/// 41894135

#ifndef CLEANING_MACHINES_H
#define CLEANING_MACHINES_H

#include "ResourcePool.h"

class Event;
class SimulationState;

struct CleaningMachine {
	size_t numGarments;
	CleaningMachine() : numGarments(0) {}
};

class CleaningMachines : public ResourcePool<CleaningMachine> {
public:
	CleaningMachines(size_t sz);
	void processWaitingList(SimulationState& state);
	bool unloadMachines(SimulationState& state);

	void enqueueUnload(CleaningMachine m);
private:
	std::list<CleaningMachine> loadedMachines_;
};


#endif