#include <stdio.h>
#include <stdlib.h>  
#include <pcap.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <arpa/inet.h>

#define ETHERNET_HEADER_LEN 14
#define HTTP2_FRAME_HEADER_LEN 9
#define GRPC_CONTENT_TYPE "application/grpc"
#define GRPC_CONTENT_TYPE_LEN (sizeof(GRPC_CONTENT_TYPE) - 1)

void print_packet_info(const struct ip *ip, const struct tcphdr *tcp, const char *timestamp) {
    char src_ip[INET_ADDRSTRLEN], dst_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(ip->ip_src), src_ip, INET_ADDRSTRLEN);
    inet_ntop(AF_INET, &(ip->ip_dst), dst_ip, INET_ADDRSTRLEN);
    printf("%s IP %s.%d > %s.%d: gRPC\n", 
        timestamp, 
        src_ip, ntohs(tcp->th_sport), 
        dst_ip, ntohs(tcp->th_dport));
}

void process_packet(const unsigned char *packet, int length, uint16_t grpc_port) {
    const struct ip *ip = (const struct ip *)(packet + ETHERNET_HEADER_LEN); // Skip Ethernet header
    int ip_header_length = ip->ip_hl * 4; // Calculate IP header length
    const struct tcphdr *tcp = (const struct tcphdr *)(packet + ETHERNET_HEADER_LEN + ip_header_length);
    int tcp_header_length = tcp->th_off * 4; // Calculate TCP header length

    // Check if the packet is using the gRPC port
    if (ntohs(tcp->th_sport) != grpc_port || ntohs(tcp->th_dport) == grpc_port) {
        struct timespec ts;
        clock_gettime(CLOCK_REALTIME, &ts);
        char timestamp[100];
        strftime(timestamp, sizeof(timestamp), "%H:%M:%S", localtime(&ts.tv_sec));
        sprintf(timestamp + strlen(timestamp), ".%06ld", ts.tv_nsec / 1000); // Append microseconds

        print_packet_info(ip, tcp, timestamp);

        // Check for HTTP/2 connection preface
        const unsigned char *http2_header = packet + ETHERNET_HEADER_LEN + ip_header_length + tcp_header_length;
        int remaining_len = length - (ETHERNET_HEADER_LEN + ip_header_length + tcp_header_length);

        // Handle HTTP/2 connection preface
        if (remaining_len >= 24 && memcmp(http2_header, "PRI * HTTP/2.0\r\n\r\nSM\r\n\r\n", 24) == 0) {
            http2_header += 24; // Skip connection preface
            remaining_len -= 24;
        }

        // Loop through the HTTP/2 frames
        while (remaining_len >= HTTP2_FRAME_HEADER_LEN) {
            uint32_t frame_length = (http2_header[0] << 16) | (http2_header[1] << 8) | http2_header[2];
            uint8_t frame_type = http2_header[3];

            // Check for DATA frame (type 0x0)
            if (frame_type == 0x0) {
                if (remaining_len >= (HTTP2_FRAME_HEADER_LEN + frame_length)) {
                    // Check for gRPC content type in the payload
                    if (frame_length >= GRPC_CONTENT_TYPE_LEN &&
                        memcmp(http2_header + HTTP2_FRAME_HEADER_LEN, GRPC_CONTENT_TYPE, GRPC_CONTENT_TYPE_LEN) == 0) {
                        print_packet_info(ip, tcp, timestamp);
                    }
                }
            }

            http2_header += HTTP2_FRAME_HEADER_LEN + frame_length;
            remaining_len -= HTTP2_FRAME_HEADER_LEN + frame_length;
        }
    }
}

void packet_handler(unsigned char *args, const struct pcap_pkthdr *header, const unsigned char *packet) {
    uint16_t grpc_port = *((uint16_t *)args);
    process_packet(packet, header->len, grpc_port);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pcap file>", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    uint16_t grpc_port = atoi(argv[2]);
    pcap_t *handle;
    char errbuf[PCAP_ERRBUF_SIZE];

    // Open the pcap file
    handle = pcap_open_offline(filename, errbuf);
    if (handle == NULL) {
        fprintf(stderr, "Could not open file %s: %s\n", filename, errbuf);
        return 1;
    }

    // Process each packet in the pcap file
    pcap_loop(handle, 0, packet_handler, (unsigned char *)&grpc_port);

    // Close the pcap file
    pcap_close(handle);
    return 0;
}
