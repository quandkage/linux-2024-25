project(Iterator)

add_executable(CircularIntIteratorDemo CircularIntIterator.cpp)
target_include_directories(CircularIntIteratorDemo PRIVATE ../../Utils)
target_compile_options(CircularIntIteratorDemo PRIVATE -fno-omit-frame-pointer -fsanitize-address-use-after-scope -fsanitize-address-use-after-return=runtime)
target_link_options(CircularIntIteratorDemo PRIVATE -fsanitize=address,undefined)

add_executable(FilterIntegerIteratorDemo FilterIntegerIterator.cpp)
target_include_directories(FilterIntegerIteratorDemo PRIVATE ../../Utils)
target_compile_options(FilterIntegerIteratorDemo PRIVATE -fno-omit-frame-pointer -fsanitize-address-use-after-scope -fsanitize-address-use-after-return=runtime)
target_link_options(FilterIntegerIteratorDemo PRIVATE -fsanitize=address,undefined)

add_executable(ReverseArrayIteratorDemo ReverseArrayIterator.cpp)
target_include_directories(ReverseArrayIteratorDemo PRIVATE ../../Utils)
target_compile_options(ReverseArrayIteratorDemo PRIVATE -fno-omit-frame-pointer -fsanitize-address-use-after-scope -fsanitize-address-use-after-return=runtime)
target_link_options(ReverseArrayIteratorDemo PRIVATE -fsanitize=address,undefined)
