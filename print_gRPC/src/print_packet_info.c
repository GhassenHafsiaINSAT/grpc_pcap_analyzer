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


