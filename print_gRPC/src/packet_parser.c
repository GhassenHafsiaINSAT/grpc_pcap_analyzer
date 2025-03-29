#include "pcap_parser_apis.h"

void parse_packet(const unsigned char *packet, uint32_t length, int link_type) {
    if (length < ETHERNET_HEADER_LEN) 
        return;  

    void* ip_header;  
    ip_header = get_ip_header(packet); 
    uint8_t ip_version = check_ip_version(ip_header); 
    TCP_Typedef_t* tcp = check_tcp(ip_header, ip_vesion); 
    if(tcp == NULL)
        return tcp; 
    else {

        uint32_t tcp_header_length = ((tcp->data_offset >> 4) & 0x0F) * 4;
        uint32_t ip6_playload_len = ntohs(ip6->payload_length); 
        uint32_t remaining_len = ip6_playload_len - tcp_header_length;
        const unsigned char *checker = (const unsigned char *)tcp + tcp_header_length;
                
        if (is_http2(checker, remaining_len)){

            if (is_grpc(checker, remaining_len)){
                print_packet_info(ip6, tcp, ip_version, (const unsigned char*)"gRPC");
                return; 
            }
            print_packet_info(ip6, tcp, ip_version, (const unsigned char*)"HTTP/2");
            return; 
        }
            
        print_packet_info(ip6, tcp, ip_version, (const unsigned char*)"TCP");
        return;         
        } 
    }              
