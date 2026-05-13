// alert.h
// Scans displays for over-temperature conditions and prints a warning
// to stdout for each offender. Stateless aside from the threshold.

#pragma once

#include "display.h"
#include <vector>

class Alert {
public:
    // Default threshold matches Display::getStatus()'s WARNING line.
    Alert(float threshold = 36.0f);

    // Examine every display; print an [ALERT] line for each one over
    // the threshold. const-ref so we can't accidentally mutate displays.
    void check(const std::vector<Display>& displays);

private:
    float threshold;
};