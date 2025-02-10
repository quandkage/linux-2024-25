#ifndef SERDESUTILS_HPP
#define SERDESUTILS_HPP

#include "SerDes.hpp"
#include <type_traits>
#include <cstring>
#include <string>

template <typename T>
void serialize(const T& obj, const std::string& fileName);

template <typename T>
void deserialize(T& obj, const std::string& fileName);

#include "SerDesUtilsDef.cpp"

#endif //SERDESUTILS_HPP
