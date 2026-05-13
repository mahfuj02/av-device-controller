// controller.h
// The Controller owns all Display objects and dispatches parsed commands

#pragma once

#include "display.h"
#include "parser.h"
#include "logger.h"
#include <vector>

class Controller {
public:
    Controller();

    // Add a display to the system. Used at startup until Day 9 wires
    // up the config file loader.
    void addDisplay(int id, const std::string& name);

    // Take a parsed command and act on it.
    void execute(const ParsedCommand& cmd);

    // Print the status line for every display.
    void printStatus();

private:
    std::vector<Display> displays;
    Logger logger;   // one logger per controller, shared by all displays

    // Internal helpers
    Display* getDisplay(int id);                            // find by ID, nullptr if not found
    void executeOnDisplay(Display& d, const ParsedCommand& cmd);
};


