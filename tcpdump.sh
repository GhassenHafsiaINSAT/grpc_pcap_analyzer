#!/bin/bash

# Capture network packets of the usb port

# We use sudo before executing tcpdump because we have to log in as root or sudoer

# -i is to filter the network packets, we want only the packets in usb interface 

# -c is to choose the number of packets  

# Capture the first 5 network packets and save them in a file named capture.pcap

sudo tcpdump -c 5 -i usb0 -w capture.pcap 



# read the capture file 

sudo tcpdump -r capture.pcap 



