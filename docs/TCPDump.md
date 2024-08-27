# Tcpdump 

- Tcpdump is a packet sniffer, it captures traffic that passes through a machine.
  
- It operates on a packet level, it means it captures the actual packets flying in and out your computer.  
- You can save packets into files.
- You can apply filters on the packets, it means ignoring packets that you are not interested to see.
- To execute tcpdump command on terminal you should be logging in as root or sudoer.  

## Network interface 

- Use `ip a` or `ip address` to list the network interfaces. 

- You can find your computer's network interfaces under `/sys/class/net`:   
                1. `enp4s0`: 	Ethernet interface.  
                2. `lo`:	loopback interface, a virtual network interface that the system uses to communicate with itself.  
                3. `wlp3s0`: 	Wireless LAN (WI-FI) interface.  

## Capture Packets from specific interface 

```yaml 
tcpdump -i eth0
``` 

## Capture only N numbers of Packets

```yaml 
tcpdump -c 5 -i eth0
``` 

## Saving captured packets to a .pcap file 

```yaml 
tcpdump -w 0001.pcap
``` 
## Reading captured packet file

```yaml 
tcpdump -r 0001.pcap
``` 

## Capture IP Address packets

```yaml 
tcpdump -n
```  

## Capture Packet from a specific port 

```yaml 
tcpdump -i enp4s0 port 22
```  

## Capture packet from source IP

```yaml 
tcpdump src 192.168.0.2
``` 

## Capture Packets from destination IP

```yaml 
tcpdump dst 50.116.66.139
``` 

## Capture only TCP Packets

```yaml 
tcpdump tcp 
```

## Simple filtering 

```yaml 
tcpdump not port 22 
```
## Reading tcpdump's output

```yaml
16:34:05.991501 IP mrs09s16-in-f14.1e100.net.https > ghassen-VivoBook-ASUSLaptop-X571LI-X571LI.51422: Flags [P.], seq 1575:1785, ack 4216, win 698, options [nop,nop,TS val 340496177 ecr 1949757965], length 210
```
1. **Timestamp : `16:34:05.991501`**
   
    - It indicates the time at which the packet was captured. The format is `HH:MM:SS.microseconds`. 
2. **Protocol : `IP`**
    - It specifies the network protocol of the packet.
      
    - tcpdump understands very limited number of protocols.  
3. **Source and Destination Addresses : `mrs09s16-in-f14.1e100.net.https > ghassen-VivoBook-ASUSLaptop-X571LI-X571LI.51422`**
    - `mrs09s16-in-f14.1e100.net.https`: Source address (mrs09s16-in-f14.1e100.net) and port (https).
    - `ghassen-VivoBook-ASUSLaptop-X571LI-X571LI.51422`: Destination address (your computer's hostname) and port (51422).
4. **Flags: [P.]**
5.  **Length : `length 210`**
    - `210` : Length of the packet payload in bytes.  
