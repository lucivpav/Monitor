#pragma once

#include <vector>

#include "Monitor.h"

class MonitorManager {
public:
	MonitorManager();
	void Show();

	bool Set(int monitorId, int intensity);
	bool Brighter(int monitorId);
	bool Darker(int monitorId);

	bool SetAll(int intensity);
	bool BrighterAll();
	bool DarkerAll();
private:
	std::vector<Monitor> EnumerateMonitors();
	BOOL static MonitorEnumCallback(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData);
	bool BrighterOrDarker(int monitorId, bool brighter);
	bool BrighterOrDarkerAll(bool brighter);

	std::vector<Monitor> monitors;
};