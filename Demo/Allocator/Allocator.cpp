#include "Allocator.h"
#include <vector>

int main() {
    char buffer[1024];
    MyAllocator<int> allocator1(buffer, sizeof(buffer));
    std::vector<int, MyAllocator<int>> myVector(allocator1);
    myVector.push_back(52);

    MyAllocator<double> allocator2(1024);
    std::vector<double, MyAllocator<double>> myVector2(allocator2);
    myVector2.push_back(1488);

    myVector.clear();
    myVector2.clear();
    return 0;
}