// controller.cpp
// Implementation of the Controller — Day 4 version (single-display routing).

#include "controller.h"
#include <iostream>
#include <stdexcept>

Controller::Controller() {
    // Nothing to do for now. Displays are added later via addDisplay().
}

void Controller::addDisplay(int id, const std::string& name) {
    displays.emplace_back(id, name);
}

void Controller::execute(const ParsedCommand& cmd) {
    // Direct, no-target commands first.
    if (cmd.command == "STATUS") {
        printStatus();
        return;
    }
    if (cmd.command == "HELP") {
        std::cout << "Commands:\n"
                  << "  DISPLAY <id> SET_POWER ON|OFF\n"
                  << "  DISPLAY <id> SET_VOLUME 0-100\n"
                  << "  DISPLAY <id> SET_BRIGHTNESS 0-100\n"
                  << "  DISPLAY <id> SET_INPUT HDMI|AV|DP\n"
                  << "  STATUS  HELP  QUIT\n";
        return;
    }

    // Day 4: only single-display commands. (ALL comes Day 5.)
    if (cmd.isAll) {
            for (auto& d : displays){
                executeOnDisplay(d, cmd);
            }
        return;
    }

    Display* d = getDisplay(cmd.displayId);
    if (!d) {
        std::cout << "[ERROR] Display " << cmd.displayId << " not found\n";
        return;
    }
    executeOnDisplay(*d, cmd);
}

void Controller::printStatus() {
    for (const auto& d : displays) {
        std::cout << d.getStatus() << "\n";
    }
}

Display* Controller::getDisplay(int id) {
    for (auto& d : displays) {
        if (d.getId() == id) return &d;
    }
    return nullptr;
}

void Controller::executeOnDisplay(Display& d, const ParsedCommand& cmd) {
    try {
        if (cmd.command == "SET_POWER") {
            if (cmd.args.empty())
                throw std::invalid_argument("SET_POWER needs ON or OFF");
            d.setPower(cmd.args[0] == "ON");
        }
        else if (cmd.command == "SET_VOLUME") {
            if (cmd.args.empty())
                throw std::invalid_argument("SET_VOLUME needs a number");
            d.setVolume(std::stoi(cmd.args[0]));
        }
        else if (cmd.command == "SET_BRIGHTNESS") {
            if (cmd.args.empty())
                throw std::invalid_argument("SET_BRIGHTNESS needs a number");
            d.setBrightness(std::stoi(cmd.args[0]));
        }
        else if (cmd.command == "SET_INPUT") {
            if (cmd.args.empty())
                throw std::invalid_argument("SET_INPUT needs HDMI, AV, or DP");
            d.setInput(cmd.args[0]);
        }
        else {
            std::cout << "[ERROR] Unknown command: " << cmd.command << "\n";
            return;
        }

        std::cout << "[OK] Display " << d.getId()
                  << " executed: " << cmd.command << "\n";
    }
    catch (const std::exception& e) {
        std::cout << "[ERROR] " << e.what() << "\n";
    }
}