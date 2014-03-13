#include "Debug.h"
#include "EventHandler.h"
#include "TracerService.h"
#include <iostream>
#include <sstream>

using namespace std;

CustomerArrivalHandler::CustomerArrivalHandler(size_t numGarments) : numGarments(numGarments) {}

CustomerArrivalHandler* CustomerArrivalHandler::clone() const {
	return new CustomerArrivalHandler(*this);
}

void CustomerArrivalHandler::operator()(const Event* evt, SimulationState& state) {
	TracerService* tracer = ServiceLocator::instance().findTracerService();
	EventDispatcher* dispatcher = ServiceLocator::instance().findDispatcherService();

	ostringstream oss;
	oss << numGarments << " garments enter the incoming queue.";
	tracer->log(evt->time(), oss.str());

	// Enqueue preTreatment
	state.stats().numGarmentsIncomplete += numGarments;
	state.stats().idleEmployeeTime += state.employees().size() * state.clock().recentAdvance();
	state.preTreatmentStations().enqueue(numGarments);

	// Bound Events
	Event event(state.clock().now());
	event.setHandler(new PreTreatmentStartHandler());
	dispatcher->dispatch(event);
}

PreTreatmentStartHandler* PreTreatmentStartHandler::clone() const {
	return new PreTreatmentStartHandler(*this);
}

void PreTreatmentStartHandler::operator()(const Event* evt, SimulationState& state) {
	EventDispatcher* dispatcher = ServiceLocator::instance().findDispatcherService();
	RandomService<int>* random = ServiceLocator::instance().findRandomService();

	Event event(state.clock().now() + random->next(state.customerInterArrivalTimeDist()));
	event.setHandler(new CustomerArrivalHandler(random->next(state.customerGarmentDropoffCntDist())));
	dispatcher->dispatch(event);
}

PreTreatmentEndHandler* PreTreatmentEndHandler::clone() const {
	return new PreTreatmentEndHandler(*this);
}

void PreTreatmentEndHandler::operator()(const Event* evt, SimulationState& state) {
	TracerService* tracer = ServiceLocator::instance().findTracerService();
	EventDispatcher* dispatcher = ServiceLocator::instance().findDispatcherService();
	RandomService<int>* random = ServiceLocator::instance().findRandomService();

	state.stats().idleEmployeeTime += state.employees().size() * state.clock().recentAdvance();
	state.employees().release();
	state.preTreatmentStations().release();
	tracer->log(evt->time(), "1 garment leaves pre-treatment.");

	// Enqueue cleaning
	state.cleaningMachines().enqueue();
}

CleaningEndHandler::CleaningEndHandler(CleaningMachine m) : m(m) {}

CleaningEndHandler* CleaningEndHandler::clone() const {
	return new CleaningEndHandler(*this);
}

void CleaningEndHandler::operator()(const Event* evt, SimulationState& state) {
	TracerService* tracer = ServiceLocator::instance().findTracerService();

	state.stats().idleEmployeeTime += state.employees().size() * state.clock().recentAdvance();
	state.stats().numMachineBatches++;

	ostringstream oss;
	oss << "Machine stops cleaning " << m.numGarments << " garments.";
	tracer->log(evt->time(), oss.str());

	// Enqueue finishing
	state.cleaningMachines().enqueueUnload(m);
}

FinishingEndHandler* FinishingEndHandler::clone() const {
	return new FinishingEndHandler(*this);
}

void FinishingEndHandler::operator()(const Event* evt, SimulationState& state) {
	TracerService* tracer = ServiceLocator::instance().findTracerService();

	state.stats().idleEmployeeTime += state.employees().size() * state.clock().recentAdvance();
	state.employees().release();
	state.finishingStations().release();
	tracer->log(evt->time(), "1 garment leaves finishing treatment.");
	state.stats().numGarmentsIncomplete--;
	state.stats().numGarmentsProcessed++;
}