#include "common.h"

struct ethernet_hdr* print_ethernet(const unsigned char* packet){    

    struct ethernet_hdr* eth = (struct ethernet_hdr*)packet; 
    return eth; 
     
}
/*
u_int print_etherent(const unsigned char *packet, int len) {
    // Example printing of Ethernet header fields
    ND_PRINT("Ethernet Frame:");
    ND_PRINT("Source MAC: %s", format_mac_address(bp));
    ND_PRINT("Destination MAC: %s", format_mac_address(bp + 6));
    ND_PRINT("EtherType: 0x%04x", EXTRACT_16BITS(bp + 12));

    // Call the provided function to print payload if required
    if (print_payload != NULL) {
        print_payload(ndo, ether_payload);
    }

    // Return the length of the Ethernet header (for example)
    return 14; // Standard length of Ethernet header
}
*/