#include "SerDes.hpp"

MappedFile::MappedFile(const std::string &fileName, size_t size) : m_data(nullptr) {

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

MappedFile::~MappedFile() {
    if (m_data && m_data != MAP_FAILED) {
        munmap(m_data, m_size);
    }
}

void *MappedFile::data() const {
    return m_data;
}

size_t MappedFile::size() const {
    return m_size;
}



