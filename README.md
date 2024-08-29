# gRPC Packet Analyzer

## Overview

The **gRPC Packet Analyzer** project was developed during a 2-month internship at ACTIA Engineering Services. It focuses on analyzing network traffic to detect gRPC communications, featuring a custom tcpdump plugin, cross-compilation support for ARM architecture, and detailed documentation.

## Project Structure

### `docs/`

This directory contains documentation files related to the project:

- **`gRPC.md`**: Information on gRPC protocol and its implementation.
- **`NDK_android.md`**: Instructions for setting up and using the Android NDK for cross-compilation.
- **`Networking_headers.md`**: Overview of networking headers used in the project.
- **`protofiles.md`**: Details on the .proto files used for defining gRPC services and messages.
- **`TCPDump.md`**: Documentation on integrating the custom tcpdump plugin.

### `gRPC-ProtoFiles/`

This directory includes the gRPC protocol files and their implementation:

- **`gRPC-cpp/`**: Contains C++ implementation files for gRPC.
  - **`client.cpp`**: C++ client implementation for gRPC.
  - **`server.cpp`**: C++ server implementation for gRPC.
  - **`Makefile`**: Makefile for building the C++ gRPC components.

- **`gRPC-python/`**: Contains Python implementation files for gRPC.
  - **`client.py`**: Python client implementation for gRPC.
  - **`server.py`**: Python server implementation for gRPC.
  - **`example.proto`**: Proto file used for defining gRPC services in Python.

  
### `MyAndroidProject/`

This directory contains the Android NDK project for cross-compiling:

- **`build/`**: Contains build files and output from the Android NDK build process.
  - **`CMakeLists.txt`**: CMake configuration for Android NDK build.
  - **`src/`**: Source directory for the Android project.
    - **`test.c`**: Example C source file.

- **`CMakeLists.txt`**: CMake configuration file for building the Android project.

### `print_gRPC/`

This directory contains the core implementation for analyzing gRPC packets:

- **`include/`**: Contains header files.
  - **`common.h`**: Common definitions and declarations used across the project.

- **`src/`**: Contains source files for packet processing.
  - **`main.c`**: Entry point for the packet analyzer.
  - **`packet_handler.c`**: Functions for handling packets.
  - **`packet_handler_wrapper.c`**: Wrapper functions for packet handling.
  - **`print_ethernet.c`**: Functions for printing Ethernet headers.
  - **`print_grpc.c`**: Functions for identifying and printing gRPC traffic.
  - **`print_headers_info.c`**: Functions for printing header information.
  - **`print_http2.c`**: Functions for parsing HTTP/2 headers.
  - **`print_ip4.c`**: Functions for printing IPv4 headers.
  - **`print_ip6.c`**: Functions for printing IPv6 headers.
  - **`print_packet_info.c`**: Functions for printing general packet information.
  - **`print_tcp.c`**: Functions for printing TCP headers.
  - **`process_packet.c`**: Functions for processing packets.

- **`Makefile`**: Makefile for building the packet analyzer.
- **`grpc_traffic.pcap`** and **`input.pcap`**: Example pcap file for analysis.
  
- **`output/`**: Directory for output files.

## Prerequisites

- **gRPC:** Ensure gRPC and its dependencies are installed.
- **CMake:** Required for building C++ components.
- **Android NDK:** Needed for cross-compilation to ARM architecture.

