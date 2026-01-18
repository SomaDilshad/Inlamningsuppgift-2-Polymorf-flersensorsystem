#ifndef THRESHOLD_H
#define THRESHOLD_H

#include <string>
#include <vector>

// Struktur för tröskelregler
struct Threshold {
    std::string sensorName;
    double limit;
    bool isOver;  // true: larma om värde > limit, false: larma om värde < limit
    
    Threshold(const std::string& name, double lim, bool over)
        : sensorName(name), limit(lim), isOver(over) {}
};

// Struktur för larm
struct Alert {
    std::string sensorName;
    double measuredValue;
    double threshold;
    bool isOver;  // true: värde över tröskel, false: värde under tröskel
    std::string timestamp;
    
    Alert(const std::string& name, double value, double thresh, bool over);
    std::string toString() const;
};

// Klass för att hantera trösklar och larm
class ThresholdManager {
private:
    std::vector<Threshold> thresholds;
    std::vector<Alert> alerts;
    
public:
    // Lägg till tröskelregel
    void addThreshold(const std::string& sensorName, double limit, bool isOver);
    
    // Kontrollera om ett värde utlöser larm
    bool checkValue(const std::string& sensorName, double value);
    
    // Visa alla aktiva larm
    void showAlerts() const;
    
    // Rensa alla larm
    void clearAlerts();
    
    // Hämta tröskel för en sensor
    std::vector<Threshold> getThresholdsForSensor(const std::string& sensorName) const;
    
    // Ta bort tröskel för sensor
    void removeThreshold(const std::string& sensorName);
    
    // Visa alla tröskelregler
    void showThresholds() const;
};

#endif
