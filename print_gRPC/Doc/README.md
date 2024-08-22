## Ethernet header 
To extract Ethernet-related data, the following structure is used:

```c
struct ethernet_hdr {
    uint8_t dest_mac[6];
    uint8_t src_mac[6];
    uint16_t ethertype;
};
```

- **Structure Details**:

    - **Destination MAC Address**: 6 bytes
    - **Source MAC Address**: 6 bytes
    - **EtherType**: 2 bytes, indicating the protocol encapsulated in the payload (e.g., IPv4, IPv6).

## IPv4 header
```c
struct ip4_hdr {
    uint8_t version_ihl;
    uint8_t tos;
    uint16_t total_length;
    uint16_t identification;
    uint16_t flags_fragment_offset;
    uint8_t ttl;
    uint8_t protocol;
    uint16_t checksum;
    uint32_t src_addr;
    uint32_t dst_addr;
};
```

- **Structure Details**:
    - **version_ihl** (8 bits)
        - Version (4 bits): Identifies the IP version. For IPv4, this value is 4.
        Internet Header 
        - Length (IHL) (4 bits): Specifies the length of the IP header in 32-bit words. The minimum value is 5, corresponding to a 20-byte header, and the maximum is 15 (60 bytes).

    - **tos (Type of Service)** (8 bits): Differentiated Services Code.  

    - **total_length** (16 bits): Represents the entire length of the IP packet (header + data), in bytes. The minimum size is 20 bytes (header only), and the maximum is 65,535 bytes.

    - **identification** (16 bits): A unique value assigned to each packet. If the packet is fragmented, this value helps in reassembling the fragments into the original packet.

    - **flags_fragment_offset** (16 bits)
            

    - **ttl (Time to Live)** (8 bits): Specifies the maximum number of hops (routers) the packet can pass through. Each router decreases this value by 1. When TTL reaches 0, the packet is discarded.

    - **protocol** (8 bits): Identifies the protocol used in the data portion of the IP packet (e.g., TCP is 6, UDP is 17).

    - **checksum** (16 bits): A checksum for error-checking the header. Ensures the integrity of the header data.

    - **src_addr** (32 bits): The source IP address of the packet.

    - **dst_addr** (32 bits): The destination IP address of the packet.

## IPv6 header

```c
struct ipv6_hdr {
    uint32_t version_tc_fl;   
    uint16_t payload_length;    
    uint8_t next_header;        
    uint8_t hop_limit;
    uint8_t src_addr[16];       
    uint8_t dest_addr[16];      
};
```