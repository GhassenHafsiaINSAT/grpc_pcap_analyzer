#include "common.h"
// This function reads each packet separatly and calls the process_packet function
void packet_handler(unsigned char *args, const struct pcap_pkthdr *header, const unsigned char *packet); 