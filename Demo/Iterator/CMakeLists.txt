project(Iterator)


add_executable(DirectoryDemo Directory.cpp)
target_include_directories(DirectoryDemo PRIVATE ../../Utils)
target_link_libraries(DirectoryDemo PRIVATE libs)

add_executable(CircularIntIteratorDemo CircularIntIterator.cpp)
target_include_directories(CircularIntIteratorDemo PRIVATE ../../Utils)
target_link_libraries(CircularIntIteratorDemo PRIVATE libs)

add_executable(FilterIntegerIteratorDemo FilterIntegerIterator.cpp)
target_include_directories(FilterIntegerIteratorDemo PRIVATE ../../Utils)
target_link_libraries(FilterIntegerIteratorDemo PRIVATE libs)

add_executable(ReverseArrayIteratorDemo ReverseArrayIterator.cpp)
target_include_directories(ReverseArrayIteratorDemo PRIVATE ../../Utils)
target_link_libraries(ReverseArrayIteratorDemo PRIVATE libs)

add_custom_command(TARGET DirectoryDemo POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_LIST_DIR}/TestPath $<TARGET_FILE_DIR:DirectoryDemo>/TestPath)