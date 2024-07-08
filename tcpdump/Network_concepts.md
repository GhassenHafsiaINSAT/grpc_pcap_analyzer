# Networking Fundamentals

## Table of Contents
1. [Introduction to Networking](#introduction-to-networking)
2. [OSI and TCP/IP Models](#osi-and-tcpip-models)
3. [Network Packets](#network-packets)
4. [Address Resolution Protocol (ARP)](#address-resolution-protocol-arp)
5. [Domain Name System (DNS)](#domain-name-system-dns)
6. [Encapsulation Process](#encapsulation-process)
7. [Application Layer Functions](#application-layer-functions)

## Introduction to Networking

- **Network Definition**: Computers communicating with each other to share data.

- **Internet Components**: Routers, switches, firewalls.
- **Ethernet**: Typically used for connecting devices to a network via switches.
- **Switch**: Connects multiple devices together to form a network and operates at Layer 2 of the OSI model using MAC addresses.
- **Router**: Connects two or more networks and operates at Layer 3 using IP addresses.
- **Firewall**: Protects your network by controlling incoming and outgoing network traffic.
- **Wireless Access Point**: Enables wireless connectivity for devices.
- **Hub**: Basic device that sends messages to all connected devices, considered 'dumb'.
- **Switch Functionality**: Knows the Layer 2 (MAC) address of each connected device; MAC addresses are unique and immutable.
- **Network Layers**:
  - **Layer 1 (Physical Layer)**: Physical aspects like electrical wires; includes hubs and repeaters.
  - **Layer 2 (Data Link Layer)**: Handles switches, bridges, and frames.
  - **Layer 3 (Network Layer)**: Deals with IP addresses and routers; routers connect networks.

## OSI and TCP/IP Models

- **TCP/IP Model Layers**:
  
  - **Physical Layer**: Ethernet cables.
  - **Network Layer**: IP addresses and routers.
  - **Transport Layer**: TCP (reliable) and UDP (faster).
  - **Application Layer**: Protocols used in applications (e.g., web browsers).
- **OSI Model Layers**:
  
  - **Layer 7**: Application
  - **Layer 6**: Presentation
  - **Layer 5**: Session
  - **Layer 4**: Transport
  - **Layer 3**: Network
  - **Layer 2**: Data Link
  - **Layer 1**: Physical

## Network Packets
### What is a Packet?

- Data sent over computers is segmented into packets (small segments of a larger message).
  
- These packets are combined by the device that receives them.
- **Datagram**: An alternative term for "packet".

### Why Use Packets?
- Allows multiple connections and multiple exchanges of data at the same time.

### What is a Packet Header?

- A packet header contains information about the packet, such as origin and destination IP addresses.
  
- A packet consists of two portions: the Header and the Payload.
- The payload carries a small piece of the data.

### Packet Sniffing
- The practice of capturing and analyzing packets of data as they travel over a computer network.

### Networking Protocol
- A protocol is a standardized way of formatting data so that any computer can interpret the data.
- Most packets traversing the internet will include a Transmission Control Protocol (TCP) header and an Internet Protocol (IP) header.

### Network Traffic
- Network traffic refers to the packets passing through a network.
- It indicates the amount of data moving across a computer network at any given time.

## Address Resolution Protocol (ARP)
- **Purpose**: Translates IP addresses into MAC addresses to help devices locate each other on a local network.
- **IP Address**: Used for routing data across networks.
- **MAC Address**: Unique identifier assigned to network devices.

## Domain Name System (DNS)
- **Purpose**: Translates domain names (e.g., www.example.com) into IP addresses (e.g., 192.0.2.1) to facilitate communication over the internet.

### DNS Query
- A DNS query is a demand for information sent from a user's computer to a DNS server, asking for the IP address associated with a domain name.

## Encapsulation Process
- **Definition**: Adding a header to your data as it moves down the network stack.
  
- **Steps**:
  - **Application Layer**: Data.
  - **Transport Layer**: Data + header (TCP/UDP) = Segment.
  - **Network Layer**: Data + header + IP address = Packet (handled by routers).
  - **Data Link Layer**: Data + header + IP address + MAC address = Frame (handled by switches).

## Application Layer Functions
- **Functions**:
  
  - Determining whether adequate resources exist for communication.
  - Managing communication between applications.
  - Directing data to the correct program.
