#pragma once
#include <unistd.h>
#include <fcntl.h>
#include <type_traits>
#include <sys/mman.h>
#include <cstring>
#include <stdexcept>

class MappedFile {
private:
    size_t m_size = 0;
    void* m_data = nullptr;
public:
    MappedFile(const std::string& fileName, size_t size)
        : m_data(nullptr) {
        int fd = open(fileName.c_str(), O_RDWR | O_CREAT, 0666);
        if (fd == -1) {
            throw std::runtime_error("Failed to open or create file: " + fileName);
        }

        if (ftruncate(fd, size) == -1) {
            close(fd);
            throw std::runtime_error("Failed to resize file to size: " + std::to_string(size));
        }

        void* data = mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
        close(fd);

        if (data == MAP_FAILED) {
            throw std::runtime_error("Memory mapping failed for file: " + fileName);
        }

        m_data = data;
        m_size = size;
    }

    ~MappedFile() {
        if (m_data && m_data != MAP_FAILED) {
            munmap(m_data, m_size);
        }
    }

    void* data() const {
        return m_data;
    }

    size_t size() const {
        return m_size;
    }
};

template <typename T>
void serialize(const T& obj, const std::string& fileName) {
    static_assert(std::is_trivially_copyable_v<T>, "T must be trivially copyable");

    MappedFile mappedFile(fileName, sizeof(T));
    std::memcpy(mappedFile.data(), &obj, sizeof(T));
}

template <typename T>
void deserialize(T& obj, const std::string& fileName) {
    static_assert(std::is_trivially_copyable_v<T>, "T must be trivially copyable");

    MappedFile mappedFile(fileName, sizeof(T));
    std::memcpy(&obj, mappedFile.data(), sizeof(T));
}
