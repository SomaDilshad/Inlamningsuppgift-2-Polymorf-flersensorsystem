#ifndef STORAGE_H
#define STORAGE_H

#include <vector>
#include <string>
#include "measurement.h"

class MeasurementStorage {
private:
    std::vector<Measurement> measurements;
    
public:
    void läggTillMätning(const Measurement& m);
    void visaAllaMätningar() const;
    void visaStatistikPerSensor() const;
    void visaStatistikFörSensor(const std::string& sensorName) const;
    bool sparaTillFil(const std::string& path) const;
    bool laddaFrånFil(const std::string& path);
    void rensAllaMätningar();
};

#endif
