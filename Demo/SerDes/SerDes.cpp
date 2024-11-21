#include "SerDes.hpp"
#include <iomanip>

struct Test {
    int a;
    double b;
};

int main(){
    try {
        Test t = {1,3.14};
        serialize(t, "/home/robert/Desktop/linux-2024-25/Demo/SerDes/TestRep/uzbek.bin");

        Test t2;
        deserialize(t2, "/home/robert/Desktop/linux-2024-25/Demo/SerDes/TestRep/uzbek.bin");

        auto fd = open("/home/robert/Desktop/linux-2024-25/Demo/SerDes/TestRep/hopar.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
        if (fd == -1) {
            perror("open");
            return -1;
        }

        std::string result = "t2.a: " + std::to_string(t2.a) + ", t2.b: " + std::to_string(t2.b) + "\n";
        ssize_t bytes_written = write(fd, result.c_str(), result.size());
        if (bytes_written == -1) {
            perror("write");
            close(fd);
            return -1;
        }
        close(fd);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }
    return 0;
}
