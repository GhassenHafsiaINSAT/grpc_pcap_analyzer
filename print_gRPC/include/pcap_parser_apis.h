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

#include "network_headers.h"

#define HTTP2_PREFACE_SIZE 24
#define HTTP2_PREFACE {
    0x50, 0x52, 0x49, 0x20, 0x2a, 0x20, 0x48, 0x54, 
    0x54, 0x50, 0x2f, 0x32, 0x2e, 0x30, 0x0d, 0x0a,
    0x0d, 0x0a, 0x53, 0x4d, 0x0d, 0x0a, 0x0d, 0x0a
}
#define GRPC_PREFACE_SIZE 31
#define GRPC_PREFACE {
    0x40, 0x0c, 0x63, 0x6f, 0x6e, 0x74, 0x65, 0x6e, 
    0x74, 0x2d, 0x74, 0x79, 0x70, 0x65, 0x10, 0x61,
    0x70, 0x70, 0x6c, 0x69, 0x63, 0x61, 0x74, 0x69,
    0x6f, 0x6e, 0x2f, 0x67, 0x72, 0x70, 0x63
};

// protocols checkers 
char* get_time(); 
uint8_t is_ethernet(int datalink);
uint8_t is_sll(int datalink);
void* get_ip_header(const unsigned char* packet);
uint8_t check_ip_version(void* ip_header);
TCP_Typedef_t* check_tcp(void* ip_header, uint8_t ip_vesion);
uint8_t is_http2(const unsigned char *ptr, uint32_t length);
uint8_t is_grpc(const unsigned char *http2_header, uint32_t length);

// handle and parse packet
void parse_packet(const unsigned char *packet, uint32_t length, int link_type);
void packet_handler_wrapper(unsigned char *args, const struct pcap_pkthdr *header, const unsigned char *packet);
void handle_pcap_file(unsigned char *args, const struct pcap_pkthdr *header, const unsigned char *packet, int link_type);

// print packet and headers info 
void src_dst_ipv4_format(unsigned char* src_addr, unsigned char* dst_addr);
void src_dst_ipv6_format(unsigned char* src_addr, unsigned char* dst_addr);
void print_packet_info(void* pIP, TCP_Typedef_t* pTCP, uint8_t ip_type, const unsigned char *protocol);   
void print_IPv6_info(IPV6_Typedef_t* pIPV6);
void print_IPv4_info(IPV4_Typedef_t* pIPV4);
void print_MAC_info(ETHERNET_Typedef_t* pETH);
void print_tcp_info(TCP_Typedef_t* pTCP);
void print_http2_info(TCP_Typedef_t* pHTTP2);
