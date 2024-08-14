### The minimum size of rpc packet is 11?
    - **the version**: 1 byte
    - **the sourceIP address**: 4 bytes
    - **the destinationIP address**: 4 bytes 
    - **the playload length**: 2  bytes 

## Networking layers 

1. **Ethernet layer**: data link layer whre network frames are transfered over physical media.  

2. **IP layer**: This is layer where packets are routed from source to destination. 

3. **TCP layer**: This is transport layer that ensures reliable data transmission. 

4. **HTTP/2 layer**: This is an application layer protocol that gRPC uses for transport.  

5. **gRPC layer**: This is an RPC framework that send and recieves messagers over HTTP/2.  

## Identifying gRPC traffic
the http tells the client or the server what type of data is sent, for gRPC 

1. **Capture Ethernet Frames**: Using tcpdump we can capture ethernet frames while reading directly from the network interface
2. **Extract IP packets**: Check if the etherent frame contains IP packet.  
3. **Extract TCP segments**: check the protocol field in IP packet to see if it indicates TCP (proto number 6).  
4. **Identify HTTP/2 traffic**: gRPC uses http/2 as transport protocol, HTTP traffic is usually on ports 80 (unsecured) and 443 (secured with SSL/TLS), look for http headers in TCP playload. 
5. **Check for gRPC indicators** 
- check for http headers that contain "content-type: application/grpc" 
- look for gRPC-specific metadata headers like "grpc-status" and "grpc-message".

// Check for HTTP/2 connection preface
        const unsigned char *http2_header = packet + ETHERNET_HEADER_LEN + ip_header_length + tcp_header_length;
        int remaining_len = length - (ETHERNET_HEADER_LEN + ip_header_length + tcp_header_length);

        // Handle HTTP/2 connection preface
        if (remaining_len >= 24 && memcmp(http2_header, "PRI * HTTP/2.0\r\n\r\nSM\r\n\r\n", 24) == 0) {
            http2_header += 24; // Skip connection preface
            remaining_len -= 24;
        }

        // Loop through the HTTP/2 frames
        while (remaining_len >= HTTP2_FRAME_HEADER_LEN) {
            uint32_t frame_length = (http2_header[0] << 16) | (http2_header[1] << 8) | http2_header[2];
            uint8_t frame_type = http2_header[3];

            // Check for DATA frame (type 0x0)
            if (frame_type == 0x0) {
                if (remaining_len >= (HTTP2_FRAME_HEADER_LEN + frame_length)) {
                    // Check for gRPC content type in the payload
                    if (frame_length >= GRPC_CONTENT_TYPE_LEN &&
                        memcmp(http2_header + HTTP2_FRAME_HEADER_LEN, GRPC_CONTENT_TYPE, GRPC_CONTENT_TYPE_LEN) == 0) {
                        print_packet_info(ip, tcp, timestamp);
                    }
                }
            }

            http2_header += HTTP2_FRAME_HEADER_LEN + frame_length;
            remaining_len -= HTTP2_FRAME_HEADER_LEN + frame_length;
        }
    }
}







if (ntohs(tcp->th_sport) != grpc_port || ntohs(tcp->th_dport) == grpc_port) {
        struct timespec ts;
        clock_gettime(CLOCK_REALTIME, &ts);
        char timestamp[100];
        strftime(timestamp, sizeof(timestamp), "%H:%M:%S", localtime(&ts.tv_sec));
        sprintf(timestamp + strlen(timestamp), ".%06ld", ts.tv_nsec / 1000); // Append microseconds

        print_packet_info(ip, tcp, timestamp);

        // Check for HTTP/2 connection preface
        const unsigned char *http2_header = packet + ETHERNET_HEADER_LEN + ip_header_length + tcp_header_length;
        int remaining_len = length - (ETHERNET_HEADER_LEN + ip_header_length + tcp_header_length);

        // Handle HTTP/2 connection preface
        if (remaining_len >= 24 && memcmp(http2_header, "PRI * HTTP/2.0\r\n\r\nSM\r\n\r\n", 24) == 0) {
            http2_header += 24; // Skip connection preface
            remaining_len -= 24;
        }

        // Loop through the HTTP/2 frames
        while (remaining_len >= HTTP2_FRAME_HEADER_LEN) {
            uint32_t frame_length = (http2_header[0] << 16) | (http2_header[1] << 8) | http2_header[2];
            uint8_t frame_type = http2_header[3];

            // Check for DATA frame (type 0x0)
            if (frame_type == 0x0) {
                if (remaining_len >= (HTTP2_FRAME_HEADER_LEN + frame_length)) {
                    // Check for gRPC content type in the payload
                    if (frame_length >= GRPC_CONTENT_TYPE_LEN &&
                        memcmp(http2_header + HTTP2_FRAME_HEADER_LEN, GRPC_CONTENT_TYPE, GRPC_CONTENT_TYPE_LEN) == 0) {
                        print_packet_info(ip, tcp, timestamp);
                    }
                }
            }

            http2_header += HTTP2_FRAME_HEADER_LEN + frame_length;
            remaining_len -= HTTP2_FRAME_HEADER_LEN + frame_length;
        }
    }






    test 
    if (ntohs(tcp->source) == 50051 || ntohs(tcp->dest) == 50051) {
            struct timespec ts;
            clock_gettime(CLOCK_REALTIME, &ts);
            char timestamp[100];
            strftime(timestamp, sizeof(timestamp), "%H:%M:%S", localtime(&ts.tv_sec));
            sprintf(timestamp + strlen(timestamp), ".%06ld", ts.tv_nsec / 1000); 
            


            // Check for HTTP/2 connection preface
            const unsigned char *http2_header = packet + 14 + ip_header_length + tcp_header_length;
            int remaining_len = length - (14 + ip_header_length + tcp_header_length);

            if (remaining_len >= 24 && memcmp(http2_header, "PRI * HTTP/2.0\r\n\r\nSM\r\n\r\n", 24) == 0) {
                http2_header += 24; // Skip connection preface
                remaining_len -= 24;
            }

            // Loop through the HTTP/2 frames
            while (remaining_len >= HTTP2_FRAME_HEADER_LEN) {
                uint32_t frame_length = (http2_header[0] << 16) | (http2_header[1] << 8) | http2_header[2];
                uint8_t frame_type = http2_header[3];

                // Check for DATA frame (type 0x0)
                if (frame_type == 0x0) {
                    if (remaining_len >= (HTTP2_FRAME_HEADER_LEN + frame_length)) {
                        // Check for gRPC content type in the payload
                        if (frame_length >= GRPC_CONTENT_TYPE_LEN &&
                            memcmp(http2_header + HTTP2_FRAME_HEADER_LEN, GRPC_CONTENT_TYPE, GRPC_CONTENT_TYPE_LEN) == 0) {
                            //print_packet_info(ip, tcp, timestamp);
                        }
                    }
                }

                http2_header += HTTP2_FRAME_HEADER_LEN + frame_length;
                remaining_len -= HTTP2_FRAME_HEADER_LEN + frame_length;
            }
        }