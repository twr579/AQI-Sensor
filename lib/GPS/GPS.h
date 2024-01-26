/**
 * GPS.h - GPS class definition
 */

#include <TinyGPS++.h>
#include "AbstractSensor.hpp"

struct GPSData
{
    double lat;
    double lng;
};

/**
 * Initialize, run, and store data for the NEO-6M GPS module
 */
class GPS : public AbstractSensor<GPSData>
{
public:
    // Initialize the GPS
    void begin();

    // Run the GPS
    void run();

private:
    // TinyGPSPlus object for collecting data from the GPS module
    TinyGPSPlus gps;

    // Check if the GPS is connected
    void checkStatus();
};