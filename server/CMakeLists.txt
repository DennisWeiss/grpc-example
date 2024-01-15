
file(
        GLOB
        GRPC_EXAMPLE_SERVER_SRC
        src/*.h
        src/*.cpp
)

add_executable(grpc_example_server ${GRPC_EXAMPLE_SERVER_SRC})

target_include_directories(grpc_example_server PUBLIC ${CMAKE_SOURCE_DIR}/generated)

target_link_libraries(
        grpc_example_server
        protobuf::libprotobuf
        gRPC::grpc
        gRPC::grpc++
)
