// main.cpp — Day 3 sanity check for the parser.
// Drives parse() with a handful of inputs and prints the resulting struct.

#include "parser.h"
#include <iostream>
#include <string>
#include <vector>

void printResult(const std::string& input) {
    std::cout << "Input: \"" << input << "\"\n";
    try {
        ParsedCommand cmd = parse(input);
        std::cout << "  isAll="     << std::boolalpha << cmd.isAll
                  << "  displayId=" << cmd.displayId
                  << "  command=\"" << cmd.command << "\"";
        std::cout << "  args=[";
        for (size_t i = 0; i < cmd.args.size(); ++i) {
            if (i > 0) std::cout << ", ";
            std::cout << "\"" << cmd.args[i] << "\"";
        }
        std::cout << "]\n";
    } catch (const std::exception& e) {
        std::cout << "  ERROR: " << e.what() << "\n";
    }
    std::cout << "\n";
}

int main() {
    std::vector<std::string> tests = {
        // valid
        "DISPLAY 2 SET_VOLUME 60",
        "ALL SET_POWER ON",
        "STATUS",
        "HELP",
        "display 1 set_input hdmi",        // lowercase — should still uppercase
        "ALL SET_INPUT HDMI",

        // edge cases / errors
        "",                                 // empty → throws
        "DISPLAY",                          // missing ID and command → throws
        "ALL",                              // missing command → throws
        "DISPLAY abc SET_VOLUME 60",        // non-numeric ID → throws (stoi)

        // structurally fine but nonsense — should NOT throw at parser
        "BANANA",                           // direct cmd "BANANA"
        "My name is Mahfuj",                // direct cmd "MY", args ["NAME","IS","MAHFUJ"]
    };

    std::cout << "=== Parser test ===\n\n";
    for (const auto& t : tests) printResult(t);
    return 0;
}