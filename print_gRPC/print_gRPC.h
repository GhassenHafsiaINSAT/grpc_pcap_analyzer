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

// Ethernet header
struct ethernet_hdr {
    uint8_t dest_mac[6];
    uint8_t src_mac[6];
    uint16_t ethertype;
};

// IPv4 header
struct ip4_hdr {
    uint8_t version_ihl;
    uint8_t tos;
    uint16_t total_length;
    uint16_t identification;
    uint16_t flags_fragment_offset;
    uint8_t ttl;
    uint8_t protocol;
    uint16_t checksum;
    uint32_t src_addr;
    uint32_t dst_addr;
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


/* The function retrieves the current time with high precision using clock_gettime.
It formats the time into a string in HH:MM:SS format and appends the microseconds to the timestamp. */
void print_time(); 


// This function prints out the packet using basic for loop
void print_packet(const unsigned char *packet, int length); 

/* This function prints out the packet info, including:
    - timestamp
    - src_ip
    - dst_ip
    - protocol used 
*/
void print_packet_info(const struct ip *ip, const struct tcphdr *tcp, const char *timestamp); 

// This function parses the pcap file in order to check if it's gRPC message or not 
void process_packet(const unsigned char *packet, int length);

// This function reads each packet separatly and calls the process_packet function
void packet_handler(unsigned char *args, const struct pcap_pkthdr *header, const unsigned char *packet); 
