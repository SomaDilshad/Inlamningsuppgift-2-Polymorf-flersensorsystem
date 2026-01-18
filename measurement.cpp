#include "measurement.h"
#include "utils.h"

Measurement::Measurement(const std::string& name, const std::string& unit, double val)
    : sensorName(name), unit(unit), value(val), timestamp(Utils::nuvarandeTidsstämpel()) {}
