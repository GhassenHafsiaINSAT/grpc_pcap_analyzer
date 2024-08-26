#include "common.h"

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

void print_http2_header(const unsigned char *ptr){
        
    int length_field = (ptr[0] << 16) | (ptr[1] << 8) | ptr[2];
    char type = ptr[3];
    int flags = ptr[4];
    int stream_id = (ptr[5] << 24) | (ptr[6] << 16) | (ptr[7] << 8) | ptr[8];
    
    printf("-----------------HTTP/2 HEADER INFO-----------------\n"); 
    printf("Length field: %d\n Type: %c\n flags: %d\n streamID: %d",
             length_field, type, flags, stream_id); 
}