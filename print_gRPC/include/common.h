#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <netinet/ip.h>
#include <netinet/ip6.h>
#include <netinet/tcp.h>
#include <pcap.h>
#include <arpa/inet.h>
#include <time.h>
#include <string.h>

#define ETHERNET_HEADER_LEN 14
#define ETHERTYPE_IPV6 0x86DD
#define NEXT_HEADER_TCP 0x0600

#define HTTP2_FRAME_HEADER_SIZE 9

typedef enum {
    FRAME_TYPE_DATA = 0x0,
    FRAME_TYPE_HEADERS = 0x1,
    FRAME_TYPE_PRIORITY = 0x2,
    FRAME_TYPE_RST_STREAM = 0x3,
    FRAME_TYPE_SETTINGS = 0x4,
    FRAME_TYPE_PUSH_PROMISE = 0x5,
    FRAME_TYPE_PONG = 0x6,
    FRAME_TYPE_GOAWAY = 0x7,
    FRAME_TYPE_WINDOW_UPDATE = 0x8,
    FRAME_TYPE_CONTINUATION = 0x9
} http2_frame_type_t;

typedef struct {
    uint32_t length;
    uint8_t type;
    uint8_t flags;
    uint32_t stream_id;
} http2_frame_header_t;

struct ethernet_hdr {
    uint8_t dest_mac[6];
    uint8_t src_mac[6];
    uint16_t ethertype;

};  
// IPv4 header
struct ipv4_hdr {
    uint8_t version : 4;
    uint8_t ihl : 4;
    uint8_t tos;
    uint16_t len;
    uint16_t id;
    uint16_t flags : 3;
    uint16_t frag_offset : 13;
    uint8_t ttl;
    uint8_t proto;
    uint16_t csum;
    uint32_t saddr;
    uint32_t daddr;
};

// IPv6 header
struct ipv6_hdr {
    uint32_t version_tc_fl;   
    uint16_t payload_length;    
    uint8_t next_header;        
    uint8_t hop_limit;
    uint8_t src_addr[16];       
    uint8_t dest_addr[16];      
};

// TCP header structure
struct tcp_hdr {
    uint16_t src_port;
    uint16_t dst_port;
    uint32_t seq_num;
    uint32_t ack_num;
    uint8_t data_offset;
    uint8_t flags;
    uint16_t window;
    uint16_t checksum;
    uint16_t urgent_pointer;
};

struct http2_hdr {
    uint32_t length : 24;
    uint8_t type;
    uint8_t flags;
    uint32_t reserved : 1;
    uint32_t stream_id : 31;
};

unsigned char target_sequence[] = {
    0x40, 0x0c, 0x63, 0x6f, 0x6e, 0x74, 0x65, 0x6e, 0x74, 0x2d, 0x74, 
    0x79, 0x70, 0x65, 0x10, 0x61, 0x70, 0x70, 0x6c, 0x69, 0x63, 0x61, 
    0x74, 0x69, 0x6f, 0x6e, 0x2f, 0x67, 0x72, 0x70, 0x63
};


// This function reads each packet separatly and calls the process_packet function
void packet_handler(unsigned char *args, const struct pcap_pkthdr *header, const unsigned char *packet); 

// This function parses the pcap file in order to check if it's gRPC message or not 
void process_packet(const unsigned char *packet, int length);

/* This function prints out if the packet contains gRPC message, indicating:
    - timestamp
    - gRPC protocol 
    - src_ip
    - dst_ip
*/
void print_packet_info(struct ipv6_hdr *ip, struct tcp_hdr *tcp, const unsigned char *protocol); 


// This function prints out TCP header info 
void print_tcp_info(struct tcp_hdr *tcp);

// This function prints out IPv6 header info 
void print_IPv6_info(struct ipv6_hdr *eth);

// This function prints out the Ethernet header info 
void print_MAC_info(struct ethernet_hdr *hdr); 

int check_grpc_content_type(unsigned char *http2_header, int packet_len); 

int is_http2_frame(const unsigned char *payload, int len); 

struct ethernet_hdr print_ethernet(const unsigned char *packet, int len);