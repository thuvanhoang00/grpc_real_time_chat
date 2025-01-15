cmake_minimum_required(VERSION 3.8)

project(server)

set(CMAKE_CXX_STANDARD 17)

include (./common.cmake)

# Proto files
# /home/thu/LearnGRPC/grpc_real_time_chat/source
get_filename_component(hw_proto "/source/greet.proto" ABSOLUTE)
get_filename_component(hw_proto_path "${hw_proto}" PATH)

message("Binary dir: ${CMAKE_CURRENT_BINARY_DIR}")
message("hw_proto: ${hw_proto}")
message("hw_proto_path: ${hw_proto_path}")
message("----------------------------------")
# Generated sources
set(hw_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/../source/greet.pb.cc")
set(hw_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/../source/greet.pb.h")
set(hw_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/../source/greet.grpc.pb.cc")
set(hw_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/../source/greet.grpc.pb.h")
message("hw_proto_srcs: ${hw_proto_srcs}")
message("hw_proto_hdrs: ${hw_proto_hdrs}")
message("hw_grpc_srcs: ${hw_grpc_srcs}")
message("hw_grpc_hdrs: ${hw_grpc_hdrs}")
message("----------------------------------")

# add_custom_command(
#     OUTPUT "${hw_proto_srcs}" "${hw_proto_hdrs}" "${hw_grpc_srcs}" "${hw_grpc_hdrs}"
#     COMMAND ${_PROTOBUF_PROTOC}
#     ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
#         --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
#         -I "${hw_proto_path}"
#         --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
#         "${hw_proto}"
#       DEPENDS "${hw_proto}"
# )

# Include generated *.pb.h files
include_directories("${CMAKE_CURRENT_BINARY_DIR}/source/")

# hw_grpc_proto
add_library(hw_grpc_proto
  ${hw_grpc_srcs}
  ${hw_grpc_hdrs}
  ${hw_proto_srcs}
  ${hw_proto_hdrs})
target_link_libraries(hw_grpc_proto
  absl::check
  ${_REFLECTION}
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF})

# Targets (client|server)
foreach(_target
  client server)
  add_executable(${_target} "../source/${_target}.cpp")
  target_link_libraries(${_target}
    hw_grpc_proto
    absl::check
    absl::flags
    absl::flags_parse
    absl::log
    ${_REFLECTION}
    ${_GRPC_GRPCPP}
    ${_PROTOBUF_LIBPROTOBUF})
endforeach()
