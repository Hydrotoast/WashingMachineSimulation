/// Gio Carlo Cielo Borje
/// 41894135

#ifndef FINISHING_STATIONS_H
#define FINISHING_STATIONS_H

#include "ObjectPool.h"

class Event;
class SimulationState;

class FinishingStations : public ObjectPool {
public:
	FinishingStations(size_t sz);
	void processWaitingList(SimulationState& state);
};

#endif