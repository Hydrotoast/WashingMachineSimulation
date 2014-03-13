#include "ConfigParser.h"
#include <iostream>

using namespace std;

ConfigParser::ConfigParser() {}

ConfigParser& ConfigParser::instance() {
	static ConfigParser instance;
	return instance;
}

void ConfigParser::parse() {
	unsigned int duration;

	// Counts
	cin >> duration;
	cfg.simDuration = duration * 60 * 60;
	cin >> cfg.employeeCnt;
	cin >> cfg.preTreatments.stationCnt;
	cin >> cfg.cleaningMachines.machineCnt;
	cin >> cfg.finishings.stationCnt;

	// Pre Treatment Configuration
	cin >> cfg.preTreatments.procTime.avg;
	cin >> cfg.preTreatments.procTime.stddev;

	// Cleaning Machine Configuration
	cin >> cfg.cleaningMachines.procTime;
	cin >> cfg.cleaningMachines.maxGarments;

	// Finishing Station Configuration
	cin >> cfg.finishings.procTime.avg;
	cin >> cfg.finishings.procTime.stddev;
	
	// Customer Configuration
	cin >> cfg.customers.interArrivalTime.avg;
	cin >> cfg.customers.interArrivalTime.stddev;
	cin >> cfg.customers.garmentsDropoffCnt.avg;
	cin >> cfg.customers.garmentsDropoffCnt.stddev;
}

SimulationConfig ConfigParser::build() {
	return cfg;
}