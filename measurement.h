#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include <string>

class Measurement {
public:
    std::string sensorName;
    std::string unit;
    double value;
    std::string timestamp;
    
    Measurement(const std::string& name, const std::string& unit, double val);
};

#endif
