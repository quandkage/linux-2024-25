#ifndef SERDES_H
#define SERDES_H

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
    MappedFile(const std::string& fileName, size_t size);

    ~MappedFile();

    void* data() const;

    [[nodiscard]] size_t size() const;

};

#endif