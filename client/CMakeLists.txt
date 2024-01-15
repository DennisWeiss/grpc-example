
file(
        GLOB
        GRPC_EXAMPLE_CLIENT_SRC
        src/*.h
        src/*.cpp
)

add_executable(grpc_example_client ${GRPC_EXAMPLE_CLIENT_SRC})
