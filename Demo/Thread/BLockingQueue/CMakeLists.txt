project(Blocking_Queue)

add_executable(BlockingQueue MainBlockingQueue.cpp)
target_include_directories(BlockingQueue PRIVATE /home/robert/linux-2024-25/Utils/Thread/BlockingQueue)
target_link_libraries(BlockingQueue PRIVATE libs)