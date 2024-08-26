#include "common.h"

void packet_handler_wrapper(unsigned char *args, const struct pcap_pkthdr *header, const unsigned char *packet) {
    packet_handler(args, header, packet, link_type); 
}