

project(Iterator)


add_executable(DirectoryDemo Directory.cpp)
target_include_directories(DirectoryDemo PRIVATE ../../Utils)

add_executable(CircularIntIteratorDemo CircularIntIterator.cpp)
target_include_directories(CircularIntIteratorDemo PRIVATE ../../Utils)

add_executable(FilterIntegerIteratorDemo FilterIntegerIterator.cpp)
target_include_directories(FilterIntegerIteratorDemo PRIVATE ../../Utils)

add_executable(ReverseArrayIteratorDemo ReverseArrayIterator.cpp)
target_include_directories(ReverseArrayIteratorDemo PRIVATE ../../Utils)
