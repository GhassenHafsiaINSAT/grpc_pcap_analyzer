#include "common.h"

struct ipv4_hdr* print_ip4(const unsigned char *packet){    

        struct ipv4_hdr* ip4 = (struct ipv4_hdr*)(packet + ETHERNET_HEADER_LEN);
        return ip4;
}