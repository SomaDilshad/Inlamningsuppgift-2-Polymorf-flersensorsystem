#include "sensor.h"
#include <random>
#include <chrono>
#include <sstream>
#include <iomanip>

//=== TemperatureSensor Implementation ===
TemperatureSensor::TemperatureSensor(std::string id, double minVal, double maxVal)
    : id_(id), minVal_(minVal), maxVal_(maxVal) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    gen_.seed(seed);
    dist_ = std::uniform_real_distribution<double>(minVal_, maxVal_);
}

double TemperatureSensor::read() {
    return dist_(gen_);
}

std::string TemperatureSensor::name() const {
    return id_;
}

std::string TemperatureSensor::unit() const {
    return "°C";
}

std::string TemperatureSensor::sensorInfo() const {
    std::ostringstream oss;
    oss << name() << " - Temperature sensor (" << unit() << "), Range: " 
        << minVal_ << " to " << maxVal_;
    return oss.str();
}

//=== HumiditySensor Implementation ===
HumiditySensor::HumiditySensor(std::string id, double minVal, double maxVal)
    : id_(id), minVal_(minVal), maxVal_(maxVal) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    gen_.seed(seed);
    dist_ = std::uniform_real_distribution<double>(minVal_, maxVal_);
}

double HumiditySensor::read() {
    return dist_(gen_);
}

std::string HumiditySensor::name() const {
    return id_;
}

std::string HumiditySensor::unit() const {
    return "%";
}

std::string HumiditySensor::sensorInfo() const {
    std::ostringstream oss;
    oss << name() << " - Humidity sensor (" << unit() << "), Range: " 
        << minVal_ << " to " << maxVal_;
    return oss.str();
}

//=== PressureSensor Implementation ===
PressureSensor::PressureSensor(std::string id, double minVal, double maxVal)
    : id_(id), minVal_(minVal), maxVal_(maxVal) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    gen_.seed(seed);
    dist_ = std::uniform_real_distribution<double>(minVal_, maxVal_);
}

double PressureSensor::read() {
    return dist_(gen_);
}

std::string PressureSensor::name() const {
    return id_;
}

std::string PressureSensor::unit() const {
    return "hPa";
}

std::string PressureSensor::sensorInfo() const {
    std::ostringstream oss;
    oss << name() << " - Pressure sensor (" << unit() << "), Range: " 
        << minVal_ << " to " << maxVal_;
    return oss.str();
}
