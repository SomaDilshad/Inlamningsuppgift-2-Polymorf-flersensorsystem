#ifndef UTILS_H
#define UTILS_H

#include <string>

class Utils {
public:
    static std::string nuvarandeTidsstämpel();
    static int hämtaIntegerInput(const std::string& prompt);
    static double hämtaDoubleInput(const std::string& prompt);
};

#endif
