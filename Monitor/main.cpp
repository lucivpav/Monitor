#include <iostream>
#include "Monitor.h"

void Usage() {
	std::cout << "Monitor.exe -- prints the usage information" << std::endl;
	std::cout << "Monitor.exe /show -- prints current brightness and contrast for every monitor detected" << std::endl;
	std::cout << "Monitor.exe /set 1 60 -- sets both brightness and contrast to 60 of monitor with id 1" << std::endl;
}

void Show() {
	auto monitors = EnumerateMonitors();
	if (monitors.empty()) {
		std::cout << "No monitors found." << std::endl;
		return;
	}
	for (int i = 0; i < monitors.size(); i++) {
		if (i != 0) std::cout << std::endl;
		std::cout << "Monitor " << i << ": " << std::endl;
		std::cout << "Current brightness: " << monitors[i].currentBrightness() << std::endl;
		std::cout << "Current contrast: " << monitors[i].currentContrast() << std::endl;
	}
}

bool Set(int monitorId, int intensity) {
	auto monitors = EnumerateMonitors();
	if (monitorId >= monitors.size() || monitorId < 0) {
		std::cerr << "Monitor with id " << monitorId << " not found" << std::endl;
		return false;
	}
	monitors[monitorId].setCurrentBrightness(intensity);
	monitors[monitorId].setCurrentContrast(intensity);
	return true;
}

int main(int argc, char ** argv) {
	if (argc == 1) {
		Usage();
		return 1;
	}
	
	if (argc == 2 && std::string("/show") == std::string(argv[1])) {
		Show();
		return 0;
	}

	if (argc == 4 && std::string("/set") == std::string(argv[1])) {
		int monitorId = std::atoi(argv[2]);
		int intensity = std::atoi(argv[3]);
		if (!Set(monitorId, intensity))
			return 1;
		return 0;
	}

	Usage();
	return 1;
}
