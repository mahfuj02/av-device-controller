// logger.cpp
// Implementation of Logger. Uses std::ofstream in append mode and a small
// std::chrono/std::strftime recipe for the timestamp.

#include "logger.h"

#include <chrono>
#include <ctime>
#include <stdexcept>
#include <filesystem>


Logger::Logger(const std::string& filepath) {

    // Ensure the parent directory exists (so a fresh clone with no `logs/`
    // folder works out of the box).
    auto parent = std::filesystem::path(filepath).parent_path();
    if (!parent.empty()) {
        std::filesystem::create_directories(parent);
    }
    // std::ios::app = "append" — every write goes at the end of the file.
    // Without this flag, opening a file in write mode truncates it.
    file.open(filepath, std::ios::app);
    if (!file.is_open())
        throw std::runtime_error("Cannot open log file: " + filepath);
}

void Logger::log(int id, const std::string& event, const std::string& value) {
    file << getCurrentTime() << " [Display " << id << "] " << event;
    if (!value.empty())
        file << " = " << value;
    file << "\n";
    file.flush(); // force the write to disk now, not whenever the OS feels like it
}

std::string Logger::getCurrentTime() {
    // 3-step recipe to turn "now" into a formatted string.
    auto now = std::chrono::system_clock::now();               // time point
    std::time_t t = std::chrono::system_clock::to_time_t(now); // convert to C-style time_t
    char buf[20];
    std::strftime(buf, sizeof(buf), "%H:%M:%S",
                  std::localtime(&t)); // format into the buffer
    return std::string(buf);
}