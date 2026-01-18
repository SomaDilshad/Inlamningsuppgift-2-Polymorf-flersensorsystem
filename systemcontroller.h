#ifndef SYSTEMCONTROLLER_H
#define SYSTEMCONTROLLER_H

#include <memory>
#include <vector>
#include <string>
#include "sensor.h"
#include "storage.h"
#include "threshold.h"

class SystemController {
private:
    std::vector<std::unique_ptr<Sensor>> sensors;
    MeasurementStorage storage;
    ThresholdManager thresholdManager;
    
public:
    SystemController();
    
    // Sensor management
    void addSensor(std::unique_ptr<Sensor> sensor);
    void createDefaultSensors();
    void listAllSensors() const;
    
    // Sampling and measurements
    void sampleAllOnce();  // Läser alla sensorer en gång
    void sampleMultipleTimes(int count);
    
    // Statistics and display
    void showAllMeasurements() const;
    void showStatistics() const;
    void showSensorStatistics(const std::string& sensorName) const;
    
    // Threshold and alerts
    void configureThreshold();  // Frågar användaren
    void showAlerts() const;
    void showThresholds() const;
    void clearAlerts();
    
    // File operations
    bool saveToFile(const std::string& path) const;
    bool loadFromFile(const std::string& path);
    void clearAllData();
    
    // Utility
    std::vector<std::string> getSensorNames() const;
    
private:
    void createMeasurement(const Sensor& sensor, double value);
};

#endif
