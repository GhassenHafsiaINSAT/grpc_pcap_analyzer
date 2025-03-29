#include "pcap_parser_apis.h"

uint8_t is_ethernet(int datalink){
    if(datalink == DLT_EN10MB)
        return 1 
    else 
        return 0 
}

uint8_t is_sll(int datalink){
    if(datalink == DLT_LINUX_SLL)
        return 1 
    else 
        return 0 
}

void* get_ip_header(const unsigned char* packet){
    
    void* ip_header; 
    if(is_ethernet){
        ip_header = packet + ETHERNET_HEADER_LEN; 
        return ip_header; 
    }
    else if (is_sll){
        ip_header = packet + SSL_HEADER_LEN; 
    }
    else 
        return NULL; 
}

uint8_t check_ip_version(void* ip_header) {
    
    uint8_t version; 
    
    if (((IPV4_Typedef_t*)ip_header)->version != 0) {
        version = ((IPV4_Typedef_t*)ip_header)->version;
    } 
    else {
        version = ((IPV6_Typedef_t*)ip_header)->version_tc_fl >> 28; 
    }
    if (version == IPV6_VERSION)
        return 6; 
    else if (version == IPV4_VERSION){
        return 4; 
    }
    else 
        return 0; 
}

TCP_Typedef_t* check_tcp(void* ip_header, uint8_t ip_vesion){
    if (ip_version == IPV6_VERSION){
        if (((IPV6_Typedef_t*)ip_header)->next_header == NEXT_HEADER_TCP){
            TCP_Typedef_t* pTCP =  (TCP_Typedef_t*)ip_header + IP6_HEADER_LENGTH; 
            return pTCP; 
        }
    }
    else if (ip_version == IPV4_VERSION){
        if (((IPV4_Typedef_t*)ip_header)->proto == NEXT_HEADER_TCP){
            TCP_Typedef_t* pTCP =  (TCP_Typedef_t*)ip_header + IP4_HEADER_LENGTH; 
            return pTCP; 
        }
    }
        else 
            return NULL; 
}

uint8_t is_http2(const unsigned char *ptr, uint32_t length) {
    if (length < HTTP2_FRAME_HEADER_SIZE) {
        return 0;
    }

    char type = ptr[3];
    printf("Type: %0x\n" ,type); 
    if ((length >= HTTP2_PREFACE_SIZE - 1) && 
        memcmp(ptr, HTTP2_PREFACE, HTTP2_PREFACE_SIZE - 1) == 0){
            return 1; 
    }
    if (type <= 9)
    {
        return 1;  
    }
    
    return 0;
}

uint8_t is_grpc(const unsigned char *http2_header, uint32_t length)
{
    for (unsigned char *i = http2_header; i <= http2_header + length - GRPC_PREFACE_SIZE; i++) {
        if (memcmp(i, GRPC_PREFACE, GRPC_PREFACE_SIZE) == 0) {
            return 1;            
        }
    }
    return 0;
}
