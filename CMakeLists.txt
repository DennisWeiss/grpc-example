cmake_minimum_required(VERSION 3.27)

project(grpc_example)

set(CMAKE_CXX_STANDARD 20)

file(
        GLOB
        PROTO_OBJECTS
        ${CMAKE_SOURCE_DIR}/proto/protos/*.proto
)

set(PROTO_BINARY_DIR ${CMAKE_SOURCE_DIR}/generated)
set(PROTO_IMPORT_DIR ${CMAKE_SOURCE_DIR}/proto)

find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)

add_library(
        proto_objects
        OBJECT
        ${PROTO_OBJECTS}
)

target_link_libraries(
        proto_objects
        protobuf::libprotobuf
        gRPC::grpc
        gRPC::grpc++
)

target_include_directories(proto_objects PUBLIC "$<BUILD_INTERFACE:${PROTO_BINARY_DIR}>")

protobuf_generate(
        TARGET proto_objects
        IMPORT_DIRS ${PROTO_IMPORT_DIR}
        PROTOC_OUT_DIR ${PROTO_BINARY_DIR}
)
protobuf_generate(
        TARGET proto_objects
        IMPORT_DIRS ${PROTO_IMPORT_DIR}
        PROTOC_OUT_DIR ${PROTO_BINARY_DIR}
        LANGUAGE grpc
        GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc
        PLUGIN "protoc-gen-grpc=\$<TARGET_FILE:gRPC::grpc_cpp_plugin>"
)


add_subdirectory(server)
add_subdirectory(client)
