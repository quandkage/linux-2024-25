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
private:
    int fd_;
    void* data_;
    size_t size_;

public:
    MappedFile(const std::string& fileName, size_t size)
        : fd_(-1), data_(MAP_FAILED), size_(size) {

        fd_ = open(fileName.c_str(), O_RDWR | O_CREAT, 0666);
        if (fd_ == -1) {
            throw std::runtime_error("Failed to open or create file: " + fileName);
        }

        if (ftruncate(fd_, size_) == -1) {
            close(fd_);
            throw std::runtime_error("Failed to resize file to size: " + std::to_string(size_));
        }

        data_ = mmap(nullptr, size_, PROT_READ | PROT_WRITE, MAP_SHARED, fd_, 0);
        if (data_ == MAP_FAILED) {
            close(fd_);
            throw std::runtime_error("Memory mapping failed for file: " + fileName);
        }
    }

    ~MappedFile() {
        if (data_ != MAP_FAILED) {
            munmap(data_, size_);
        }
        if (fd_ != -1) {
            close(fd_);
        }
    }

    void* getData() {
        return data_;
    }

    int getFd() const {
        return fd_;
    }
};

template <typename T>
void serialize(const T& obj, const std::string& fileName) {
    static_assert(std::is_trivially_copyable_v<T>, "T must be trivially copyable");

    MappedFile mappedFile(fileName, sizeof(T));

    std::memcpy(mappedFile.getData(), &obj, sizeof(T));
}

template <typename T>
void deserialize(T& obj, const std::string& fileName) {
    static_assert(std::is_trivially_copyable_v<T>, "T must be trivially copyable");

    MappedFile mappedFile(fileName, sizeof(T));

    std::memcpy(&obj, mappedFile.getData(), sizeof(T));
}

void createFiles() {
    std::filesystem::create_directory("data");

    std::ofstream outText("hopar.txt", std::ios::app);
    if (!outText) {
        throw std::runtime_error("Error creating or opening 'hopar.txt' for writing");
    }
}

