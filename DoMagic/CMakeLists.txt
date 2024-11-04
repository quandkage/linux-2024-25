add_executable(DoMagic do_magic.cpp do_magic_test.cpp)
target_include_directories(DoMagic PRIVATE ../DoMagic)
add_executable(DoMagic2 do_magic2.cpp)
target_include_directories(DoMagic2 PRIVATE ../DoMagic)

add_custom_command(TARGET DoMagic POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_LIST_DIR}/Tests $<TARGET_FILE_DIR:DoMagic>/Tests)

add_custom_command(TARGET DoMagic2 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_LIST_DIR}/Tests $<TARGET_FILE_DIR:DoMagic2>/Tests)