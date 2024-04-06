#include "MonitorManager.h"
#include <iostream>

MonitorManager::MonitorManager()
{
    monitors = EnumerateMonitors();
}

std::vector<Monitor> MonitorManager::EnumerateMonitors()
{
    std::vector<Monitor> monitors;
    EnumDisplayMonitors(NULL, NULL, MonitorEnumCallback, reinterpret_cast<LPARAM>(&monitors));
    return monitors;
}

BOOL CALLBACK MonitorManager::MonitorEnumCallback(_In_ HMONITOR hMonitor, _In_ HDC hdcMonitor, _In_ LPRECT lprcMonitor, _In_ LPARAM dwData)
{
    std::vector<Monitor>* monitors = reinterpret_cast<std::vector<Monitor>*>(dwData);

    // Get the number of physical monitors.
    DWORD cPhysicalMonitors;
    BOOL bSuccess = GetNumberOfPhysicalMonitorsFromHMONITOR(hMonitor, &cPhysicalMonitors);

    LPPHYSICAL_MONITOR pPhysicalMonitors = NULL;
    if (bSuccess)
    {
        // Allocate the array of PHYSICAL_MONITOR structures.
        LPPHYSICAL_MONITOR pPhysicalMonitors = new PHYSICAL_MONITOR[cPhysicalMonitors];

        if (pPhysicalMonitors != NULL)
        {
            // Get the array.
            bSuccess = GetPhysicalMonitorsFromHMONITOR(hMonitor, cPhysicalMonitors, pPhysicalMonitors);

            // Use the monitor handles.
            for (unsigned int i = 0; i < cPhysicalMonitors; ++i)
            {
                monitors->push_back(Monitor(pPhysicalMonitors[i]));
            }
        }
    }
    // Return true to continue enumeration.
    return TRUE;
}

void MonitorManager::Show() {
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

bool MonitorManager::Set(int monitorId, int intensity) {
	if (monitorId >= monitors.size() || monitorId < 0) {
		std::cerr << "Monitor with id " << monitorId << " not found" << std::endl;
		return false;
	}
	bool result = true;
	if (!monitors[monitorId].setCurrentBrightness(intensity)) {
		std::cerr << "Error setting brightness for monitor " << monitorId << std::endl;
		result = false;
	}
	if (!monitors[monitorId].setCurrentContrast(intensity)) {
		std::cerr << "Error setting contrast for monitor " << monitorId << std::endl;
		result = false;
	}
	return result;
}

bool MonitorManager::BrighterOrDarker(int monitorId, bool brighter) {
	if (monitors.empty()) {
		std::cout << "No monitors found." << std::endl;
		return false;
	}
	if (monitorId >= monitors.size() || monitorId < 0) {
		std::cerr << "Monitor with id " << monitorId << " not found" << std::endl;
		return false;
	}
	const int currentIntensity = monitors[monitorId].currentBrightness();
	const int newIntensity = brighter ? min(currentIntensity + 10, 100) : max(currentIntensity - 10, 0);

	bool result = true;
	if (!monitors[monitorId].setCurrentBrightness(newIntensity)) {
		std::cerr << "Error setting brightness for monitor " << monitorId << std::endl;
		result = false;
	}

	if (!monitors[monitorId].setCurrentContrast(newIntensity)) {
		std::cerr << "Error setting contrast for monitor " << monitorId << std::endl;
		result = false;
	}
	return result;
}

bool MonitorManager::SetAll(int intensity)
{
	if (monitors.empty()) {
		std::cout << "No monitors found." << std::endl;
		return true;
	}
	bool result = true;
	for (int i = 0; i < monitors.size(); i++) {
		result &= Set(i, intensity);
	}
	return result;
}

bool MonitorManager::Brighter(int monitorId) {
	return BrighterOrDarker(monitorId, true);
}

bool MonitorManager::Darker(int monitorId) {
	return BrighterOrDarker(monitorId, false);
}

bool MonitorManager::BrighterAll() {
	return BrighterOrDarkerAll(true);
}

bool MonitorManager::DarkerAll() {
	return BrighterOrDarkerAll(false);
}

bool MonitorManager::BrighterOrDarkerAll(bool brighter) {
	if (monitors.empty()) {
		std::cout << "No monitors found." << std::endl;
		return true;
	}
	bool result = true;
	for (int i = 0; i < monitors.size(); i++) {
		result &= BrighterOrDarker(i, brighter);
	}
	return result;
}