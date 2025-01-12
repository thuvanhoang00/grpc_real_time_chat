find_package(gRPC REQUIRED)
find_package(Protobuf REQUIRED)

add_executable(server greeter_server.cpp greet.pb.cc greet.grpc.pb.cc)
target_include_directories(server PRIVATE ${Protobuf_INCLUDE_DIRS} ${gRPC_INCLUDE_DIRS})
target_link_libraries(server PRIVATE gRPC::grpc++ Protobuf::libprotobuf)