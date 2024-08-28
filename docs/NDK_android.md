## NDK

- The Native Development Kit is a set of tools allowing you to embed C or C++ (native code) into your Android apps

## Concepts

- You should have an understanding of the following components as you build your app: 
    - **Native shared libraries `.so`**: are a collection of compiled code that can be loaded and used by multiple programs simultaniously, they are dynamic, linked to the application at runtime

    - **Native static libraries `.a`**: are a collection of object files that are linked directly into the application at compile time, the library becomes part of the executable, and eahc application using the library has its own copy of it.

    - **Application Binary Interface (ABI)**: An ABI is a set of rules and ocnventions of how binary code interacts at the machine level, it defines things like how functions are called, how arguments are passed, how return values are handled, how libraries interact in binary format.  
    ABI ensures that compiled code works together regardless of which compiler or language was used to create it, deiffrent operating systems and processor architectures have their own ABIs.  

## Build your project 

- The Make-based ndk-build
- CMake 
- Standalone toolchains (with configure-based projects)

