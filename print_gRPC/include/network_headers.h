#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>

extern int link_type;

////////////////////////// SSL //////////////////////////
#define SSL_HEADER_LEN 16

typedef struct{
    uint16_t packet_type;  
    uint16_t address_type;  
    uint16_t address_len;   
    uint8_t address[8];     
    uint16_t protocol;      
}SSL_Typedef_t;

////////////////////////// ETHERNET //////////////////////////

#define ETHERNET_HEADER_LEN 14
#define ETHERTYPE_IPV6 0x86DD
#define ETHERTYPE_IPV4 0x0800

typedef struct{
    uint8_t dest_mac[6];
    uint8_t src_mac[6];
    uint16_t ethertype;
}ETHERNET_Typedef_t; 

////////////////////////// IPv4 //////////////////////////

#define IP4_HEADER_LEN 20

typedef struct{
    uint8_t version : 4;
    uint8_t ihl : 4;
    uint8_t tos;
    uint16_t len;
    uint16_t id;
    uint16_t flags : 3;
    uint16_t frag_offset : 13;
    uint8_t ttl;
    uint8_t proto;
    uint16_t csum;
    uint32_t saddr;
    uint32_t daddr;
} IPV4_Typedef_t;

////////////////////////// IPv6 //////////////////////////
#define IP6_HEADER_LENGTH 40
#define NEXT_HEADER_TCP 0x06

typedef struct{
    uint32_t version_tc_fl;   
    uint16_t payload_length;    
    uint8_t next_header;        
    uint8_t hop_limit;
    uint8_t src_addr[16];       
    uint8_t dest_addr[16];      
}IPV6_Typedef_t;

////////////////////////// TCP //////////////////////////

#define TCP_BASE_OFFSET 

typedef struct{
    uint16_t src_port;
    uint16_t dst_port;
    uint32_t seq_num;
    uint32_t ack_num;
    uint8_t data_offset;
    uint8_t flags;
    uint16_t window;
    uint16_t checksum;
    uint16_t urgent_pointer;
}TCP_Typedef_t;

////////////////////////// HTTP2 //////////////////////////

#define HTTP2_FRAME_HEADER_SIZE 9

typedef struct{
    uint32_t length : 24;
    uint8_t type;
    uint8_t flags;
    uint32_t reserved : 1;
    uint32_t stream_id : 31;
}HTTP2_Typedef_t;

typedef enum {
    FRAME_TYPE_DATA = 0x0,
    FRAME_TYPE_HEADERS = 0x1,
    FRAME_TYPE_PRIORITY = 0x2,
    FRAME_TYPE_RST_STREAM = 0x3,
    FRAME_TYPE_SETTINGS = 0x4,
    FRAME_TYPE_PUSH_PROMISE = 0x5,
    FRAME_TYPE_PONG = 0x6,
    FRAME_TYPE_GOAWAY = 0x7,
    FRAME_TYPE_WINDOW_UPDATE = 0x8,
    FRAME_TYPE_CONTINUATION = 0x9
} http2_frame_type_t;

unsigned char target_sequence[32];
const char http2_preface[24];

#endif //COMMON_H