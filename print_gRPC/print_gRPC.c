#include "print_gRPC.h"

void print_packet(const unsigned char *packet, int length){
        
        for(int i=0;i<length;i++) {

            printf("%c",packet[i]);
        
        } 
    
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

void print_tcp_info(struct tcp_hdr *tcp) {

    printf("-----------------TCP HEADER INFO-----------------\n"); 

    // print source port
    printf("Source port: %d\n", ntohs(tcp->src_port)); 
    
    // print destination port 
    printf("Destination port: %d\n", ntohs(tcp->dst_port));
    
    // print tcp header length 
    printf("TCP header length: %d\n", ((tcp->data_offset >> 4) & 0x0F) * 4);


}


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

void process_packet(const unsigned char *packet, int length) {

    struct ethernet_hdr *eth = (struct ethernet_hdr*)packet; 
    // print_MAC_info(eth); 

    if (ntohs(eth->ethertype) == ETHERTYPE_IPV6){
        struct ipv6_hdr *ip6 = (struct ipv6_hdr*)(packet + ETHERNET_HEADER_LEN);
        // print_IPv6_info(ip6);

        
        if (ntohs(ip6->next_header) == NEXT_HEADER_TCP){
            struct tcp_hdr *tcp = (struct tcp_hdr*)(packet + ETHERNET_HEADER_LEN + 40); 
            // print_tcp_info(tcp);
            int tcp_header_length = ((tcp->data_offset >> 4) & 0x0F) * 4;
            int ip6_playload_len = ntohs(ip6->payload_length); 
            int remaining_len = ip6_playload_len - tcp_header_length ;

            if (remaining_len > 0) {
                int verif = 0; 
                int packet_len = length;
                unsigned char *http2_header = (unsigned char *)packet + ETHERNET_HEADER_LEN + 40 + tcp_header_length;
                for (unsigned char *i = http2_header; i <= packet + packet_len - sizeof(target_sequence); i++) {
                    if (memcmp(i, target_sequence, sizeof(target_sequence)) == 0) {
                        // printf("Content-Type 'application/grpc' found\n");
                        print_packet_info(ip6, tcp, "gRPC");
                        verif = 1; 
                        break;
                    }
                    
                }
                if (verif == 0) print_packet_info(ip6, tcp, "HTTP/2");
            }
            else print_packet_info(ip6, tcp, "TCP");

        }
    }
    else {

        struct ip4_hdr *ip4 = (struct ip4_hdr*)(packet + ETHERNET_HEADER_LEN); 

        int len_ip4_hdr = htons(ip4->total_length); 
        char src_ip[INET_ADDRSTRLEN], dst_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(ip4->src_addr), src_ip, INET_ADDRSTRLEN);
        inet_ntop(AF_INET, &(ip4->dst_addr), dst_ip, INET_ADDRSTRLEN);
        printf("Source IP4: %s\n", src_ip);
        printf("Destination IP4: %s\n", dst_ip);

        struct tcp_hdr *tcp = (struct tcp_hdr*)(packet + ETHERNET_HEADER_LEN + len_ip4_hdr); 
    }


}

void packet_handler(unsigned char *args, const struct pcap_pkthdr *header, const unsigned char *packet) {
    
    static int packet_count = 0;  
    packet_count++;  
    printf("Packet #%d\n", packet_count);

    process_packet(packet, header->len);
    printf("\n"); 
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pcap file>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    pcap_t *handle;
    char errbuf[PCAP_ERRBUF_SIZE];

    handle = pcap_open_offline(filename, errbuf);
    if (handle == NULL) {
        fprintf(stderr, "Could not open file %s: %s\n", filename, errbuf);
        return 1;
    }
    int i =0; 
    pcap_loop(handle, 0, packet_handler, NULL); 

    pcap_close(handle);
    return 0;
}