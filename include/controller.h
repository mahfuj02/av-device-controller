// controller.h
// The Controller owns all Display objects and dispatches parsed commands

#pragma once

#include "alert.h"
#include "display.h"
#include "logger.h"
#include "parser.h"
#include <vector>

class Controller {
  public:
    Controller();

    // Add a single display. Used by loadConfig() and by tests.
    void addDisplay(int id, const std::string& name);

    // Load displays from a config file (one "id name" pair per line).
    void loadConfig(const std::string& filepath =
                        "../config/displays.cfg"); //  load displays from a config file
    // Take a parsed command and act on it.
    void execute(const ParsedCommand& cmd);

    // Print the status line for every display.
    void printStatus();

    void tickTemperatures(); // nudge every display's temperature by a random delta

  private:
    std::vector<Display> displays;
    Logger logger; // one logger per controller, shared by all displays
    Alert alert;   // one alert per controller, shared by all displays

    // Internal helpers
    Display* getDisplay(int id); // find by ID, nullptr if not found
    void executeOnDisplay(Display& d, const ParsedCommand& cmd);
};
