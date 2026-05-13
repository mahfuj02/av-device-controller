// main.cpp — Day 4 REPL (Read-Eval-Print Loop).
// Interactive command prompt that drives the Controller end-to-end.

#include "controller.h"
#include "parser.h"
#include <iostream>
#include <string>

int main() {
    Controller ctrl;

    // Load display configuration. If this fails (missing file, empty file)
    // there's nothing useful to do, so bail with a non-zero exit code.
    try {
        ctrl.loadConfig();      // uses default ../config/displays.cfg
    } catch (const std::exception& e) {
        std::cerr << "[FATAL] " << e.what() << "\n";
        return 1;
    }

    std::cout << "AV Device Controller v1.0\n";
    std::cout << "Type HELP for commands. Type QUIT to exit.\n\n";

    std::string input;
    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, input)) break;   // Ctrl+Z / EOF
        if (input.empty()) continue;
        if (input == "QUIT" || input == "quit") break;

        try {
            ParsedCommand cmd = parse(input);
            ctrl.execute(cmd);
        } catch (const std::exception& e) {
            std::cout << "[ERROR] " << e.what() << "\n";
        }
        ctrl.tickTemperatures();  // simulate temperature changes and check for alerts

    }

    std::cout << "Shutting down. Goodbye.\n";
    return 0;
}