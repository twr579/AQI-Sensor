/**
 * AbstractSensor.hpp - AbstractSensor class definition
 */

#pragma once

/**
 * Abstract class for initializing and running a sensor, and storing sensor data for later retrieval.
 *
 * @tparam T the type of data stored by the sensor
 */
template <typename T>
class AbstractSensor
{
public:
    // Initialize the sensor
    virtual void begin() = 0;

    // Run the sensor
    virtual void run() = 0;

    // Get stored sensor data
    T getData();

    // Check if data is valid and ready to publish
    bool isValid();

    // Clear valid flag, invalidating old sensor data
    void clear();

protected:
    // Set sensor data
    void setData(T newData);

private:
    // Sensor data
    T data;

    // Flag that determines whether or not data is valid and ready to publish
    bool valid;

    // Check if the sensor is connected and running properly
    virtual void checkStatus() = 0;
};

template <typename T>
T AbstractSensor<T>::getData() { return data; }

template <typename T>
void AbstractSensor<T>::setData(T newData)
{
    data = newData;
    valid = true;
}

template <typename T>
void AbstractSensor<T>::clear() { valid = false; }

template <typename T>
bool AbstractSensor<T>::isValid() { return valid; }