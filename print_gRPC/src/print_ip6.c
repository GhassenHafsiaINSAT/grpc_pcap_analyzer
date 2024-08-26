#include "common.h"

struct ipv6_hdr* print_ip6(const unsigned char *packet){    

        struct ipv6_hdr* ip6 = (struct ipv6_hdr*)(packet + ETHERNET_HEADER_LEN);
        return ip6;
}