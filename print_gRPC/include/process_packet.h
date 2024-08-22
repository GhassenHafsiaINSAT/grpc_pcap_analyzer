#include "common.h"

// This function parses the pcap file in order to check if it's gRPC message or not 
void process_packet(const unsigned char *packet, int length);