#include <stdio.h>      // provides input output functions
#include <stdlib.h>     // provides standard utility functions
#include <pcap.h>       // provides functions for packet capture
#include <arpa/inet.h>  // Provides functions for converting IP addresses

void rcp_print(const u_char *packet, u_int length){
    if (length <11) 
    {printf("Packet is too short for rpc\n"); 
    return ;  
    }

    u_int version = packet[0]; 
    struct in_addr src_ip, dst_ip; 
    memcpy(&src_ip, packet + 1, 4); 
    memcpy(&dst_ip, packet + 5, 4); 
    u_int playload_length = ntohs(*(u_int16_t)(packet+9)); 
    
    printf("RCP Packet - Version %u, Source IP: %s, Destination IP: %s, playload length : %u", 
        version, inet_ntoa(src_ip), inet_ntoa(dst_ip), playload_length); 

    if (length > 11) {
        printf("Payload: ");
        for (u_int i = 11; i < length; i++) {
            printf("%02x ", packet[i]);
        }
        printf("\n");
    }
}

void rcp_handle(const u_char *packet, u_int length) {
    printf("RCP: ");
    rcp_print(packet, length);
}
