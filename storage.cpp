#include "storage.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <cmath>

void MeasurementStorage::läggTillMätning(const Measurement& m) {
    measurements.push_back(m);
}

void MeasurementStorage::visaAllaMätningar() const {
    if (measurements.empty()) {
        std::cout << "No measurements available.\n";
        return;
    }
    
    std::cout << "\n=== ALL MEASUREMENTS ===\n";
    for (const auto& m : measurements) {
        std::cout << m.timestamp << " - " << m.sensorName 
                  << ": " << std::fixed << std::setprecision(2) 
                  << m.value << " " << m.unit << "\n";
    }
    std::cout << "Total: " << measurements.size() << " measurements\n";
}

void MeasurementStorage::visaStatistikPerSensor() const {
    if (measurements.empty()) {
        std::cout << "No measurements available.\n";
        return;
    }
    
    // Gruppera mätningar per sensor
    std::vector<std::string> sensorNames;
    for (const auto& m : measurements) {
        if (std::find(sensorNames.begin(), sensorNames.end(), m.sensorName) == sensorNames.end()) {
            sensorNames.push_back(m.sensorName);
        }
    }
    
    std::cout << "\n=== STATISTICS PER SENSOR ===\n";
    for (const auto& sensorName : sensorNames) {
        visaStatistikFörSensor(sensorName);
    }
}

void MeasurementStorage::visaStatistikFörSensor(const std::string& sensorName) const {
    std::vector<double> values;
    std::string unit;
    
    for (const auto& m : measurements) {
        if (m.sensorName == sensorName) {
            values.push_back(m.value);
            unit = m.unit;
        }
    }
    
    if (values.empty()) {
        std::cout << "No measurements found for sensor: " << sensorName << "\n";
        return;
    }
    
    // Beräkna statistik
    double sum = std::accumulate(values.begin(), values.end(), 0.0);
    double mean = sum / values.size();
    
    std::sort(values.begin(), values.end());
    double min = values.front();
    double max = values.back();
    double median = values.size() % 2 == 0 
        ? (values[values.size()/2 - 1] + values[values.size()/2]) / 2.0
        : values[values.size()/2];
    
    // Standardavvikelse
    double variance = 0.0;
    for (double v : values) {
        variance += (v - mean) * (v - mean);
    }
    variance /= values.size();
    double stdDev = std::sqrt(variance);
    
    std::cout << "\n--- " << sensorName << " (" << unit << ") ---\n";
    std::cout << "Count: " << values.size() << "\n";
    std::cout << "Min: " << std::fixed << std::setprecision(2) << min << "\n";
    std::cout << "Max: " << std::fixed << std::setprecision(2) << max << "\n";
    std::cout << "Mean: " << std::fixed << std::setprecision(2) << mean << "\n";
    std::cout << "Median: " << std::fixed << std::setprecision(2) << median << "\n";
    std::cout << "Std Dev: " << std::fixed << std::setprecision(2) << stdDev << "\n";
}

bool MeasurementStorage::sparaTillFil(const std::string& path) const {
    std::ofstream file(path);
    if (!file.is_open()) {
        std::cout << "Error: Could not open file for writing: " << path << "\n";
        return false;
    }
    
    // Skriv CSV-huvud
    file << "timestamp,sensorName,value,unit\n";
    
    for (const auto& m : measurements) {
        file << m.timestamp << "," << m.sensorName << "," 
             << std::fixed << std::setprecision(2) << m.value 
             << "," << m.unit << "\n";
    }
    
    file.close();
    std::cout << "Saved " << measurements.size() << " measurements to " << path << "\n";
    return true;
}

bool MeasurementStorage::laddaFrånFil(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cout << "Error: Could not open file for reading: " << path << "\n";
        return false;
    }
    
    std::string line;
    bool firstLine = true;
    int loaded = 0;
    
    while (std::getline(file, line)) {
        if (firstLine) {
            firstLine = false;
            continue; // Skip header
        }
        
        if (line.empty()) continue;
        
        std::istringstream iss(line);
        std::string timestamp, sensorName, valueStr, unit;
        
        if (std::getline(iss, timestamp, ',') &&
            std::getline(iss, sensorName, ',') &&
            std::getline(iss, valueStr, ',') &&
            std::getline(iss, unit)) {
            
            try {
                double value = std::stod(valueStr);
                Measurement m(sensorName, unit, value);
                m.timestamp = timestamp; // Använd tidsstämpel från fil
                measurements.push_back(m);
                loaded++;
            } catch (...) {
                // Ignorera felaktiga rader
            }
        }
    }
    
    file.close();
    std::cout << "Loaded " << loaded << " measurements from " << path << "\n";
    return true;
}

void MeasurementStorage::rensAllaMätningar() {
    measurements.clear();
}
