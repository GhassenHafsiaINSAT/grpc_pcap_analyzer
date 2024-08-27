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

    - **flags_fragment_offset** (16 bits).  
            
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

- **`uint32_t version_tc_fl`**: Combines IPv6 version, traffic class, and flow label.
- **`uint16_t payload_length`**: Length of the payload in bytes.
- **`uint8_t next_header`**: Identifies the type of the next header (e.g., TCP, UDP).
- **`uint8_t hop_limit`**: Maximum number of hops the packet can pass through.
- **`uint8_t src_addr[16]`**: Source IPv6 address (128-bit).
- **`uint8_t dest_addr[16]`**: Destination IPv6 address (128-bit).

## TCP Header (`struct tcp_hdr`)
```c
struct tcp_hdr {
    uint16_t src_port;
    uint16_t dst_port;
    uint32_t seq_num;
    uint32_t ack_num;
    uint8_t data_offset;
    uint8_t flags;
    uint16_t window;
    uint16_t checksum;
    uint16_t urgent_pointer;
};
```
- **`uint16_t src_port`**: Source port number.
- **`uint16_t dest_port`**: Destination port number.
- **`uint32_t seq_num`**: Sequence number of the first byte in this segment.
- **`uint32_t ack_num`**: Acknowledgment number, if ACK flag is set.
- **`uint8_t data_offset`**: Size of the TCP header.
- **`uint8_t flags`**: Control flags (e.g., SYN, ACK, FIN).
- **`uint16_t window`**: Size of the sender's receive window.
- **`uint16_t checksum`**: Checksum for error-checking header and data.
- **`uint16_t urgent_pointer`**: Indicates urgent data, if URG flag is set.


## HTTP/2 header

This structure defines the header for any HTTP/2 frame.  

```c
struct http2_header {
    uint32_t length;
    uint8_t type;
    uint8_t flags;
    uint32_t stream_id;
};
```

- **`uint32_t length`**: The length of the payload, (only the lower 24 bits of the 32-bit value are used).  

- **`uint8_t type`**: The type of frame being sent, which corresponds to one of the values in `http2_frame_type_t`.  

- **`uint8_t flags`**: Various flags that modify the frame's behavior.  

- **`uint32_t stream_id`**: The identifier of the stream to which this frame belongs.  

### HTTP/2 Frame Types
- This enumeration defines the various types of frames that can be transmitted in an HTTP/2 connection.  
```c
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
```
- **FRAME_TYPE_DATA (0x0)**: Carries payload data for a request or response.  

- **FRAME_TYPE_HEADERS (0x1)**: Carries HTTP headers, initiating a new stream or continues a set of headers.  

- **FRAME_TYPE_PRIORITY (0x2)**: Specifies the priority of a stream, to manage bandwidth.  

- **FRAME_TYPE_RST_STREAM (0x3)**: Closes a stream prematurely.  

- **FRAME_TYPE_SETTINGS (0x4)**: Configures parameters that affect the entire connection, like flow control options and maximum frame sizes.  

- **FRAME_TYPE_PUSH_PROMISE (0x5)**: Reserves a stream for future use, allowing the server to push responses to the client without an explicit request.  

- **FRAME_TYPE_PONG (0x6)**: Confirms receipt of a `PING` frame, used for keeping the connection alive and measuring latency.  

- **FRAME_TYPE_GOAWAY (0x7)**: Shuts down an HTTP/2 connection.  

- **FRAME_TYPE_WINDOW_UPDATE (0x8)**: Manages flow control, Adjusting the window size, which controls the amount of data that can be sent.  

- **FRAME_TYPE_CONTINUATION (0x9)**: Continues a sequence of header block fragments, used when headers are too large to fit in a single frame.  



