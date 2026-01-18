#ifndef SENSOR_H
#define SENSOR_H

#include <string>
#include <memory>
#include <random>

// Abstrakt basklass för alla sensorer
class Sensor {
public:
    virtual ~Sensor() = default;  // Virtuell destruktor
    
    // Ren virtuell funktioner - måste implementeras i subklasser
    virtual double read() = 0;
    virtual std::string name() const = 0;
    virtual std::string unit() const = 0;
    
    // Virtuell funktion för sensor-specifik information (kan överridas)
    virtual std::string sensorInfo() const {
        return name() + " (" + unit() + ")";
    }
};

// Temperatursensor
class TemperatureSensor : public Sensor {
private:
    std::string id_;
    double minVal_, maxVal_;
    mutable std::mt19937 gen_;
    mutable std::uniform_real_distribution<double> dist_;
    
public:
    TemperatureSensor(std::string id, double minVal = 15.0, double maxVal = 30.0);
    double read() override;
    std::string name() const override;
    std::string unit() const override;
    std::string sensorInfo() const override;
};

// Luftfuktighetssensor
class HumiditySensor : public Sensor {
private:
    std::string id_;
    double minVal_, maxVal_;
    mutable std::mt19937 gen_;
    mutable std::uniform_real_distribution<double> dist_;
    
public:
    HumiditySensor(std::string id, double minVal = 30.0, double maxVal = 80.0);
    double read() override;
    std::string name() const override;
    std::string unit() const override;
    std::string sensorInfo() const override;
};

// Trycksensor
class PressureSensor : public Sensor {
private:
    std::string id_;
    double minVal_, maxVal_;
    mutable std::mt19937 gen_;
    mutable std::uniform_real_distribution<double> dist_;
    
public:
    PressureSensor(std::string id, double minVal = 980.0, double maxVal = 1050.0);
    double read() override;
    std::string name() const override;
    std::string unit() const override;
    std::string sensorInfo() const override;
};

#endif
