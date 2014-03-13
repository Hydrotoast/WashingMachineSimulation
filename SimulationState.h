/// Gio Carlo Cielo Borje
/// 41894135

#ifndef SIMULATION_STATE_H
#define SIMULATION_STATE_H

#include "DiscreteClock.h"
#include "ObjectPool.h"
#include "ResourcePool.h"

#include "SimulationConfig.h"
#include "SimulationStatistics.h"
#include "PreTreatmentStations.h"
#include "CleaningMachines.h"
#include "FinishingStations.h"
#include <iostream>

class Event;

class SimulationState {
public:
	SimulationState(SimulationConfig config);

	SimulationConfig& config();
	discrete_time::Clock& clock();
	SimulationStatistics& stats();

	ObjectPool& employees();
	PreTreatmentStations& preTreatmentStations();
	CleaningMachines& cleaningMachines();
	FinishingStations& finishingStations();

	std::normal_distribution<double>& preTreatmentProcTimeDist();
	std::normal_distribution<double>& finishingProcTimeDist();
	std::normal_distribution<double>& customerInterArrivalTimeDist();
	std::normal_distribution<double>& customerGarmentDropoffCntDist();
private:
	SimulationConfig config_;
	discrete_time::Clock clock_;
	SimulationStatistics stats_;

	ObjectPool employees_;
	PreTreatmentStations preTreatmentStations_;
	CleaningMachines cleaningMachines_;
	FinishingStations finishingStations_;

	std::normal_distribution<double> preTreatmentProcTimeDist_;
	std::normal_distribution<double> finishingProcTimeDist_;
	std::normal_distribution<double> customerInterArrivalTimeDist_;
	std::normal_distribution<double> customerGarmentDropoffCntDist_;
};

std::ostream& operator<<(std::ostream& os, SimulationState& state);

#endif