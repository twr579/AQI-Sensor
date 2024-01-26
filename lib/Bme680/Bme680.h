/**
 * BME680.h - BME680 class definition
 */

#include "bsec.h"
#include "AbstractSensor.hpp"

struct BME680Data
{
    float iaq;
    float co2;
    float voc;
    float pressure;
    float temperature;
    float humidity;
};

/**
 * Initialize, run, and store data for the BME680 sensor
 */
class BME680 : public AbstractSensor<BME680Data>
{
public:
    // Initialize the BME680
    void begin();

    // Run the BME680
    void run();

private:
    // Bsec object for collecting data from the sensor
    Bsec bsec;

    // Check if the bsec object has any error or warning codes
    void checkStatus();
};