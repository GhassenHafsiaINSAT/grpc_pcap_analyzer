#include "common.h"

void process_packet(const unsigned char *packet, int length) {

    struct ethernet_hdr* eth = print_ethernet(packet, length); 
    
    if (eth->ethertype == ETHERTYPE_IPV6){

        struct ipv6_hdr* ip6 = print_ip6(packet, length); 
        
        if (ip6->next_header == NEXT_HEADER_TCP){

            struct tcp_hdr* tcp = print_tcp(packet,length);
            
            int tcp_header_length = ((tcp->data_offset >> 4) & 0x0F) * 4;
            int ip6_playload_len = ntohs(ip6->payload_length); 
            int remaining_len = ip6_playload_len - tcp_header_length ;
            
            if (remaining_len < HTTP2_FRAME_HEADER_SIZE){ 
                pritnf("Data is too short to be an HTTP/2 frame.\n"); 
                print_packet_info(ip6, tcp, "TCP");
                return; 
            }
            else {
                int packet_len = length;
                unsigned char *http2_header = (unsigned char *)packet + ETHERNET_HEADER_LEN + 40 + tcp_header_length;
                
                if(is_http2_frame(http2_header, packet_len) == 1){
                    if (check_grpc_content_type(http2_header, packet_len) == 1){
                         print_packet_info(ip6, tcp, "gRPC");
                         return; 
                    }
                    else { 
                        print_packet_info(ip6, tcp, "HTTP/2");
                        return; 
                    }
                }
                else{
                    print_packet_info(ip6, tcp, "HTTP");
                    return; 
                }
            }
            
        }
            

    }
}
   /* else {

        struct ip4_hdr *ip4 = (struct ip4_hdr*)(packet + ETHERNET_HEADER_LEN); 

        int len_ip4_hdr = htons(ip4->total_length); 
        char src_ip[INET_ADDRSTRLEN], dst_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(ip4->src_addr), src_ip, INET_ADDRSTRLEN);
        inet_ntop(AF_INET, &(ip4->dst_addr), dst_ip, INET_ADDRSTRLEN);
        printf("Source IP4: %s\n", src_ip);
        printf("Destination IP4: %s\n", dst_ip);

        struct tcp_hdr *tcp = (struct tcp_hdr*)(packet + ETHERNET_HEADER_LEN + len_ip4_hdr); 
    }*/


