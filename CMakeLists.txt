cmake_minimum_required(VERSION 2.8)

project(qt-threads)

add_subdirectory(lock-to-stop)
add_subdirectory(supplier-consumer)
add_subdirectory(two-lock-queue)
add_subdirectory(logging-thread)
add_subdirectory(async-streams)
add_subdirectory(concurrent)

