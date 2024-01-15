
file(
        GLOB
        GRPC_EXAMPLE_SERVER_SRC
        src/*.h
        src/*.cpp
)

add_executable(grpc_example_server ${GRPC_EXAMPLE_SERVER_SRC})
