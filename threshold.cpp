#include "threshold.h"
#include "utils.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>

Alert::Alert(const std::string& name, double value, double thresh, bool over)
    : sensorName(name), measuredValue(value), threshold(thresh), 
      isOver(over), timestamp(Utils::nuvarandeTidsstämpel()) {}

std::string Alert::toString() const {
    std::ostringstream oss;
    oss << timestamp << " - " << sensorName << ": " 
        << std::fixed << std::setprecision(2) << measuredValue
        << " is " << (isOver ? "ABOVE" : "BELOW") 
        << " threshold " << threshold;
    return oss.str();
}

void ThresholdManager::addThreshold(const std::string& sensorName, double limit, bool isOver) {
    thresholds.emplace_back(sensorName, limit, isOver);
}

bool ThresholdManager::checkValue(const std::string& sensorName, double value) {
    bool triggered = false;
    
    for (const auto& threshold : thresholds) {
        if (threshold.sensorName == sensorName) {
            if ((threshold.isOver && value > threshold.limit) ||
                (!threshold.isOver && value < threshold.limit)) {
                alerts.emplace_back(sensorName, value, threshold.limit, threshold.isOver);
                triggered = true;
            }
        }
    }
    
    return triggered;
}

void ThresholdManager::showAlerts() const {
    if (alerts.empty()) {
        std::cout << "No alerts registered.\n";
        return;
    }
    
    std::cout << "\n=== ALERTS ===\n";
    for (const auto& alert : alerts) {
        std::cout << alert.toString() << "\n";
    }
    std::cout << "Total alerts: " << alerts.size() << "\n";
}

void ThresholdManager::clearAlerts() {
    alerts.clear();
    std::cout << "All alerts cleared.\n";
}

std::vector<Threshold> ThresholdManager::getThresholdsForSensor(const std::string& sensorName) const {
    std::vector<Threshold> result;
    for (const auto& th : thresholds) {
        if (th.sensorName == sensorName) {
            result.push_back(th);
        }
    }
    return result;
}

void ThresholdManager::removeThreshold(const std::string& sensorName) {
    thresholds.erase(
        std::remove_if(thresholds.begin(), thresholds.end(),
            [&sensorName](const Threshold& th) {
                return th.sensorName == sensorName;
            }),
        thresholds.end()
    );
}

void ThresholdManager::showThresholds() const {
    if (thresholds.empty()) {
        std::cout << "No thresholds configured.\n";
        return;
    }
    
    std::cout << "\n=== CONFIGURED THRESHOLDS ===\n";
    for (const auto& th : thresholds) {
        std::cout << th.sensorName << ": " 
                  << (th.isOver ? "ALERT if > " : "ALERT if < ") 
                  << std::fixed << std::setprecision(2) << th.limit << "\n";
    }
}
