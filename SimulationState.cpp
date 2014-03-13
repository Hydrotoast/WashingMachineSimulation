#include "Debug.h"
#include "SimulationState.h"

using namespace std;

SimulationState::SimulationState(SimulationConfig config) :
	config_(config), clock_(0), stats_(),
	employees_(config.employeeCnt),
	preTreatmentStations_(config.preTreatments.stationCnt),
	cleaningMachines_(config.cleaningMachines.machineCnt),
	finishingStations_(config.finishings.stationCnt),
	preTreatmentProcTimeDist_(config.preTreatments.procTime.avg, config.preTreatments.procTime.stddev),
	finishingProcTimeDist_(config.finishings.procTime.avg, config.finishings.procTime.stddev),
	customerInterArrivalTimeDist_(config.customers.interArrivalTime.avg, config.customers.interArrivalTime.stddev),
	customerGarmentDropoffCntDist_(config.customers.garmentsDropoffCnt.avg, config.customers.garmentsDropoffCnt.stddev)
{}

SimulationConfig& SimulationState::config() {
	return config_;
}

discrete_time::Clock& SimulationState::clock() {
	return clock_;
}

SimulationStatistics& SimulationState::stats() {
	return stats_;
}

ObjectPool& SimulationState::employees() {
	return employees_;
}

PreTreatmentStations& SimulationState::preTreatmentStations() {
	return preTreatmentStations_;
}

CleaningMachines& SimulationState::cleaningMachines() {
	return cleaningMachines_;
}

FinishingStations& SimulationState::finishingStations() {
	return finishingStations_;
}

std::normal_distribution<double>& SimulationState::preTreatmentProcTimeDist() {
	return preTreatmentProcTimeDist_;
}

std::normal_distribution<double>& SimulationState::finishingProcTimeDist() {
	return finishingProcTimeDist_;
}

std::normal_distribution<double>& SimulationState::customerInterArrivalTimeDist() {
	return customerInterArrivalTimeDist_;
}

std::normal_distribution<double>& SimulationState::customerGarmentDropoffCntDist() {
	return customerGarmentDropoffCntDist_;
}

ostream& operator<<(ostream& os, SimulationState& state) {
	size_t employeeIdleTimePercentage = static_cast<size_t>(
			(static_cast<double>(state.stats().idleEmployeeTime)
			/ (state.config().employeeCnt 
				* state.config().simDuration)) 
			* 100u
		);
	os << "Garments Processed:\t\t" << state.stats().numGarmentsProcessed << endl
		<< "Garments Incomplete:\t\t" << state.stats().numGarmentsIncomplete << endl
		<< "Machine Batches Complete:\t" << state.stats().numMachineBatches << endl
		<< "Employee Idle Time Percentage:\t" << employeeIdleTimePercentage << endl;
	return os;
}