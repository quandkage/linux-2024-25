#include <iostream>
#include "DoCommand/DoCommand.hpp"

int main() {
    const char* command = "ls -l";
    int result = do_command(command);

    std::cout << "exit code " << result << std::endl;

    return 0;
}