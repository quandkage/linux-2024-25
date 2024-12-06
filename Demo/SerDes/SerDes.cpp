#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>
#include "SerDes.hpp"

struct Test {
    int a;
    double b;
};

void test_basic_serialization() {
    Test t1 = {42, 3.14159};
    serialize(t1, "data/test_basic.bin");

    Test t2;
    deserialize(t2, "data/test_basic.bin");

    assert(t2.a == 42);
    assert(std::abs(t2.b - 3.14159) < 1e-5);
    std::cout << "Test Basic Serialization and Deserialization passed." << std::endl;
}

void test_boundary_values() {
    Test t1 = {0, 0.0};
    serialize(t1, "data/test_zero.bin");
    Test t2;
    deserialize(t2, "data/test_zero.bin");
    assert(t2.a == 0);
    assert(t2.b == 0.0);

    t1 = {-1, -2.718};
    serialize(t1, "data/test_negative.bin");
    deserialize(t2, "data/test_negative.bin");
    assert(t2.a == -1);
    assert(std::abs(t2.b - -2.718) < 1e-5);

    t1 = {std::numeric_limits<int>::max(), std::numeric_limits<double>::max()};
    serialize(t1, "data/test_max.bin");
    deserialize(t2, "data/test_max.bin");
    assert(t2.a == std::numeric_limits<int>::max());
    assert(t2.b == std::numeric_limits<double>::max());

    std::cout << "Test Boundary Values passed." << std::endl;
}

void test_empty_file() {
    std::ofstream emptyFile("data/empty.bin", std::ios::binary);
    emptyFile.close();

    Test t;
    try {
        deserialize(t, "data/empty.bin");
        std::cout << "Test Empty File failed: expected an exception." << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Test Empty File passed (caught expected exception)." << std::endl;
    }
}

void test_large_object() {
    struct LargeObject {
        int a[1000];
        double b[1000];
    };

    LargeObject lo1;
    for (int i = 0; i < 1000; ++i) {
        lo1.a[i] = i;
        lo1.b[i] = i * 1.1;
    }

    serialize(lo1, "data/test_large_object.bin");

    LargeObject lo2;
    deserialize(lo2, "data/test_large_object.bin");

    assert(lo2.a[0] == 0);
    assert(std::abs(lo2.b[999] - 1099.0) < 1e-1);

    std::cout << "Test Large Object passed." << std::endl;
}

int main() {
    try {
        test_basic_serialization();
        test_boundary_values();
        test_empty_file();
        test_large_object();
    } catch (const std::exception& e) {
        std::cerr << "Test failed: " << e.what() << std::endl;
        return -1;
    }
    return 0;
}
