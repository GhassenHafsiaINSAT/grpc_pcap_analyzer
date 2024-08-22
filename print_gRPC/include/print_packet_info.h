#include "common.h"

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