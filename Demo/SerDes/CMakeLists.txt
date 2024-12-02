project(SerDES)

add_executable(SerDesDemo SerDes.cpp)
target_include_directories(SerDesDemo PRIVATE ../../Utils/SerDes)


