#include "Iterator/ArgumentParser.h"
#include <iostream>
#include <vector>

int main() {
    std::vector<std::string> args = {"program_name", "-a", "-b", "value1", "-c", "value2"};

    std::vector<char*> argv;
    for (auto& arg : args) {
        argv.push_back(const_cast<char*>(arg.c_str()));
    }

    int argc = static_cast<int>(argv.size());
    const char* options = "ab:c:";

    ArgumentParser parser(argc, argv.data(), options);

    for (const auto& arg : parser) {
        std::cout << "Option: " << arg.m_flag.value_or("Unknown");
        if (arg.m_value) {
            std::cout << ", Value: " << arg.m_value.value();
        } else {
            std::cout << ", No Value";
        }
        std::cout << std::endl;
    }

    return 0;
}
