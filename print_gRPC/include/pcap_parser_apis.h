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

const char http2_preface[] = {
    0x50, 0x52, 0x49, 0x20, 0x2a, 0x20, 0x48, 0x54, 
    0x54, 0x50, 0x2f, 0x32, 0x2e, 0x30, 0x0d, 0x0a,
    0x0d, 0x0a, 0x53, 0x4d, 0x0d, 0x0a, 0x0d, 0x0a
};


unsigned char gRPC_preface[] = {
    0x40, 0x0c, 0x63, 0x6f, 0x6e, 0x74, 0x65, 0x6e, 
    0x74, 0x2d, 0x74, 0x79, 0x70, 0x65, 0x10, 0x61,
    0x70, 0x70, 0x6c, 0x69, 0x63, 0x61, 0x74, 0x69,
    0x6f, 0x6e, 0x2f, 0x67, 0x72, 0x70, 0x63
};

TCP_Typedef_t *get_tcp(const unsigned char *packet, uint16_t protocol);
IPV6_Typedef_t *get_ip6(const unsigned char *packet, int link_type);
IPV4_Typedef_t *get_ip4(const unsigned char *packet);

char* get_time(); 
int is_http2(const unsigned char *tptr, int length);
int is_grpc(unsigned char *http2_header, int packet_len);
void src_dst_ipv6_format(char* src_addr, char* dst_addr);
void src_dst_ipv4_format(char* src_addr, char* dst_addr); 
uint16_t get_physical_proto(const unsigned char *packet, int link_type);

void parse_packet(const unsigned char *packet, int length, int link_type);
void packet_handler_wrapper(unsigned char *args, const struct pcap_pkthdr *header, const unsigned char *packet);
void handle_pcap_file(unsigned char *args, const struct pcap_pkthdr *header, const unsigned char *packet, int link_type);
void print_http2_header(const unsigned char *ptr);

void print_tcp_info(TCP_Typedef_t *tcp);
void print_IPv6_info(IPV6_Typedef_t *eth);
void print_MAC_info(ETHERNET_Typedef_t *hdr)
void print_packet_info(ETHERNET_Typedef_t *pETH, void *pIP, TCP_Typedef_t *pTCP, const unsigned char *protocol); 
