#include "Monitor.h"

Monitor::Monitor(PHYSICAL_MONITOR pm) : mPhysicalMonitor(pm)
{
    DWORD dwMonitorCapabilities = 0;
    DWORD dwSupportedColorTemperatures = 0;
    BOOL bSuccess = GetMonitorCapabilities(mPhysicalMonitor.hPhysicalMonitor, &dwMonitorCapabilities, &dwSupportedColorTemperatures);

    if (bSuccess)
    {
        if (dwMonitorCapabilities & MC_CAPS_BRIGHTNESS)
        {
            // Get min and max brightness.
            DWORD dwMinimumBrightness = 0;
            DWORD dwMaximumBrightness = 0;
            DWORD dwCurrentBrightness = 0;
            bSuccess = GetMonitorBrightness(mPhysicalMonitor.hPhysicalMonitor, &dwMinimumBrightness, &dwCurrentBrightness, &dwMaximumBrightness);
            
            if (bSuccess)
            {
                mBrightnessSupported = true;
                mMinimumBrightness = dwMinimumBrightness;
                mMaximumBrightness = dwMaximumBrightness;
            }
        }

        if (dwMonitorCapabilities & MC_CAPS_CONTRAST)
        {
            // Get min and max contrast.
            DWORD dwMinimumContrast = 0;
            DWORD dwMaximumContrast = 0;
            DWORD dwCurrentContrast = 0;
            bSuccess = GetMonitorContrast(mPhysicalMonitor.hPhysicalMonitor, &dwMinimumContrast, &dwCurrentContrast, &dwMaximumContrast);

            if (bSuccess)
            {
                mContrastSupported = true;
                mMinimumContrast = dwMinimumContrast;
                mMaximumContrast = dwMaximumContrast;
            }
        }
    }
}

Monitor::~Monitor()
{
}

bool Monitor::brightnessSupported() const
{
    return mBrightnessSupported;
}

int Monitor::minimumBrightness() const
{
    return mMinimumBrightness;
}

int Monitor::maximumBrightness() const
{
    return mMaximumBrightness;
}

int Monitor::currentBrightness() const
{
    if (!mBrightnessSupported)
        return -1;

    DWORD dwMinimumBrightness = 0;
    DWORD dwMaximumBrightness = 100;
    DWORD dwCurrentBrightness = 0;
    BOOL bSuccess = GetMonitorBrightness(mPhysicalMonitor.hPhysicalMonitor, &dwMinimumBrightness, &dwCurrentBrightness, &dwMaximumBrightness);
    if (bSuccess)
    {
        return dwCurrentBrightness;
    }
    return -1;
}

int Monitor::currentContrast() const
{
    if (!mContrastSupported)
        return -1;

    DWORD dwMinimumContrast = 0;
    DWORD dwMaximumContrast = 100;
    DWORD dwCurrentContrast = 0;
    BOOL bSuccess = GetMonitorBrightness(mPhysicalMonitor.hPhysicalMonitor, &dwMinimumContrast, &dwCurrentContrast, &dwMaximumContrast);
    if (bSuccess)
    {
        return dwCurrentContrast;
    }
    return -1;
}

bool Monitor::setCurrentBrightness(int b)
{
    if (!mBrightnessSupported)
        return false;

    return SetMonitorBrightness(mPhysicalMonitor.hPhysicalMonitor, b);
}

bool Monitor::setCurrentContrast(int b)
{
    if (!mContrastSupported)
        return false;

    // The constrast setting Win32 API gives unstable results - often it is no-op even though true is returned.
    // Run setCurrentContrast() twice to lower the risk of unexpected behavior for the end user.
    bool firstResult = SetMonitorContrast(mPhysicalMonitor.hPhysicalMonitor, b);
    Sleep(20);
    bool secondResult = SetMonitorContrast(mPhysicalMonitor.hPhysicalMonitor, b);
    return firstResult || secondResult;
}

void Monitor::setCurrentBrightnessFraction(double fraction)
{
    if (!mBrightnessSupported)
        return;
    if (mMinimumBrightness >= mMaximumBrightness)
        return;
    setCurrentBrightness((mMaximumBrightness - mMinimumBrightness) * fraction + mMinimumBrightness);
}