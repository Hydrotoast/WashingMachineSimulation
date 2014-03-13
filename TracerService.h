/// Gio Carlo Cielo Borje
/// 41894135

#ifndef TRACER_SERVICE_H
#define TRACER_SERVICE_H

#include "DiscreteClock.h"
#include <iostream>
#include <string>

class TracerService {
public:
	void log(discrete_time::time_point time, std::string message);
private:
	std::string formatTime(discrete_time::time_point time);
};

#endif