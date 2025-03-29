#include "pcap_parser_apis.h"

IPV4_Typedef_t* get_ip4(const unsigned char *packet){    

        switch (link_type){
                case DLT_EN10MB:
                        IPV4_Typedef_t* pIPV4 = (IPV4_Typedef_t*)(packet + ETHERNET_HEADER_LEN);
                        return pIPV4;  
                
                case DLT_LINUX_SLL:
                        IPV4_Typedef_t* pIPV4 = (IPV4_Typedef_t*)(packet + SSL_HEADER_LEN);
                        return pIPV4; 

                default: 
                        return NULL
        }  
}

IPV6_Typedef_t* get_ip6(const unsigned char *packet, int link_type){    

        switch (link_type){
                
                case DLT_EN10MB:
                        IPV6_Typedef_t* pIPV6 = (IPV6_Typedef_t*)(packet + ETHERNET_HEADER_LEN);
                        return pIPV6;  
                
                case DLT_LINUX_SLL:
                        IPV6_Typedef_t* pIPV6 = (IPV6_Typedef_t*)(packet + SSL_HEADER_LEN);
                        return pIPV6; 

                default: 
                        return NULL
        }   
}

TCP_Typedef_t* get_tcp(const unsigned char *packet, uint16_t protocol){
    if (ntohs(protocol) == ETHERTYPE_IPV6){
        IPV6_Typedef_t* ip6 = get_ip6(packet, link_type);
        if (ip6->next_header == NEXT_HEADER_TCP){
            TCP_Typedef_t* pTCP; 
           TCP_Typedef_t* pTCP = (TCP_Typedef_t*)(packet + IP6_HEADER_LENGTH); 
            return pTCP; 
        }
    }
    else if (ntohs(protocol) == ETHERTYPE_IPV4){
        IPV4_Typedef_t* ip4 = get_ip4(packet, link_type);
        if (ip4->proto == NEXT_HEADER_TCP){
            TCP_Typedef_t* pTCP; 
            TCP_Typedef_t* pTCP = (TCP_Typedef_t*)(packet + IP4_HEADER_LEN); 
            return pTCP; 
        }
    }
    else {
        return NULL;
    } 
}

int is_http2(const unsigned char *ptr, int length) {
    if (length < HTTP2_FRAME_HEADER_SIZE) {
        return 0;
    }

    char type = ptr[3];
    printf("Type: %0x\n" ,type); 
    if (length >= (int)(sizeof(http2_preface) - 1) && 
        memcmp(ptr, http2_preface, sizeof(http2_preface) - 1) == 0){
            return 1; 
        }
         
    if (type <= 9)
    {
        return 1;  
    }
    
    return 0;
}

int is_grpc(unsigned char *http2_header, int packet_len)
{
    for (unsigned char *i = http2_header; i <= http2_header + packet_len - sizeof(target_sequence); i++) {
        if (memcmp(i, target_sequence, sizeof(target_sequence)) == 0) {
            return 1;            
        }
    }

    return 0;
}

uint16_t get_physical_proto(const unsigned char* packet, int link_type){    
    
    switch (link_type) {
        case DLT_EN10MB:
            ETHERNET_Typedef_t* pETHERNET = (ETHERNET_Typedef_t*)packet;
            return pETHERNET->ethertype; 
        
        case DLT_LINUX_SLL:
            SSL_Typedef_t* pSLL = (SSL_Typedef_t*)packet;
            return pSLL->protocol; 
        
        default:
            printf("Unknown or unsupported link-layer type: %d\n", link_type);
            return 0; 
    }     
}

void parse_packet(const unsigned char *packet, int length, int link_type) {
    if (length < ETHERNET_HEADER_LEN) 
        return;  

    uint16_t protocol = get_physical_proto(packet, link_type); 
    if (protocol == 0) return; 
    else {

        struct tcp_hdr* tcp = parse_tcp(packet, protocol);

        int tcp_header_length = ((tcp->data_offset >> 4) & 0x0F) * 4;
        int ip6_playload_len = ntohs(ip6->payload_length); 
        int remaining_len = ip6_playload_len - tcp_header_length ;
        unsigned char *checker = (unsigned char *)tcp + tcp_header_length;
                
        if (is_http2(checker, remaining_len)){

            if (is_grpc(checker, remaining_len)){
                print_packet_info(ip6, tcp, (const unsigned char*)"gRPC");
                return; 
            }
            print_packet_info(ip6, tcp, (const unsigned char*)"HTTP/2");
            return; 
        }
            
        print_packet_info(ip6, tcp, (const unsigned char*)"TCP");
        return;         
        }               
}