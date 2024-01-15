
file(
        GLOB
        GRPC_EXAMPLE_CLIENT_SRC
        src/*.h
        src/*.cpp
)

add_executable(grpc_example_client ${GRPC_EXAMPLE_CLIENT_SRC})

target_include_directories(grpc_example_client PUBLIC ${CMAKE_SOURCE_DIR}/generated)

target_link_libraries(
        grpc_example_client
        protobuf::libprotobuf
        gRPC::grpc
        gRPC::grpc++
)
