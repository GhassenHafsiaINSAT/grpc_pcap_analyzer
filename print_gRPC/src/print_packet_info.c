#include "common.h"

void print_packet_info(struct ipv6_hdr *ip6, struct tcp_hdr *tcp, const unsigned char *protocol) {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    char timestamp[100];
    strftime(timestamp, sizeof(timestamp), "%H:%M:%S", localtime(&ts.tv_sec));
    sprintf(timestamp + strlen(timestamp), ".%06ld", ts.tv_nsec / 1000); 
    
    char src_ip[48]; 
    char dst_ip[48]; 

    sprintf(src_ip,  "%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X",
            ip6->src_addr[0], ip6->src_addr[1], ip6->src_addr[2], 
            ip6->src_addr[3], ip6->src_addr[4], ip6->src_addr[5],
            ip6->src_addr[6], ip6->src_addr[7], ip6->src_addr[8],
            ip6->src_addr[9], ip6->src_addr[10], ip6->src_addr[11],
            ip6->src_addr[12], ip6->src_addr[13], ip6->src_addr[14],
            ip6->src_addr[15]);

    sprintf(dst_ip, "%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X",
            ip6->dest_addr[0], ip6->dest_addr[1], ip6->dest_addr[2], 
            ip6->dest_addr[3], ip6->dest_addr[4], ip6->dest_addr[5],
            ip6->dest_addr[6], ip6->dest_addr[7], ip6->dest_addr[8],
            ip6->dest_addr[9], ip6->dest_addr[10], ip6->dest_addr[11],
            ip6->dest_addr[12], ip6->dest_addr[13], ip6->dest_addr[14],
            ip6->dest_addr[15]);

    printf("%s IP %s.%d > %s.%d: %s\n", 
        timestamp, 
        src_ip, ntohs(tcp->src_port), 
        dst_ip, ntohs(tcp->dst_port),
        protocol);
        
    }

void print_IPv6_info(struct ipv6_hdr *ip6) {

    printf("-----------------IPv6 HEADER INFO-----------------\n"); 
    // print source IPv6 address
    printf("Source IP6: %02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X\n",
            ip6->src_addr[0], ip6->src_addr[1], ip6->src_addr[2], 
            ip6->src_addr[3], ip6->src_addr[4], ip6->src_addr[5],
            ip6->src_addr[6], ip6->src_addr[7], ip6->src_addr[8],
            ip6->src_addr[9], ip6->src_addr[10], ip6->src_addr[11],
            ip6->src_addr[12], ip6->src_addr[13], ip6->src_addr[14],
            ip6->src_addr[15]);

    // print destination IPv6 address
    printf("Destination IP6: %02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X\n",
            ip6->dest_addr[0], ip6->dest_addr[1], ip6->dest_addr[2], 
            ip6->dest_addr[3], ip6->dest_addr[4], ip6->dest_addr[5],
            ip6->dest_addr[6], ip6->dest_addr[7], ip6->dest_addr[8],
            ip6->dest_addr[9], ip6->dest_addr[10], ip6->dest_addr[11],
            ip6->dest_addr[12], ip6->dest_addr[13], ip6->dest_addr[14],
            ip6->dest_addr[15]);

    // print playload size of IPv6 packet
    printf("ipv6 playload size: %d\n", ntohs(ip6->payload_length)); 
    printf("\n"); 

}

void print_MAC_info(struct ethernet_hdr *eth) {

    printf("-----------------MAC HEADER INFO-----------------\n"); 
    // print source MAC address
    printf("Source MAC: %02X:%02X:%02X:%02X:%02X:%02X\n",
            eth->src_mac[0], eth->src_mac[1], eth->src_mac[2], 
                eth->src_mac[3], eth->src_mac[4], eth->src_mac[5]); 

    // print destination MAC address
    printf("Destination MAC: %02X:%02X:%02X:%02X:%02X:%02X\n",
            eth->dest_mac[0], eth->dest_mac[1], eth->dest_mac[2],
                eth->dest_mac[3], eth->dest_mac[4], eth->dest_mac[5]);                

    // print Ethernet type 
    printf("EtherType: 0x%04X\n", ntohs(eth->ethertype));

    printf("\n"); 


} 

void print_tcp_info(struct tcp_hdr *tcp) {

    printf("-----------------TCP HEADER INFO-----------------\n"); 

    // print source port
    printf("Source port: %d\n", ntohs(tcp->src_port)); 
    
    // print destination port 
    printf("Destination port: %d\n", ntohs(tcp->dst_port));
    
    // print tcp header length 
    printf("TCP header length: %d\n", ((tcp->data_offset >> 4) & 0x0F) * 4);


}
