/// Gio Carlo Cielo Borje
/// 41894135

#ifndef PRETREATMENT_STATION_H
#define PRETREATMENT_STATION_H

#include "ObjectPool.h"

class Event;
class SimulationState;

class PreTreatmentStations : public ObjectPool {
public:
	PreTreatmentStations(size_t sz);
	void processWaitingList(SimulationState& state);
};

#endif