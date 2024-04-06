#include <iostream>
#include "MonitorManager.h"

void Usage() {
	std::cout << "Monitor.exe -- prints the usage information" << std::endl;
	std::cout << "Monitor.exe /show -- prints current brightness and contrast for every monitor detected" << std::endl;
	std::cout << std::endl;
	std::cout << "Monitor.exe /set 1 60 -- sets both brightness and contrast to 60% of monitor with id 1" << std::endl;
	std::cout << "Monitor.exe /brighter 1 -- increases the brightness and contrast to +10% of monitor with id 1" << std::endl;
	std::cout << "Monitor.exe /darker 1 -- decreases the brightness and contrast to -10% of monitor with id 1" << std::endl;
	std::cout << std::endl;
	std::cout << "Monitor.exe /set 60 -- sets both brightness and contrast to 60% of all monitors" << std::endl;
	std::cout << "Monitor.exe /brighter -- increases the brightness and contrast to +10% of all monitors" << std::endl;
	std::cout << "Monitor.exe /darker -- decreases the brightness and contrast to -10% of all monitors" << std::endl;
}

int MapOpResultToExitCode(bool opSuccess) {
	return opSuccess ? 0 : 1;
}

int main(int argc, char ** argv) {
	if (argc == 1) {
		Usage();
		return 1;
	}

	MonitorManager manager;
	
	if (argc == 2 && std::string("/show") == std::string(argv[1])) {
		manager.Show();
		return 0;
	}

	if (argc == 4 && std::string("/set") == std::string(argv[1])) {
		int monitorId = std::atoi(argv[2]);
		int intensity = std::atoi(argv[3]);
		return MapOpResultToExitCode(manager.Set(monitorId, intensity));
	}

	if (argc == 3 && std::string("/brighter") == std::string(argv[1])) {
		int monitorId = std::atoi(argv[2]);
		return MapOpResultToExitCode(manager.Brighter(monitorId));
	}

	if (argc == 3 && std::string("/darker") == std::string(argv[1])) {
		int monitorId = std::atoi(argv[2]);
		return MapOpResultToExitCode(manager.Darker(monitorId));
	}

	if (argc == 3 && std::string("/set") == std::string(argv[1])) {
		int intensity = std::atoi(argv[2]);
		return MapOpResultToExitCode(manager.SetAll(intensity));
	}

	if (argc == 2 && std::string("/brighter") == std::string(argv[1])) {
		return MapOpResultToExitCode(manager.BrighterAll());
	}

	if (argc == 2 && std::string("/darker") == std::string(argv[1])) {
		return MapOpResultToExitCode(manager.DarkerAll());
	}

	Usage();
	return 1;
}
