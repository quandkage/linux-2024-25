#pragma once
#include "DoCommand/DoCommand.hpp"
#include <sstream>

void xargs(int argc, char* argv[]) {
    if (argc < 2) {
        exit(1);
    }

    std::string command;
    for (size_t i = 0; i < argc; ++i) {
        if (i > 0) {
            command += " ";
            command += argv[i];
        }
    }
    std::string input;
    while (std::getline(std::cin, input)) {
        std::stringstream stream(input);
        std::string arg;

        while (stream >> arg) {
            std::string full = command + " " + arg;

            int res = do_command(full.c_str());

            if (res != 0) {
                std::cerr << "Failed with exit code" << res << std::endl;

            }
        }
    }
}