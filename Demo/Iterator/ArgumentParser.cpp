#include "Iterator/ArgumentParser.h"
#include <iostream>
#include <vector>

int main() {
    const char* args[] = {
        "program_name",
        "-a",
        "-b",
        "value1",
        "-c",
        "value2"
    };

    int argc = sizeof(args) / sizeof(char*);
    char** argv = const_cast<char**>(args);

    const char* options = "ab:c:";

    ArgumentParser parser(argc, argv, options);

    for (const auto& arg : parser) {
        std::cout << "Option: " << arg.m_flag;
        if (arg.m_value) {
            std::cout << ", Value: " << arg.m_value.value();
        } else {
            std::cout << ", No Value";
        }
        std::cout << std::endl;
    }
    return 0;
}

