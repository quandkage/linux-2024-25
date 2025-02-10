project(SerDES)

add_executable(SerDesDemo SerDes.cpp)
target_include_directories(SerDesDemo PRIVATE ../../Utils/SerDes)
target_link_libraries(SerDesDemo PRIVATE libs)


