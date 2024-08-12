    #include <stdio.h>
    #include <pcap.h>
    #include <string.h>
    #include <stdint.h>
    #include <time.h>
    #include <arpa/inet.h>

    #define HTTP2_FRAME_HEADER_LEN 9
    #define GRPC_CONTENT_TYPE "application/grpc"
    #define GRPC_CONTENT_TYPE_LEN (sizeof(GRPC_CONTENT_TYPE) - 1)


// Custom IP Header Structure
struct __attribute__((__packed__)) custom_ip_hdr {
    uint8_t ip_hl:4, ip_v:4;  // Header length and version
    uint8_t ip_tos;           // Type of service
    uint16_t ip_len;          // Total length
    uint16_t ip_id;           // Identification
    uint16_t ip_off;          // Fragment offset field
    uint8_t ip_ttl;           // Time to live
    uint8_t ip_p;             // Protocol
    uint16_t ip_sum;          // Checksum
    uint32_t ip_src;          // Source address (4 bytes)
    uint32_t ip_dst;          // Destination address (4 bytes)
};

// Custom TCP Header Structure
struct __attribute__((__packed__)) custom_tcp_hdr {
    uint16_t source;          // Source port
    uint16_t dest;            // Destination port
    uint32_t seq;             // Sequence number
    uint32_t ack_seq;         // Acknowledgment number
    uint8_t  doff:4;          // Data offset
    uint8_t  reserved:4;      // Reserved
    uint8_t  fin:1;           // FIN flag
    uint8_t  syn:1;           // SYN flag
    uint8_t  rst:1;           // RST flag
    uint8_t  psh:1;           // PSH flag
    uint8_t  ack:1;           // ACK flag
    uint8_t  urg:1;           // URG flag
    uint8_t  ece:1;           // ECE flag
    uint8_t  cwr:1;           // CWR flag
    uint16_t window;          // Window size
    uint16_t check;           // Checksum
    uint16_t urg_ptr;         // Urgent pointer
};

   /* void print_packet_info(const struct ip *ip, const struct tcphdr *tcp, const char *timestamp) {
        char src_ip[INET_ADDRSTRLEN], dst_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(ip->ip_src), src_ip, INET_ADDRSTRLEN);
        inet_ntop(AF_INET, &(ip->ip_dst), dst_ip, INET_ADDRSTRLEN);
        printf("%s IP %s.%d > %s.%d: gRPC\n", 
            timestamp, 
            src_ip, ntohs(tcp->source), 
            dst_ip, ntohs(tcp->dest));
    }
    */

    void process_packet(const unsigned char *packet, int length) {
        const struct custom_ip_hdr *ip = (const struct custom_ip_hdr *)(packet + 14); 
        int ip_header_length = ip->ip_hl * 4; 
        const struct custom_tcp_hdr *tcp = (const struct custom_tcp_hdr *)(packet + 14 + ip_header_length);
        int tcp_header_length = tcp->doff * 4; 
        
        char src_ip[INET_ADDRSTRLEN], dst_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(ip->ip_src), src_ip, INET_ADDRSTRLEN);
        inet_ntop(AF_INET, &(ip->ip_dst), dst_ip, INET_ADDRSTRLEN);

        printf("Source IP: %s\n", src_ip);
        printf("Destination IP: %s\n", dst_ip);

        // Debug output for source and destination ports
        printf("TCP src port: %d, dst port: %d\n", ntohs(tcp->source), ntohs(tcp->dest));

        // Check if the packet is using port 50051
        if (ntohs(tcp->source) == 50051 || ntohs(tcp->dest) == 50051) {
            struct timespec ts;
            clock_gettime(CLOCK_REALTIME, &ts);
            char timestamp[100];
            strftime(timestamp, sizeof(timestamp), "%H:%M:%S", localtime(&ts.tv_sec));
            sprintf(timestamp + strlen(timestamp), ".%06ld", ts.tv_nsec / 1000); 
            


            // Check for HTTP/2 connection preface
            const unsigned char *http2_header = packet + 14 + ip_header_length + tcp_header_length;
            int remaining_len = length - (14 + ip_header_length + tcp_header_length);

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
                            //print_packet_info(ip, tcp, timestamp);
                        }
                    }
                }

                http2_header += HTTP2_FRAME_HEADER_LEN + frame_length;
                remaining_len -= HTTP2_FRAME_HEADER_LEN + frame_length;
            }
        }
    }

    void packet_handler(unsigned char *args, const struct pcap_pkthdr *header, const unsigned char *packet) {
        process_packet(packet, header->len);
    }

    int main(int argc, char *argv[]) {
        if (argc != 2) {
            fprintf(stderr, "Usage: %s <pcap file>\n", argv[0]);
            return 1;
        }

        char *filename = argv[1];
        pcap_t *handle;
        char errbuf[PCAP_ERRBUF_SIZE];

        // Open the pcap file
        handle = pcap_open_offline(filename, errbuf);
        if (handle == NULL) {
            fprintf(stderr, "Could not open file %s: %s\n", filename, errbuf);
            return 1;
        }

        // Process each packet in the pcap file
        pcap_loop(handle, 0, packet_handler, NULL);

        // Close the pcap file
        pcap_close(handle);
        return 0;
    }
