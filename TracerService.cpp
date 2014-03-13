#include "TracerService.h"
#include <sstream>

using namespace std;

void TracerService::log(discrete_time::time_point time, string message) {
	string timeStr = formatTime(time);
	string delim = " - ";
	cout << timeStr << delim << message << endl;
	cout.flush();
}

string TracerService::formatTime(discrete_time::time_point time) {
	ostringstream oss;
	unsigned int hrs = time / 3600u;
	unsigned int mins = (time / 60u) % 60u;
	unsigned int secs = time % 60u;
	oss.fill('0');
	oss.width(2);
	oss << hrs << ":";
	oss.fill('0');
	oss.width(2);
	oss << mins << ":";
	oss.fill('0');
	oss.width(2);
	oss << secs;
	return oss.str();
}