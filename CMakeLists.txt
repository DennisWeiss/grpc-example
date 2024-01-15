cmake_minimum_required(VERSION 3.27)

project(grpc_example)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(server)
add_subdirectory(client)
