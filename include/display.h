// display.h
// Blueprint for a single display (TV/screen) in the venue.
// Every TV in the system is represented in memory by one instance of this class.

#pragma once // include this header at most once per translation unit

#include <string>

class Display {
  public:
    // ---- Constructor ----
    // Build a Display with a numeric ID and a human-readable name.
    // Defaults are set in the .cpp file (power off, vol 50, HDMI, 35C, etc.)
    Display(int id, const std::string& name);

    // ---- Setters: change the state of this display ----
    void setPower(bool on);                  // turn this display on/off
    void setVolume(int level);               // 0..100 ; throws if out of range
    void setBrightness(int level);           // 0..100 ; throws if out of range
    void setInput(const std::string& input); // "HDMI" | "AV" | "DP" ; throws otherwise
    void simulateTemperature();              // nudge temperature by a random delta

    // ---- Getters: read the current state (no mutation, hence trailing const) ----
    int getId() const;
    std::string getName() const;
    bool isPoweredOn() const;
    int getVolume() const;
    int getBrightness() const;
    std::string getInput() const;
    float getTemperature() const;

    // One-line human-readable summary — used by the STATUS command.
    std::string getStatus() const;

  private:
    // ---- Internal state ----
    // Outside code can never touch these directly — only through setters/getters.
    int id;
    std::string name;
    bool power;
    int volume;
    int brightness;
    std::string input;
    float temperature;
};
