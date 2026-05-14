// display.cpp
// Implementation of the Display class declared in include/display.h
// (see that header for the public interface)

#include "display.h"

#include <cstdlib>   // rand() — used by simulateTemperature()
#include <sstream>   // std::ostringstream — string builder for getStatus()
#include <stdexcept> // std::invalid_argument — thrown on bad inputs

// ---- Constructor ----
// The ": id(id), name(name), power(false), ..." part is a "member initializer list".
// It initializes each field directly, which is faster than assigning inside the body
// and is the only way to initialize const or reference members.
Display::Display(int id, const std::string& name)
    : id(id), name(name), power(false), volume(50), brightness(80), input("HDMI"),
      temperature(35.0f) {}

// ---- Setters ----

void Display::setPower(bool on) { power = on; }

void Display::setVolume(int level) {
    if (level < 0 || level > 100)
        throw std::invalid_argument("Volume must be 0-100");
    volume = level;
}

void Display::setBrightness(int level) {
    if (level < 0 || level > 100)
        throw std::invalid_argument("Brightness must be 0-100");
    brightness = level;
}

void Display::setInput(const std::string& inp) {
    if (inp != "HDMI" && inp != "AV" && inp != "DP")
        throw std::invalid_argument("Input must be HDMI, AV, or DP");
    input = inp;
}

void Display::simulateTemperature() {
    // Random delta in the range -0.5 .. +0.5 degrees per call.
    // rand() % 11 -> 0..10  ;  -5 -> -5..5  ;  * 0.1 -> -0.5..0.5
    float delta = (rand() % 11 - 5) * 0.1f;
    temperature += delta;

    // Clamp so the value stays inside a believable physical range.
    if (temperature < 30.0f)
        temperature = 30.0f;
    if (temperature > 75.0f)
        temperature = 75.0f;
}

// ---- Getters ----
// All marked const — they read state but never modify it.

int Display::getId() const { return id; }
std::string Display::getName() const { return name; }
bool Display::isPoweredOn() const { return power; }
int Display::getVolume() const { return volume; }
int Display::getBrightness() const { return brightness; }
std::string Display::getInput() const { return input; }
float Display::getTemperature() const { return temperature; }

// One-line human-readable status string.
// Built with ostringstream so we can chain values of different types
// with << and convert to a string at the end.
std::string Display::getStatus() const {
    std::ostringstream ss;
    ss << "[Display " << id << " | " << name << "] ";
    ss << "Power: " << (power ? "ON" : "OFF");
    ss << " | Input: " << input;
    ss << " | Vol: " << volume << "%";
    ss << " | Bright: " << brightness << "%";
    ss << " | Temp: " << temperature << "C";
    if (temperature > 60.0f)
        ss << "  WARNING: HIGH TEMP";
    return ss.str();
}
