project(Iterator)

add_executable(iterator CircularIntIterator.cpp)
add_executable(iterator FilterIntegerIterator.cpp)
add_executable(iterator ReverseArrayIterator.cpp)
add_compile_options(-fsanitize=address,undefined -fno-omit-frame-pointer -fsanitize-address-use-after-scope -fsanitize-address-use-after-return=runtime)
add_link_options(-fsanitize=address,undefined)

target_include_directories(iterator PRIVATE ../../Utils)
