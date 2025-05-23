#include "pcap_parser_apis.h"

void packet_handler_wrapper(unsigned char *args, const struct pcap_pkthdr* header, const unsigned char* packet) {
    packet_handler(args, header, packet, link_type); 
}

void handle_pcap_file(unsigned char *args, const struct pcap_pkthdr *header, const unsigned char *packet, int link_type) {
        
    static int packet_count = 0;  
    packet_count++;  
        
    printf("Packet #%d\n", packet_count);
    uint32_t length = (uint32_t)header->len; 
    process_packet(packet, length, link_type);
    printf("\n"); 
}