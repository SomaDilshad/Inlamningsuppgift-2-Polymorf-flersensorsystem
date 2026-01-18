#include "systemcontroller.h"
#include "measurement.h"
#include "utils.h"
#include <iostream>
#include <memory>
#include <iomanip>

SystemController::SystemController() {
    createDefaultSensors();
}

void SystemController::addSensor(std::unique_ptr<Sensor> sensor) {
    sensors.push_back(std::move(sensor));
}

void SystemController::createDefaultSensors() {
    sensors.push_back(std::make_unique<TemperatureSensor>("TempSensor1"));
    sensors.push_back(std::make_unique<HumiditySensor>("HumiditySensor1"));
    sensors.push_back(std::make_unique<PressureSensor>("PressureSensor1"));
}

void SystemController::listAllSensors() const {
    std::cout << "\n=== REGISTERED SENSORS ===\n";
    for (const auto& sensor : sensors) {
        std::cout << "- " << sensor->sensorInfo() << "\n";
    }
}

void SystemController::sampleAllOnce() {
    std::cout << "\n=== SAMPLING ALL SENSORS ===\n";
    for (const auto& sensor : sensors) {
        double value = sensor->read();  // Polymorfiskt anrop!
        createMeasurement(*sensor, value);
        
        // Kontrollera trösklar
        if (thresholdManager.checkValue(sensor->name(), value)) {
            std::cout << "   [ALERT] " << sensor->name() 
                      << " triggered threshold!\n";
        }
    }
    std::cout << "Sampling completed.\n";
}

void SystemController::sampleMultipleTimes(int count) {
    std::cout << "\n=== SAMPLING " << count << " TIMES ===\n";
    for (int i = 0; i < count; i++) {
        std::cout << "Sample " << (i + 1) << ":\n";
        sampleAllOnce();
        std::cout << "---\n";
    }
}

void SystemController::createMeasurement(const Sensor& sensor, double value) {
    Measurement measurement(sensor.name(), sensor.unit(), value);
    storage.läggTillMätning(measurement);
    
    std::cout << "   " << sensor.name() << ": " 
              << std::fixed << std::setprecision(2) << value 
              << " " << sensor.unit() << "\n";
}

void SystemController::showAllMeasurements() const {
    storage.visaAllaMätningar();
}

void SystemController::showStatistics() const {
    storage.visaStatistikPerSensor();
}

void SystemController::showSensorStatistics(const std::string& sensorName) const {
    storage.visaStatistikFörSensor(sensorName);
}

void SystemController::configureThreshold() {
    std::cout << "\n=== CONFIGURE THRESHOLD ===\n";
    
    if (sensors.empty()) {
        std::cout << "No sensors available.\n";
        return;
    }
    
    // Visa tillgängliga sensorer
    std::cout << "Available sensors:\n";
    for (size_t i = 0; i < sensors.size(); i++) {
        std::cout << i + 1 << ". " << sensors[i]->name() << "\n";
    }
    
    int sensorChoice = Utils::hämtaIntegerInput("Select sensor (1-" + 
                                               std::to_string(sensors.size()) + "): ");
    if (sensorChoice < 1 || sensorChoice > static_cast<int>(sensors.size())) {
        std::cout << "Invalid choice.\n";
        return;
    }
    
    std::string sensorName = sensors[sensorChoice - 1]->name();
    
    // Ta bort gamla trösklar för denna sensor
    thresholdManager.removeThreshold(sensorName);
    
    double limit = Utils::hämtaDoubleInput("Enter threshold value: ");
    
    std::cout << "1. Alert when value is OVER threshold\n";
    std::cout << "2. Alert when value is UNDER threshold\n";
    int typeChoice = Utils::hämtaIntegerInput("Select alert type: ");
    
    bool isOver = (typeChoice == 1);
    thresholdManager.addThreshold(sensorName, limit, isOver);
    
    std::cout << "Threshold configured for " << sensorName 
              << ": Alert when value is " << (isOver ? "OVER " : "UNDER ") 
              << limit << "\n";
}

void SystemController::showAlerts() const {
    thresholdManager.showAlerts();
}

void SystemController::showThresholds() const {
    thresholdManager.showThresholds();
}

void SystemController::clearAlerts() {
    thresholdManager.clearAlerts();
}

bool SystemController::saveToFile(const std::string& path) const {
    return storage.sparaTillFil(path);
}

bool SystemController::loadFromFile(const std::string& path) {
    return storage.laddaFrånFil(path);
}

void SystemController::clearAllData() {
    storage.rensAllaMätningar();
    std::cout << "All measurement data cleared.\n";
}

std::vector<std::string> SystemController::getSensorNames() const {
    std::vector<std::string> names;
    for (const auto& sensor : sensors) {
        names.push_back(sensor->name());
    }
    return names;
}
