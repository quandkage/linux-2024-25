#pragma once
#include <unistd.h>
#include <fcntl.h>
#include <type_traits>
#include <sys/mman.h>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <stdexcept>

class MappedFile {
public:
    static void* map(const std::string& fileName, size_t size) {
        int fd = open(fileName.c_str(), O_RDWR | O_CREAT, 0666);
        if (fd == -1) {
            throw std::runtime_error("Failed to open or create file: " + fileName);
        }

        if (ftruncate(fd, size) == -1) {
            close(fd);
            throw std::runtime_error("Failed to resize file to size: " + std::to_string(size));
        }

        void* data = mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
        if (data == MAP_FAILED) {
            close(fd);
            throw std::runtime_error("Memory mapping failed for file: " + fileName);
        }

        close(fd);

        return data;
    }

    static void unmap(void* data, size_t size) {
        if (data != MAP_FAILED) {
            munmap(data, size);
        }
    }
};

template <typename T>
void serialize(const T& obj, const std::string& fileName) {
    static_assert(std::is_trivially_copyable_v<T>, "T must be trivially copyable");

    void* data = MappedFile::map(fileName, sizeof(T));

    std::memcpy(data, &obj, sizeof(T));

    MappedFile::unmap(data, sizeof(T));
}

template <typename T>
void deserialize(T& obj, const std::string& fileName) {
    static_assert(std::is_trivially_copyable_v<T>, "T must be trivially copyable");

    void* data = MappedFile::map(fileName, sizeof(T));

    std::memcpy(&obj, data, sizeof(T));

    MappedFile::unmap(data, sizeof(T));
}

void createFiles() {
    std::filesystem::create_directory("data");

    std::ofstream outText("hopar.txt", std::ios::app);
    if (!outText) {
        throw std::runtime_error("Error creating or opening 'hopar.txt' for writing");
    }
}
