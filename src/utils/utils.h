//
// Created by arunc on 29/09/2024.
//

#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <chrono>
#include <sstream>
#include <iomanip>

class Utils {
public:
    static std::string generateUniqueID() {
        auto now = std::chrono::system_clock::now();
        auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
        auto value = now_ms.time_since_epoch();
        long duration = value.count();
        std::stringstream ss;
        ss << std::hex << duration;
        return ss.str();
    }


};



#endif //UTILS_H
