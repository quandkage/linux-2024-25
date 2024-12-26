#pragma once
#include "DoCommand/DoCommand.hpp"
#include <sstream>
#include <vector>

void xargs(int argc, char* argv[]) {
    if (argc < 2) {
        exit(1);
    }

    std::string command = argv[1];
    for (int i = 2; i < argc; ++i) {
        command += " ";
        command += argv[i];
    }

    std::vector<std::string> arguments;
    std::string input;
    while (std::getline(std::cin, input)) {
        std::stringstream stream(input);
        std::string arg;

        while (stream >> arg) {
            arguments.push_back(arg);
        }
    }

    for (const auto& arg : arguments) {
        command += " ";
        command += arg;
    }

    int res = do_command(command.c_str());

    if (res != 0) {
        std::cerr << "Failed with exit code " << res << std::endl;
    }
}