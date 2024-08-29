CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
project(tcpdump)

include(android.toolchain.cmake)

file(GLOB SOURCES /home/ghassen/Documents/GitHub/grpc_pcap_analyzer/tcpdump-android/tcpdump/*.c)

include_directories(/usr/include 
                    /usr/include/pcap
                    /home/ghassen/Documents/GitHub/grpc_pcap_analyzer/tcpdump-android/tcpdump/
                    /home/ghassen/Documents/GitHub/grpc_pcap_analyzer/tcpdump-android/tcpdump/missing)

add_executable(tcpdump ${SOURCES})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I/usr/include -I/usr/include/pcap")
target_link_libraries(tcpdump c m)