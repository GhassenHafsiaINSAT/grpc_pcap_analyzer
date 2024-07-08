## Main functions in `.pb.cc` and `.pb.h`: 
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
