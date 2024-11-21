#include "SerDes.hpp"

struct Test {
    int a;
    float b;
};

int main(){
    try {
        Test t = {1,3.14};
        serialize(t, "/home/robert/Desktop/linux-2024-25/Demo/SerDes/TestRep/uzbek.bin");

        Test t2;
        deserialize(t2, "/home/robert/Desktop/linux-2024-25/Demo/SerDes/TestRep/uzbek.bin");

        std::cout << "Deserialized obj -> " << t2.a << " " << t2.b << std::endl;
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }
    return 0;
}
