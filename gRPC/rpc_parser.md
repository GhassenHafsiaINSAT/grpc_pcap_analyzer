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


## Integer Types

    %d or %i: Signed integer
    %u: Unsigned integer
    %o: Unsigned octal
    %x: Unsigned hexadecimal (lowercase)
    %X: Unsigned hexadecimal (uppercase)
    %hd: Short signed integer
    %hu: Short unsigned integer
    %ld: Long signed integer
    %lu: Long unsigned integer
    %lld: Long long signed integer
    %llu: Long long unsigned integer

## Floating-Point Types

    %f: Floating-point number
    %e: Scientific notation (lowercase)
    %E: Scientific notation (uppercase)
    %g: Automatic choice between %f and %e
    %lf: Double floating-point number (though %f is typically used)

## Character and String Types

    %c: Single character
    %s: String (character array)

## Pointers

    %p: Pointer address (prints as a hexadecimal)

## Other

    %%: Prints a literal % character

## `ip_hdr` structure 