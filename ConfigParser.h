/// Gio Carlo Cielo Borje
/// 41894135

#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H

#include "SimulationConfig.h"

#include <string>
#include <fstream>

/// Singleton
class ConfigParser {
public:
	static ConfigParser& instance();
	void parse();
	SimulationConfig build();
private:
	ConfigParser();
	ConfigParser(const ConfigParser&);
	ConfigParser& operator=(const ConfigParser&);

	SimulationConfig cfg;
};

#endif