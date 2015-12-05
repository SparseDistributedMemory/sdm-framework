#ifndef SDM_SERVER_H
#define SDM_SERVER_H

#include "address_space.h"
#include "counter.h"
#include "scanner.h"

class ServerConfig {
public:
	std::string address_spaces_dir;
	std::string counters_dir;
};

class Server {
public:
	const ServerConfig *config;

	void run(const ServerConfig &config);
};

class Memory {
	std::string space_name;
	std::string counters_name;
	std::string scanner_type;

	AddressSpace *space;
	Counter<int> *counters;

	Scanner *scanner;
};

#endif