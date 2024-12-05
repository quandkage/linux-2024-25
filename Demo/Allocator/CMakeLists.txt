project(Allocator)

add_executable(Allocator Allocator.cpp)
target_include_directories(Allocator PRIVATE ../../Utils/Allocator)