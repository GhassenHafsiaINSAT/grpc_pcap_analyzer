## RPC
- A local procedure call is a function call within a procedure to execute some code.
- a remote procedure call enables machine to invoke code on another machine.

## gRPC
- gRPC is an open source remote procedure call framework created by google in 2016

- gRPC is a popular implementation of RPC
- gRPC uses Protocol Buffers to encode and send data over the wire by default.
- A gRPC service is also defined in a proto file by specifying RPC methods, parameters and return types
- gRPC uses HTTP/2 streams, it allows multiple streams of messages over a single long-lived TCP connection.  

## gRPC Network Packet Encapsulation 
1. **Application layer**: at this layer, the grpc protocol operates, grpc messages are serialized using protocol buffers.  
2. **Presentation layer**: grpc does not use presentation layer as it uses protobuf for serialization.  
3. **Session layer**: grpc does not itself manage sessions, but it relies on HTTP/2 for connection management.  
4. **Transport layer**: HTTP/2 uses TCP at the transport layer.  
5. **Network layer**: The packet is encapsulated in IP packet (IPv4 or IPv6)
6. **data link layer**: the IP packet is encapsultaed inan ethernet frame.  