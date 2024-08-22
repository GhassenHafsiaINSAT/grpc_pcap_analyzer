#include "print_ethernet.h"

struct ethernet_hdr* print_ethernet(const unsigned char packet, int len){    
    
    struct ethernet_hdr* eth = (struct ethernet_hdr*)packet; 
    
    return eth; 
}