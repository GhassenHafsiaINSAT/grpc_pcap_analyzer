#include "common.h"

struct ipv6_hdr* print_ip6(const unsigned char *packet, int link_type){    

        struct ipv6_hdr* ip61 = (struct ipv6_hdr*)(packet + ETHERNET_HEADER_LEN);
        struct ipv6_hdr* ip62 = (struct ipv6_hdr*)(packet + SSL_HEADER_LEN);

        switch (link_type) {
                
                case DLT_EN10MB:
                        return ip61;  
                
                case DLT_LINUX_SLL:
                        return ip62; 
        }   
        return NULL; 

}