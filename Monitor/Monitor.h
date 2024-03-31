#pragma once

#pragma comment(lib, "Dxva2.lib")

#include <physicalmonitorenumerationapi.h>
#include <highlevelmonitorconfigurationapi.h>

#include <vector>

class Monitor
{
public:
    explicit Monitor(PHYSICAL_MONITOR pm);
    ~Monitor();

    bool brightnessSupported() const;

    int minimumBrightness() const;
    int maximumBrightness() const;
    int currentBrightness() const;

    void setCurrentBrightness(int b);
    // Set brightness from 0.0-1.0
    void setCurrentBrightnessFraction(double fraction);


    int currentContrast() const;

    void setCurrentContrast(int b);
private:
    bool mBrightnessSupported = false;
    int mMinimumBrightness = 0;
    int mMaximumBrightness = 0;
    int mCurrentBrightness = 0;

    bool mContrastSupported = false;
    int mMinimumContrast = 0;
    int mMaximumContrast = 0;
    int mCurrentContrast = 0;

    PHYSICAL_MONITOR mPhysicalMonitor;
};

std::vector<Monitor> EnumerateMonitors();