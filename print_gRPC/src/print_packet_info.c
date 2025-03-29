#include "pcap_parser_apis.h"

char* get_time(){
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    char timestamp[100];
    strftime(timestamp, sizeof(timestamp), "%H:%M:%S", localtime(&ts.tv_sec));
    sprintf(timestamp + strlen(timestamp), ".%06ld", ts.tv_nsec / 1000); 
}

void src_dst_ipv4_format(char* src_addr, char* dst_addr){
        sprintf(src_addr, "%d.%d.%d.%d", 
            ip4->, ip4->src_addr[1], 
            ip4->src_addr[2], ip4->src_addr[3]);

    sprintf(dst_addr, "%d.%d.%d.%d", 
            ip4->dest_addr[0], ip4->dest_addr[1], 
            ip4->dest_addr[2], ip4->dest_addr[3]);
}

void src_dst_ipv6_format(char* src_addr, char* dst_addr){
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
}
void print_packet_info(ETHERNET_Typedef_t* pETH, void* pIP, TCP_Typedef_t* pTCP, const unsigned char *protocol) {

        char* timestamp = get_time();
        char* src_ip; 
        char* dst_ip; 

        if ()
                src_dst_ipv6_format(src_addr, dst_addr);

        else
                src_dst_ipv4_format(src_addr, dst_addr);

        printf("%s IP %s.%d > %s.%d: %s\n", 
                timestamp, 
                src_ip, ntohs(pTCP->src_port), 
                dst_ip, ntohs(pTCP->dst_port),
                protocol); 
    }

    
void print_IPv6_info(IPV6_Typedef_t *ip6) {

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

void print_MAC_info(ETHERNET_Typedef_t *eth) {

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

void print_tcp_info(TCP_Typedef_t *tcp) {

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

