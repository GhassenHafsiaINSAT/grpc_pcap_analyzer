#include "common.h"


void process_packet(const unsigned char *packet, int length) {
    if (length < ETHERNET_HEADER_LEN) 
        return;  
    struct ethernet_hdr* eth = print_ethernet(packet); 

    if (ntohs(eth->ethertype) == ETHERTYPE_IPV6){

        struct ipv6_hdr* ip6 = print_ip6(packet); 
        
        if (ip6->next_header == NEXT_HEADER_TCP){

            struct tcp_hdr* tcp = print_tcp(packet);
            //print_tcp_info(tcp);
            
            int tcp_header_length = ((tcp->data_offset >> 4) & 0x0F) * 4;
            int ip6_playload_len = ntohs(ip6->payload_length); 
            int remaining_len = ip6_playload_len - tcp_header_length ;
            unsigned char *ptr = (unsigned char *)packet + ETHERNET_HEADER_LEN + 40 + tcp_header_length;
            
            if (is_http2(ptr, remaining_len)){

                if (check_grpc_content_type(ptr, remaining_len) == 1){
                    print_packet_info(ip6, tcp, (const unsigned char*)"gRPC");
                    return; 
                }
                
                else { 
                    print_packet_info(ip6, tcp, (const unsigned char*)"HTTP/2");
                    return; 
                }
            }
            else {
                print_packet_info(ip6, tcp, (const unsigned char*)"TCP");
                return;                 
                
            }           
        }
    }

   else if (ntohs(eth->ethertype) == ETHERTYPE_IPV4) {

        struct ipv4_hdr* ip4 = print_ip4(packet); 
        int ip4_payload_len = ntohs(ip4->len) - IP4_HEADER_LEN;
        
        if (ip4->proto == 0x06){

            struct tcp_hdr* tcp = print_tcp(packet);
            
            int tcp_header_length = ((tcp->data_offset >> 4) & 0x0F) * 4;
            int remaining_len = ip4_payload_len - tcp_header_length ;
            unsigned char *ptr = (unsigned char *)packet + ETHERNET_HEADER_LEN + 40 + tcp_header_length;
            
            if (is_http2(ptr, remaining_len)){

                if (check_grpc_content_type(ptr, remaining_len) == 1){
                    //print_packet_info(ip4, tcp, (const unsigned char*)"gRPC");
                    return; 
                }
                
                else { 
                    //print_packet_info(ip4, tcp, (const unsigned char*)"HTTP/2");
                    return; 
                }
            }
            else {
                //print_packet_info(ip4, tcp, (const unsigned char*)"TCP");
                return;                 
                
            }           
        }
    } 
}




