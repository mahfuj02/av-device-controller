// main.cpp — Day 4 REPL (Read-Eval-Print Loop).
// Interactive command prompt that drives the Controller end-to-end.

#include "controller.h"
#include "parser.h"
#include <iostream>
#include <string>

int main() {
    Controller ctrl;

    // Hardcode some displays for now. Day 9 will replace this with
    // loading from config/displays.cfg.
    ctrl.addDisplay(1, "MainBar");
    ctrl.addDisplay(2, "PoolTable");
    ctrl.addDisplay(3, "Entrance");
    ctrl.addDisplay(4, "Patio");
    ctrl.addDisplay(5, "BackRoom");

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