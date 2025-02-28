project(Blocking_Queue)

add_executable(BlockingQueue MainBlockingQueue.cpp)
add_executable(ThreadPool MainThreadPool.cpp)


target_include_directories(BlockingQueue PRIVATE ../../../Utils/Thread/BlockingQueue)
target_include_directories(ThreadPool PRIVATE ../../../Utils/Thread/BlockingQueue/)


target_link_libraries(BlockingQueue PRIVATE libs)
target_link_libraries(ThreadPool PRIVATE libs)