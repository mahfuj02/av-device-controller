// logger.h
// Writes timestamped event lines to a log file. One Logger per Controller.
// Append-mode: new runs add to the existing file rather than overwriting.

#pragma once

#include <fstream>
#include <string>

class Logger {
  public:
    // Default path assumes the program is launched from `build/`,
    // which is the convention for CMake out-of-source builds.
    // `../logs/events.log` resolves to <project_root>/logs/events.log.
    Logger(const std::string& filepath = "../logs/events.log");

    // Append one entry. `value` is optional — useful for SET_VOLUME = 60
    // but irrelevant for things like STATUS.
    void log(int displayId, const std::string& event, const std::string& value = "");

  private:
    std::ofstream file;
    std::string getCurrentTime(); // returns "HH:MM:SS"
};