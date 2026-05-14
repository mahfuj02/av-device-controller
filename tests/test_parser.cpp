// tests/test_parser.cpp
// Unit tests for the parser. Builds into its own executable (test_parser).
// Each function tests one behavior; assert() aborts on the first failure.

#include "parser.h"
#include <cassert>
#include <iostream>

// --- Pattern B: DISPLAY <id> <command> <args> ---
void testBasicDisplayCommand() {
    ParsedCommand cmd = parse("DISPLAY 2 SET_VOLUME 60");
    assert(cmd.isAll == false);
    assert(cmd.displayId == 2);
    assert(cmd.command == "SET_VOLUME");
    assert(cmd.args.size() == 1);
    assert(cmd.args[0] == "60");
    std::cout << "[PASS] testBasicDisplayCommand\n";
}

// --- Pattern A: ALL <command> <args> ---
void testAllCommand() {
    ParsedCommand cmd = parse("ALL SET_POWER ON");
    assert(cmd.isAll == true);
    assert(cmd.command == "SET_POWER");
    assert(cmd.args.size() == 1);
    assert(cmd.args[0] == "ON");
    std::cout << "[PASS] testAllCommand\n";
}

// --- Pattern C: direct command, no target ---
void testDirectCommand() {
    ParsedCommand cmd = parse("STATUS");
    assert(cmd.isAll == false);
    assert(cmd.displayId == -1);
    assert(cmd.command == "STATUS");
    assert(cmd.args.empty());
    std::cout << "[PASS] testDirectCommand\n";
}

// --- Case-insensitivity: lowercase input should uppercase ---
void testLowercaseInput() {
    ParsedCommand cmd = parse("display 1 set_volume 50");
    assert(cmd.command == "SET_VOLUME");
    assert(cmd.displayId == 1);
    assert(cmd.args[0] == "50");
    std::cout << "[PASS] testLowercaseInput\n";
}

// --- Multiple args land in the args vector in order ---
void testMultipleArgs() {
    ParsedCommand cmd = parse("My name is Mahfuj");
    assert(cmd.command == "MY");
    assert(cmd.args.size() == 3);
    assert(cmd.args[0] == "NAME");
    assert(cmd.args[1] == "IS");
    assert(cmd.args[2] == "MAHFUJ");
    std::cout << "[PASS] testMultipleArgs\n";
}

// --- Error case: empty input must throw ---
void testEmptyInputThrows() {
    try {
        parse("");
        std::cout << "[FAIL] testEmptyInputThrows — expected an exception\n";
    } catch (const std::exception&) {
        std::cout << "[PASS] testEmptyInputThrows\n";
    }
}

// --- Error case: "DISPLAY" with no ID/command must throw ---
void testDisplayMissingPartsThrows() {
    try {
        parse("DISPLAY");
        std::cout << "[FAIL] testDisplayMissingPartsThrows — expected an exception\n";
    } catch (const std::exception&) {
        std::cout << "[PASS] testDisplayMissingPartsThrows\n";
    }
}

// --- Error case: "ALL" with no command must throw ---
void testAllMissingCommandThrows() {
    try {
        parse("ALL");
        std::cout << "[FAIL] testAllMissingCommandThrows — expected an exception\n";
    } catch (const std::exception&) {
        std::cout << "[PASS] testAllMissingCommandThrows\n";
    }
}

// --- Error case: non-numeric DISPLAY ID must throw ---
void testNonNumericIdThrows() {
    try {
        parse("DISPLAY abc SET_VOLUME 60");
        std::cout << "[FAIL] testNonNumericIdThrows — expected an exception\n";
    } catch (const std::exception&) {
        std::cout << "[PASS] testNonNumericIdThrows\n";
    }
}

int main() {
    std::cout << "=== Parser unit tests ===\n\n";

    testBasicDisplayCommand();
    testAllCommand();
    testDirectCommand();
    testLowercaseInput();
    testMultipleArgs();
    testEmptyInputThrows();
    testDisplayMissingPartsThrows();
    testAllMissingCommandThrows();
    testNonNumericIdThrows();

    std::cout << "\nAll tests passed!\n";
    return 0;
}