#include "pcap_parser_apis.h"

char* get_time(){
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    char timestamp[100];
    strftime(timestamp, sizeof(timestamp), "%H:%M:%S", localtime(&ts.tv_sec));
    sprintf(timestamp + strlen(timestamp), ".%06ld", ts.tv_nsec / 1000); 
}

void src_dst_ipv4_format(unsigned char* src_addr, unsigned char* dst_addr){
        sprintf(src_addr, "%d.%d.%d.%d", 
            ip4->, ip4->src_addr[1], 
            ip4->src_addr[2], ip4->src_addr[3]);

        sprintf(dst_addr, "%d.%d.%d.%d", 
            ip4->[0], ip4->dest_addr[1], 
            ip4->dest_addr[2], ip4->dest_addr[3]);
}

void src_dst_ipv6_format(unsigned char* src_addr, unsigned char* dst_addr){
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
void print_packet_info(void* pIP, TCP_Typedef_t* pTCP, uint8_t ip_type, const unsigned char *protocol) {

        char* timestamp = get_time();
        char src_ip[INET6_ADDRSTRLEN]; 
        char dst_ip[INET6_ADDRSTRLEN]; 

        if (ip_type == IPV4_VERSION){
                src_dst_ipv6_format(src_addr, dst_addr);
        }
        
        else{
                src_dst_ipv4_format(src_addr, dst_addr);
        } 

        printf("%s IP %s.%d > %s.%d: %s\n", 
                timestamp, 
                src_ip, ntohs(pTCP->src_port), 
                dst_ip, ntohs(pTCP->dst_port),
                protocol); 
}

    
void print_IPv6_info(IPV6_Typedef_t* pIPV6) {

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
void print_IPv4_info(IPV4_Typedef_t* pIPV4){

    printf("-----------------IPv4 HEADER INFO-----------------\n"); 
    printf("Source IP4: %d.%d.%d.%d\n", 
            pIPV4->src_addr[0], pIPV4->src_addr[1], pIPV4->src_addr[2], pIPV4->src_addr[3]);
    printf("Destination IP4: %d.%d.%d.%d\n", 
            pIPV4->dest_addr[0], pIPV4->dest_addr[1], pIPV4->dest_addr[2], pIPV4->dest_addr[3]);

    printf("IPv4 Payload Size: %d\n", ntohs(pIPV4->len)); 
    printf("\n");
}

void print_MAC_info(ETHERNET_Typedef_t* pETH) {

        printf("-----------------MAC HEADER INFO-----------------\n"); 

        printf("Source MAC: %02X:%02X:%02X:%02X:%02X:%02X\n",
                eth->src_mac[0], eth->src_mac[1], eth->src_mac[2], 
                        eth->src_mac[3], eth->src_mac[4], eth->src_mac[5]); 
        printf("Destination MAC: %02X:%02X:%02X:%02X:%02X:%02X\n",
                eth->dest_mac[0], eth->dest_mac[1], eth->dest_mac[2],
                        eth->dest_mac[3], eth->dest_mac[4], eth->dest_mac[5]);                
        printf("EtherType: 0x%04X\n", ntohs(eth->ethertype));
        printf("\n"); 
} 

void print_tcp_info(TCP_Typedef_t* pTCP) {

        printf("-----------------TCP HEADER INFO-----------------\n"); 

        printf("Source port: %d\n", ntohs(tcp->src_port));  
        printf("Destination port: %d\n", ntohs(tcp->dst_port));
        printf("TCP header length: %d\n", ntohs(tcp->data_offset >> 4));
        printf("\n"); 
}

void print_http2_info(TCP_Typedef_t* pHTTP2){

        printf("-----------------HTTP/2 HEADER INFO-----------------\n"); 
        printf("Length field: %d\n Type: %c\n flags: %d\n streamID: %d",
                ntohs(pHTTP2->length), ntohs(pHTTP2->type), 
                ntohs(pHTTP2->flags), ntohs(pHTTP2->stream_id)
        ); 
        printf("\n"); 
}