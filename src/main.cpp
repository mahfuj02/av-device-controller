// main.cpp — Day 2 sanity check for the Display class.
// Goal: prove that we can construct a Display, mutate it through setters,
// read its state through getters, and that bad inputs are rejected cleanly.

#include "display.h"
#include <iostream>

int main() {
    std::cout << "AV Device Controller v1.0\n\n";

    // 1. Build a Display. Defaults come from the constructor in display.cpp:
    //    power off, vol 50, brightness 80, input HDMI, temp 35C.
    Display d(1, "MainBar");
    std::cout << "Initial state:\n  " << d.getStatus() << "\n\n";

    // 2. Drive it through valid setters. Each call mutates one field;
    //    everything else stays the same — that's encapsulation working.
    d.setPower(true);
    d.setVolume(60);
    d.setInput("AV");
    std::cout << "After setPower(true), setVolume(60), setInput(\"AV\"):\n  "
              << d.getStatus() << "\n\n";

    // 3. Try invalid inputs. The setters throw std::invalid_argument;
    //    we catch and print so the program keeps running instead of crashing.
    std::cout << "Testing invalid inputs (these should be rejected):\n";

    try {
        d.setVolume(150);                       // out of range — should throw
    } catch (const std::exception& e) {
        std::cout << "  [ERROR] " << e.what() << "\n";
    }

    try {
        d.setBrightness(-10);                   // out of range — should throw
    } catch (const std::exception& e) {
        std::cout << "  [ERROR] " << e.what() << "\n";
    }

    try {
        d.setInput("VGA");                      // not HDMI/AV/DP — should throw
    } catch (const std::exception& e) {
        std::cout << "  [ERROR] " << e.what() << "\n";
    }

    // 4. After the failed calls, the Display state should be unchanged.
    //    If the throw worked correctly, volume is still 60, brightness 80, input AV.
    std::cout << "\nState after rejected inputs (should match step 2):\n  "
              << d.getStatus() << "\n";

    return 0;
}
