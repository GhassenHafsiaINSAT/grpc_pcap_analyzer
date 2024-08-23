#include "common.h"

struct tcp_hdr* print_tcp(unsigned char packet, int len){

    struct tcp_hdr* tcp = (struct tcp_hdr*)(packet + ETHERNET_HEADER_LEN + 40); 
    return tcp; 
}