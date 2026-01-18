- Multi-Sensor System with Polymorphism and Inheritance
- Inlämningsuppgift 2 - Flersensorsystem med arv och UML
https://github.com/SomaDilshad/Inlamningsuppgift-2-Polymorf-flersensorsystem.git

- Projektöversikt
Detta projekt bygger vidare på flersensorsystemet från Inlämningsuppgift 1 med införande av arv, polymorfism och tröskelbaserade larm. Systemet använder nu en abstrakt basklass för sensorer med tre konkreta implementationer och implementerar en fullständig larmfunktionalitet.

- Uppfyllda Krav

- 1. Arv och Polymorfism 
- Abstrakt basklass `Sensor` med virtuell destruktor och ren virtuell metod `read()`
- Tre konkreta subklasser:
  - `TemperatureSensor` - simulerar temperaturvärden (15.0-30.0°C)
  - `HumiditySensor` - simulerar luftfuktighet (30.0-80.0%)
  - `PressureSensor` - simulerar tryck (980.0-1050.0 hPa)
- Polymorf lagring: `std::vector<std::unique_ptr<Sensor>>`
- Polymorfa anrop: All provtagning sker via basklasspekare

- 2. Tröskelbaserat Larm 
- Konfigurerbara trösklar per sensor (övre/nedre gräns)
- Automatisk larmdetektering vid varje provtagning
- Larmhistorik med tidsstämplar och detaljer
- Separat larmhantering från mätvärdeslagring

 3. Integration med Befintlig Funktion 
- Filhantering från INL1 fungerar fortsatt (CSV-format)
- Statistikberäkningar arbetar med polymorfa sensorer
- Utökad meny med nya larmfunktioner
- Bakåtkompatibilitet med INL1 datafiler

- 4. UML Klassdiagram 
- Komplett diagram som visar arvshierarkin
- Associationer och kompositioner mellan klasser
- Viktiga metoder och attribut dokumenterade

- Systemarkitektur

- Klassdesign
```
Sensor (Abstract)
├── TemperatureSensor
├── HumiditySensor
└── PressureSensor
```

- Nyckelkomponenter
1. SystemController - Huvudstyrenhet som samordnar all funktionalitet
2. ThresholdManager - Hanterar tröskelregler och larm
3. MeasurementStorage - Lagring och analys av mätdata (ärvt från INL1)

- Kompilering och Körning

```bash
- Kompilera
make

- Kör programmet
./sensorsystem_inl2

- Alternativ kompilering
g++ -std=c++17 -o sensorsystem_inl2 *.cpp
```

- Användargränssnitt

- Huvudmeny
```
=== MAIN MENU ===
1. List all sensors
2. Take single sample from all sensors
3. Take multiple samples
4. Show all measurements
5. Statistics
6. File operations
7. Clear all data
8. Configure threshold (NEW)
9. Show configured thresholds (NEW)
10. Show alerts (NEW)
11. Clear alerts (NEW)
0. Exit
```

- Ny Funktion: Tröskelkonfiguration
1. Välj menyval 8 för att konfigurera tröskel
2. Välj sensor från listan
3. Ange tröskelvärde
4. Välj om larm ska utlösas över eller under tröskeln
5. Vid provtagning visas automatiskt larm vid överträdelse

- Testinstruktioner

- Test 1: Verifiera Polymorfism
```bash
1. Starta programmet
2. Välj 1: Lista sensorer (visar olika sensortyper)
3. Välj 2: Ta prov (anropar read() polymorft)
```

- Test 2: Testa Larmfunktion
```bash
1. Välj 8: Konfigurera tröskel för TempSensor1
2. Sätt tröskel till 25.0 (övre gräns)
3. Välj 2 eller 3: Ta flera prover
4. Välj 10: Visa larm (visar överträdelser)
```

- Test 3: Filhantering
```bash
1. Ta några prover
2. Välj 6 → 1: Spara till "test.csv"
3. Välj 7: Rensa data
4. Välj 6 → 2: Ladda från "test.csv"
5. Välj 4: Verifiera att data laddats
```

- Tekniska Implementationer

- Polymorf Lagring
```cpp
std::vector<std::unique_ptr<Sensor>> sensors;
sensors.push_back(std::make_unique<TemperatureSensor>("Temp1"));
sensors.push_back(std::make_unique<HumiditySensor>("Hum1"));
// Alla lagras som Sensor-pekare
```

- Tröskeldetektering
```cpp
bool ThresholdManager::checkValue(const string& sensorName, double value) {
    for (const auto& threshold : thresholds) {
        if (threshold.sensorName == sensorName) {
            if ((threshold.isOver && value > threshold.limit) ||
                (!threshold.isOver && value < threshold.limit)) {
                // Skapa larm
                return true;
            }
        }
    }
    return false;
}
```

- Filstruktur
```
projekt/
├── main.cpp                 - Huvudprogram med meny
├── sensor.h/cpp             - Arvshierarki (UPPDATERAD)
├── measurement.h/cpp        - Mätvärdesstruktur
├── storage.h/cpp            - Datalagring (från INL1)
├── utils.h/cpp              - Hjälpfunktioner
├── threshold.h/cpp          - NY: Tröskel- och larmhantering
├── systemcontroller.h/cpp   - NY: Systemstyrenhet
├── Makefile                 - Byggkonfiguration
├── README.md                - Denna dokumentation
└── UML_Diagram.png         - Klassdiagram
```

- Alla Kurskrav Uppfyllda

- För Godkänt (G):
-  Abstrakt Sensor med virtuell destruktor och `read()`
-  Minst tre konkreta subklasser med `override`
-  Polymorf lagring och anrop
-  Tröskelbaserat larm implementerat
-  UML-diagram motsvarar implementation
-  Koden kompilerar och körs
-  .h/.cpp-indelning med smarta pekare

- Ytterligare (från INL1 för VG):
-  Tidsstämplar med aktuell systemtid
-  Tröskelvärdesanalys (utökad i denna uppgift)
-  Filhantering med CSV-format





