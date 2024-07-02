# Tcpdump 

- Tcpdump captures network traffic and prints it out for you.  

## Network interface 

- Use `ip a` or `ip address` to list the network interfaces. 

- You can find your computer's network interfaces under `/sys/class/net`:   
                1. `enp4s0`: 	Ethernet interface.  
                2. `lo`:	loopback interface, a virtual network interface that the system uses to communicate with itself.  
                3. `wlp3s0`: 	Wireless LAN (WI-FI) interface.  

## Capture Packets from specific interface 

```bash 
tcpdump -i eth0
``` 

## Capture only N numbers of Packets

```bash 
tcpdump -c 5 -i eth0
``` 

## Saving captured packets to a .pcap file 

```bash 
tcpdump -w 0001.pcap
``` 
## Reading captured packet file

```bash 
tcpdump -r 0001.pcap
``` 

## Capture IP Address packets

```bash 
tcpdump -n
```  

## Capture Packet from a specific port 

```bash 
tcpdump -i enp4s0 port 22
```  

### Capture packet from source IP
```bash 
tcpdump src 192.168.0.2
``` 

### Capture Packets from destination IP
```bash 
tcpdump dst 50.116.66.139
``` 

### Capture only TCP Packets
```bash 
tcpdump tcp 
``` 
