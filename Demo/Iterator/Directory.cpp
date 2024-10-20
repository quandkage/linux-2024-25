#include "Iterator/Directory.h"


int main() {
    Directory dir("/home/robert/Desktop/Uzbek");
    for (auto it = dir.begin(); it != dir.end(); ++it) {
        std::cout << it.getName() << std::endl;
    }
    return 0;
}