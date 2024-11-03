#include "Iterator/Directory.h"


int main() {
    Directory dir("TestPath");
    for (auto it = dir.begin(); it != dir.end(); ++it) {
        std::cout << *it << std::endl;
    }
    return 0;
}