## Overview 
- gRPC  uses by default protocol buffers as both its Interface Definition Language (IDL) and its underlaying message interchange format.  

## Working with protocol buffers

- Protocol buffers are structered as messages, where each message containing series of name-value pairs called fields.  

```proto
message Person {
  string name = 1; 
  int32 id = 2; 
  bool checked = 3; 
}
```

- Once you have specified your data structures, you use the protocol buffer compiler `protoc` to generate data access classes in your preferred language from your proto definition.   

## Data access classes methods

1. **Constructors and destructors** : 
 
    - `MyMessage::MyMessage()`
    - `MyMessage::~MyMessage()`

2. **Serialization Functions** :

    - `MyMessage::SerializeToString(std::string* output) const`

3. **Deserialization Function** :

     - `MyMessage::ParseFromString(const std::string& data)`

4. **Utility Functions** :
    
    - `int ByteSize() const;`:       Returns the size of serialized message.
    - `void clear();`:               Clears the message, resetting all the fields to their default values.
    - `bool IsInitialized() const;`: Checks if all required fields have been set.  

5. **Getters**
     
  - `MyMessage::id() const`
  - `MyMessage::name() const`

6. **Setters**
   
  - `MyMessage::set_id(int32_t value)`
  - `MyMessage::set_name(const std::string& value)`


## gRPC definition 

```proto

service greeter{
  rpc sendresponse (HelloRequest) returns (HelloReplay){} 
}

message HelloRequest{
  string name = 1; 
}

message HelloReplay{
  int32 id = 1; 
}
```

- gRPC uses `protoc` with a special gRPC plugin to generate code from your proto file, as well as the regular protocol buffer for populating, serializing and retrieving your message types.  

## Protocol buffer versions

- Why using proto3 instead of proto2?
  - proto3 lets you use the full range of gRPC supported languages.  
  - avoiding compatibility with proto2 clients talking to proto3 servers and vice versa.  