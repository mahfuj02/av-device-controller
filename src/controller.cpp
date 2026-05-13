// controller.cpp
// Implementation of the Controller — Day 4 version (single-display routing).

#include "controller.h"
#include <iostream>
#include <stdexcept>
#include <fstream>      
#include <sstream>

// Returns true if `cmd` is a per-display command that executeOnDisplay
// knows how to run. Used to avoid spamming the same error 5 times in a
// broadcast.
static bool isPerDisplayCommand(const std::string &cmd)
{
    return cmd == "SET_POWER" || cmd == "SET_VOLUME" || cmd == "SET_BRIGHTNESS" || cmd == "SET_INPUT";
}

Controller::Controller()
{
    // Nothing to do for now. Displays are added later via addDisplay().
}

void Controller::addDisplay(int id, const std::string &name)
{
    displays.emplace_back(id, name);
}

void Controller::loadConfig(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open config file: " + filepath);
    }

    // Start fresh in case loadConfig is called more than once.
    displays.clear();

    std::string line;
    int lineNumber = 0;
    while (std::getline(file, line)) {
        ++lineNumber;

        // Skip blank lines and comments.
        if (line.empty() || line[0] == '#') continue;

        std::istringstream iss(line);
        int id;
        std::string name;
        if (!(iss >> id >> name)) {
            std::cerr << "[WARNING] Skipping malformed line "
                      << lineNumber << ": " << line << "\n";
            continue;
        }

        displays.emplace_back(id, name);
    }

    if (displays.empty()) {
        throw std::runtime_error(
            "Config file contains no valid displays: " + filepath);
    }

    std::cout << "[SYSTEM] Loaded " << displays.size()
              << " displays from " << filepath << "\n";
}

void Controller::execute(const ParsedCommand &cmd)
{
    // Direct, no-target commands first.
    if (cmd.command == "STATUS")
    {
        printStatus();
        return;
    }
    if (cmd.command == "HELP")
    {
        std::cout << "Commands:\n"
                  << "  DISPLAY <id> SET_POWER ON|OFF\n"
                  << "  DISPLAY <id> SET_VOLUME 0-100\n"
                  << "  DISPLAY <id> SET_BRIGHTNESS 0-100\n"
                  << "  DISPLAY <id> SET_INPUT HDMI|AV|DP\n"
                  << "  ALL <command> [args...]   - broadcast to every display\n"
                  << "  STATUS                    - show all display states\n"
                  << "  HELP                      - show this message\n"
                  << "  QUIT                      - exit the program\n";
        return;
    }

    // Day 4: only single-display commands. (ALL comes Day 5.)
    if (cmd.isAll)
    {
        if (!isPerDisplayCommand(cmd.command))
        {
            std::cout << "[ERROR] Unknown command: " << cmd.command << "\n";
            return;
        }
        for (auto &d : displays)
        {
            executeOnDisplay(d, cmd);
        }
        return;
    }

    Display *d = getDisplay(cmd.displayId);
    if (!d)
    {
        std::cout << "[ERROR] Display " << cmd.displayId << " not found\n";
        return;
    }
    executeOnDisplay(*d, cmd);
}

void Controller::printStatus()
{
    for (const auto &d : displays)
    {
        std::cout << d.getStatus() << "\n";
    }
}

void Controller::tickTemperatures()
{
    // Advance the simulated temperature on every display by one tick,
    // then let Alert flag any that crossed the threshold.
    for (auto &d : displays)
    {
        d.simulateTemperature();
    }
    alert.check(displays);
}

Display *Controller::getDisplay(int id)
{
    for (auto &d : displays)
    {
        if (d.getId() == id)
            return &d;
    }
    return nullptr;
}

void Controller::executeOnDisplay(Display &d, const ParsedCommand &cmd)
{
    try
    {
        if (cmd.command == "SET_POWER")
        {
            if (cmd.args.empty())
                throw std::invalid_argument("SET_POWER needs ON or OFF");
            if (cmd.args[0] != "ON" && cmd.args[0] != "OFF")
                throw std::invalid_argument(
                    "SET_POWER must be ON or OFF, got: " + cmd.args[0]);
            d.setPower(cmd.args[0] == "ON");
        }
        else if (cmd.command == "SET_VOLUME")
        {
            if (cmd.args.empty())
                throw std::invalid_argument("SET_VOLUME needs a number");
            int val;
            try
            {
                val = std::stoi(cmd.args[0]);
            }
            catch (const std::exception &)
            {
                throw std::invalid_argument(
                    "SET_VOLUME expected a number, got: " + cmd.args[0]);
            }
            d.setVolume(val);
        }
        else if (cmd.command == "SET_BRIGHTNESS")
        {
            if (cmd.args.empty())
                throw std::invalid_argument("SET_BRIGHTNESS needs a number");
            int val;
            try
            {
                val = std::stoi(cmd.args[0]);
            }
            catch (const std::exception &)
            {
                throw std::invalid_argument(
                    "SET_BRIGHTNESS expected a number, got: " + cmd.args[0]);
            }
            d.setBrightness(val);
        }
        else if (cmd.command == "SET_INPUT")
        {
            if (cmd.args.empty())
                throw std::invalid_argument("SET_INPUT needs HDMI, AV, or DP");
            d.setInput(cmd.args[0]);
        }
        else
        {
            std::cout << "[ERROR] Unknown command: " << cmd.command << "\n";
            return;
        }
        logger.log(d.getId(), cmd.command, cmd.args.empty() ? "" : cmd.args[0]);
        std::cout << "[OK] Display " << d.getId()
                  << " executed: " << cmd.command << "\n";
    }
    catch (const std::exception &e)
    {
        std::cout << "[ERROR] " << e.what() << "\n";
    }
}