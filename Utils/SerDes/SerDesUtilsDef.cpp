#ifndef SERDESUTILSDEF_CPP
#define SERDESUTILSDEF_CPP

#include "SerDesUtils.hpp"

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

template void serialize<int>(const int& obj, const std::string& fileName);
template void deserialize<int>(int& obj, const std::string& fileName);

#endif