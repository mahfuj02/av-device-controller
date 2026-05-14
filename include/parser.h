// parser.h
// Defines the structured form of a user command and the parse() entry point.
#pragma once

#include <string>
#include <vector>

// Output shape of the parser. Plain data — no methods, no invariants.
// Filled in by parse(), consumed by Controller.

struct ParsedCommand {
    bool isAll;                    // true if the command is "ALL" (applies to all displays)
    int displayId;                 // if not ALL, the numeric ID of the target display
    std::string command;           // the command verb, e.g.  "SET_VOLUME", etc.
    std::vector<std::string> args; // any additional arguments, e.g. ["ON"], ["60"], etc.
};

ParsedCommand parse(const std::string& input);
