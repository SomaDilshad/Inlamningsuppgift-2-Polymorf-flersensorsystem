#include "utils.h"
#include <iostream>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <limits>

std::string Utils::nuvarandeTidsstämpel() {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()) % 1000;
    
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
    oss << "." << std::setfill('0') << std::setw(3) << ms.count();
    return oss.str();
}

int Utils::hämtaIntegerInput(const std::string& prompt) {
    int value;
    std::cout << prompt;
    
    while (!(std::cin >> value)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter an integer: ";
    }
    std::cin.ignore(); // Ignorera newline
    
    return value;
}

double Utils::hämtaDoubleInput(const std::string& prompt) {
    double value;
    std::cout << prompt;
    
    while (!(std::cin >> value)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a number: ";
    }
    std::cin.ignore(); // Ignorera newline
    
    return value;
}
