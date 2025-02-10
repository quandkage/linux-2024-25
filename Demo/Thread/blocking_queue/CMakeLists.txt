project(Blocking_Queue)

add_executable(BlockingQueue main_blocking_queue.cpp)
target_include_directories(BlockingQueue PRIVATE /home/robert/linux-2024-25/Utils/Thread/blocking_queue)
target_link_libraries(BlockingQueue PRIVATE libs)