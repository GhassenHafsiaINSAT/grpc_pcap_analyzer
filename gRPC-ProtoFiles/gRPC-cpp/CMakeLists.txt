cmake_minimum_required(VERSION 3.10)
project(MyProject)

# Find Protobuf
find_package(Protobuf REQUIRED)

# Include Protobuf headers
include_directories(${PROTOBUF_INCLUDE_DIRS})

# Define where to find .proto files
set(PROTO_FILES
    your_file.proto
)

# Generate C++ files from .proto files
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_FILES})

# Add executable
add_executable(MyExecutable main.cpp ${PROTO_SRCS})

# Link Protobuf libraries
target_link_libraries(MyExecutable ${PROTOBUF_LIBRARIES})
