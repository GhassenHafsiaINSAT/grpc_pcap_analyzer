#include "print_gRPC.h"

void print_time(){
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    char timestamp[100];
    strftime(timestamp, sizeof(timestamp), "%H:%M:%S", localtime(&ts.tv_sec));
    sprintf(timestamp + strlen(timestamp), ".%06ld", ts.tv_nsec / 1000); 
}

void print_packet(const unsigned char *packet, int length){
        
        for(int i=0;i<length;i++){
            printf("%c",packet[i]);
        } 
    
}

void print_packet_info(const struct ip *ip, const struct tcphdr *tcp, const char *timestamp) {
        char src_ip[INET_ADDRSTRLEN], dst_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(ip->ip_src), src_ip, INET_ADDRSTRLEN);
        inet_ntop(AF_INET, &(ip->ip_dst), dst_ip, INET_ADDRSTRLEN);
        printf("%s gRPC %s.%d > %s.%d\n", 
            timestamp, 
            src_ip, ntohs(tcp->source), 
            dst_ip, ntohs(tcp->dest));
    }

void process_packet(const unsigned char *packet, int length) {

    struct ethernet_hdr *eth = (struct ethernet_hdr*)packet; 

    /*printf("Destination MAC: %02X:%02X:%02X:%02X:%02X:%02X\n",
            eth->dest_mac[0], eth->dest_mac[1], eth->dest_mac[2],
                eth->dest_mac[3], eth->dest_mac[4], eth->dest_mac[5]);

    printf("Source MAC: %02X:%02X:%02X:%02X:%02X:%02X\n",
            eth->src_mac[0], eth->src_mac[1], eth->src_mac[2], 
                eth->src_mac[3], eth->src_mac[4], eth->src_mac[5]); 

    printf("EtherType: 0x%04X\n", ntohs(eth->ethertype)); */

    if (ntohs(eth->ethertype) == ETHERTYPE_IPV6){
        struct ipv6_hdr *ip6 = (struct ipv6_hdr*)(packet + ETHERNET_HEADER_LEN);

        int ip6_playload_len = ntohs(ip6->payload_length); 
        printf("ip playload: %d\n", ip6_playload_len); 

        /*printf("Source IP6: %02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X\n",
                ip6->src_addr[0], ip6->src_addr[1], ip6->src_addr[2], 
                ip6->src_addr[3], ip6->src_addr[4], ip6->src_addr[5],
                ip6->src_addr[6], ip6->src_addr[7], ip6->src_addr[8],
                ip6->src_addr[9], ip6->src_addr[10], ip6->src_addr[11],
                ip6->src_addr[12], ip6->src_addr[13], ip6->src_addr[14],
                ip6->src_addr[15]);

        printf("Destination IP6: %02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X\n",
                ip6->dest_addr[0], ip6->dest_addr[1], ip6->dest_addr[2], 
                ip6->dest_addr[3], ip6->dest_addr[4], ip6->dest_addr[5],
                ip6->dest_addr[6], ip6->dest_addr[7], ip6->dest_addr[8],
                ip6->dest_addr[9], ip6->dest_addr[10], ip6->dest_addr[11],
                ip6->dest_addr[12], ip6->dest_addr[13], ip6->dest_addr[14],
                ip6->dest_addr[15]);*/
        
        if (ntohs(ip6->next_header) == NEXT_HEADER_TCP){
            struct tcp_hdr *tcp = (struct tcp_hdr*)(packet + ETHERNET_HEADER_LEN + 40); 

            printf("source port: %d -> destination port: %d\n", ntohs(tcp->src_port), ntohs(tcp->dst_port)); 
            int tcp_header_length = ((tcp->data_offset >> 4) & 0x0F) * 4;
            printf("tcp header length: %d\n", tcp_header_length);

            if ((ip6_playload_len - tcp_header_length) > 0) {
                printf("http/2\n"); 
            }
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

    pcap_loop(handle, 0, packet_handler, NULL); 

    pcap_close(handle);
    return 0;
}