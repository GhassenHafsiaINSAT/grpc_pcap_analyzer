### The minimum size of rpc packet is 11?
    - **the version**: 1 byte
    - **the sourceIP address**: 4 bytes
    - **the destinationIP address**: 4 bytes 
    - **the playload length**: 2  bytes 

### Converting Playload length : 
    - The playload is a 2-byte integer value, when transmitted over the network, it is in network byte order (big-endian), we need to convert it from network byte order to host byte order to correctly interpret this value on host machine.  

    - `inet_ntoa` converts the binary IP address to a dotted-decimal string for readability
### Why Not Convert Other Fields?

    - **Version**: It is a single byte, so byte order conversion is unnecessary.
    - **Source and Destination IP Addresses**: These are handled by the `inet_ntoa` function, which converts the binary IP address to a readable string. The IP address itself is treated as a sequence of bytes, so explicit conversion is not required.


### `struct in_addr`

```c
struct in_addr {
    unit32_t s_addr;    
};
```

- `unit32_t` is a 32 bit integer that holds IPv4 address, the address is stored in network byte order.

- The `struct in_addr` is used for setting up Socket addresses and IP address conversion.  