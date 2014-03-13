/// Gio Carlo Cielo Borje
/// 41894135

#ifndef SIMULATION_CONFIG_H
#define SIMULATION_CONFIG_H

#include <random>

struct Distribution {
	unsigned int avg;
	unsigned int stddev;
};

struct StationCfg {
	unsigned int stationCnt;
	Distribution procTime;
};

struct MachineCfg {
	unsigned int machineCnt;
	unsigned int procTime;
	unsigned int maxGarments;
};

struct CustomerCfg {
	Distribution interArrivalTime;
	Distribution garmentsDropoffCnt;
};

struct SimulationConfig {
	unsigned int simDuration;
	unsigned int employeeCnt;

	StationCfg preTreatments;
	MachineCfg cleaningMachines;
	StationCfg finishings;
	CustomerCfg customers;
};

#endif