// parser.cpp
// Implementation of parse(). Mechanically splits, uppercases, and packages
// tokens into a ParsedCommand. Does not know what commands are valid.

#include "parser.h"
#include <sstream>   // std::istringstream — for splitting by whitespace
#include <stdexcept> // std::invalid_argument
#include <algorithm> // std::transform
#include <cctype>    // ::toupper

ParsedCommand parse(const std::string &rawInput)
{
    ParsedCommand result;
    std::istringstream ss(rawInput);
    std::string token;
    std::vector<std::string> tokens;

    // 1. Tokenize — split rawInput by whitespace.
    //    Each pass of the loop reads the next whitespace-separated word.
    //    2. Uppercase each token so input is case-insensitive.
    while (ss >> token)
    {
        std::transform(token.begin(), token.end(),
                       token.begin(), ::toupper);
        tokens.push_back(token);
    }

    // Empty input → throw immediately.
    if (tokens.empty())
        throw std::invalid_argument("Empty input");

    // 3. Branch on the first token.
    if (tokens[0] == "ALL")
    {
        // Pattern A: ALL <command> <args...>
        result.isAll = true;
        result.displayId = 0;
        if (tokens.size() < 2)
            throw std::invalid_argument("ALL needs a command");
        result.command = tokens[1];
        for (size_t i = 2; i < tokens.size(); i++)
            result.args.push_back(tokens[i]);
    }
    else if (tokens[0] == "DISPLAY")
    {
        // Pattern B: DISPLAY <id> <command> <args...>
        result.isAll = false;
        if (tokens.size() < 3)
            throw std::invalid_argument("DISPLAY needs ID and command");
        try
        {
            result.displayId = std::stoi(tokens[1]);
        }
        catch (const std::exception &)
        {
            throw std::invalid_argument(
                "DISPLAY ID must be a number, got: " + tokens[1]);
        }
        result.command = tokens[2];
        for (size_t i = 3; i < tokens.size(); i++)
            result.args.push_back(tokens[i]);
    }
    else
    {
        // Pattern C: direct command (STATUS, HELP, QUIT, ...)
        result.isAll = false;
        result.displayId = -1;
        result.command = tokens[0];
        for (size_t i = 1; i < tokens.size(); i++)
            result.args.push_back(tokens[i]);
    }

    return result;
}