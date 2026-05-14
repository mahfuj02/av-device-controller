// alert.cpp
// Implementation of Alert. One method body — tiny on purpose.

#include "alert.h"
#include <iostream>

Alert::Alert(float threshold) : threshold(threshold) {}

void Alert::check(const std::vector<Display>& displays) {
    for (const auto& d : displays) {
        if (d.getTemperature() > threshold) {
            std::cout << "[ALERT] Display " << d.getId()
                      << " temperature critical: " << d.getTemperature() << "C\n";
        }
    }
}