project(WachDogs)

add_executable(Watcher drWatcher.cpp)
target_include_directories(Watcher PRIVATE ../../Utils/WatchDogs)
#target_link_libraries(Watcher PRIVATE libs)
