#include "common.h"

uint16_t get_protocol_type(const unsigned char* packet, int link_type){    
    
    struct ethernet_hdr* eth = (struct ethernet_hdr*)packet;
    struct sll_hdr *sll = (struct sll_hdr *)packet;
    
    switch (link_type) {
        
        case DLT_EN10MB:
            return eth->ethertype; 
        
        case DLT_LINUX_SLL:
            return sll->protocol; 

        default:

            printf("Unknown or unsupported link-layer type: %d\n", link_type);
            return 0; 
    }     

}