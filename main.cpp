#include <iostream>
#include <memory>
#include "systemcontroller.h"
#include "utils.h"

// Funktionsdeklarationer
void displayMainMenu();
void handleFileOperations(SystemController& controller);
void handleStatistics(SystemController& controller);

int main() {
    std::cout << "=== MULTI-SENSOR SYSTEM WITH POLYMORPHISM ===\n";
    std::cout << "Inheritance and Threshold-based Alerts\n\n";
    
    SystemController controller;
    
    int choice;
    do {
        displayMainMenu();
        choice = Utils::hämtaIntegerInput("Enter your choice: ");
        
        switch (choice) {
            case 1:
                controller.listAllSensors();
                break;
            case 2:
                controller.sampleAllOnce();
                break;
            case 3: {
                int count = Utils::hämtaIntegerInput("Number of samples to take: ");
                controller.sampleMultipleTimes(count);
                break;
            }
            case 4:
                controller.showAllMeasurements();
                break;
            case 5:
                handleStatistics(controller);
                break;
            case 6:
                handleFileOperations(controller);
                break;
            case 7:
                controller.clearAllData();
                break;
            case 8:
                controller.configureThreshold();
                break;
            case 9:
                controller.showThresholds();
                break;
            case 10:
                controller.showAlerts();
                break;
            case 11:
                controller.clearAlerts();
                break;
            case 0:
                std::cout << "Exiting program...\n";
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
        
        if (choice != 0) {
            std::cout << "\nPress Enter to continue...";
            std::cin.get();
        }
        
    } while (choice != 0);
    
    return 0;
}

void displayMainMenu() {
    std::cout << "\n=== MAIN MENU ===\n";
    std::cout << "1. List all sensors\n";
    std::cout << "2. Take single sample from all sensors\n";
    std::cout << "3. Take multiple samples\n";
    std::cout << "4. Show all measurements\n";
    std::cout << "5. Statistics\n";
    std::cout << "6. File operations\n";
    std::cout << "7. Clear all data\n";
    std::cout << "8. Configure threshold (NEW)\n";
    std::cout << "9. Show configured thresholds (NEW)\n";
    std::cout << "10. Show alerts (NEW)\n";
    std::cout << "11. Clear alerts (NEW)\n";
    std::cout << "0. Exit\n";
}

void handleFileOperations(SystemController& controller) {
    std::cout << "\n1. Save to file\n";
    std::cout << "2. Load from file\n";
    
    int choice = Utils::hämtaIntegerInput("Choose: ");
    std::string filename;
    
    std::cout << "Enter filename: ";
    std::getline(std::cin, filename);
    
    if (choice == 1) {
        controller.saveToFile(filename);
    } else if (choice == 2) {
        controller.loadFromFile(filename);
    } else {
        std::cout << "Invalid choice.\n";
    }
}

void handleStatistics(SystemController& controller) {
    std::cout << "\n1. Statistics for all sensors\n";
    std::cout << "2. Statistics for specific sensor\n";
    
    int choice = Utils::hämtaIntegerInput("Choose: ");
    
    if (choice == 1) {
        controller.showStatistics();
    } else if (choice == 2) {
        std::string sensorName;
        std::cout << "Enter sensor name: ";
        std::getline(std::cin, sensorName);
        controller.showSensorStatistics(sensorName);
    } else {
        std::cout << "Invalid choice.\n";
    }
}
