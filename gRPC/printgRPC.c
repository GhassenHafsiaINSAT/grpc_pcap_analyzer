/* this program uses libcalp to capture network packets and inspect them in order to identify gRPC traffic by looking for specific HTTP/2 indicators within the playload.  
*/

#include <pcap.h>               // inculdes functions for packet capture
#include <stdio.h>              // input/output
#include <stdlib.h>             // memory allocation     
#include <string.h>             // string manipulation 
#include <netinet/ip.h>         // provide structures for IP headers
#include <netinet/tcp.h>        // provide structures for TCP headers

#define SIZE_ETHERNET 14        // defines size of ethernet header 

/* Ethernet header */
struct ethernet_header {
    u_char ether_dhost[6]; /* Destination host address */
    u_char ether_shost[6]; /* Source host address */
    u_short ether_type;    /* type of encapsulated protocol*/
};

/* Callback function invoked by libpcap for every captured packet */
void got_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *packet) {
    const struct ethernet_header *ethernet;
    const struct ip *ip;
    const struct tcphdr *tcp;
    const char *payload;
    int size_ip;
    int size_tcp;
    int size_payload;


    ethernet = (struct ethernet_header*)(packet);
    // Access the destination MAC address
    u_char *destination = ethernet->dest_mac;

    // Access the source MAC address
    u_char *source = ethernet->src_mac;

    // Access the EtherType field
    u_short ether_type = ntohs(ethernet->ether_type);

    ip = (struct ip*)(packet + SIZE_ETHERNET);
    size_ip = ip->ip_hl * 4;
    if (size_ip < 20) {
        printf("Invalid IP header length: %u bytes\n", size_ip);
        return;
    }

    if (ip->ip_p != IPPROTO_TCP) {
        return; // Not TCP
    }

    tcp = (struct tcphdr*)(packet + SIZE_ETHERNET + size_ip);
    size_tcp = tcp->th_off * 4;
    if (size_tcp < 20) {
        printf("Invalid TCP header length: %u bytes\n", size_tcp);
        return;
    }

    payload = (u_char *)(packet + SIZE_ETHERNET + size_ip + size_tcp);
    size_payload = ntohs(ip->ip_len) - (size_ip + size_tcp);

    if (size_payload > 0) {
        // Check for HTTP/2 frames and gRPC-specific indicators in the payload
        if (strstr(payload, "application/grpc") != NULL) {
            printf("gRPC traffic detected\n");
        }
    }
}

int main(int argc, char *argv[]) {
    char *dev = NULL;
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle;
    char filter_exp[] = "tcp port 80 or tcp port 443"; // Adjust the filter for HTTP/2 traffic
    struct bpf_program fp;
    bpf_u_int32 net;

    if (argc == 2) {
        dev = argv[1];
    } else {
        dev = pcap_lookupdev(errbuf);
        if (dev == NULL) {
            fprintf(stderr, "Couldn't find default device: %s\n", errbuf);
            return(2);
        }
    }

    printf("Device: %s\n", dev);

    handle = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf);
    if (handle == NULL) {
        fprintf(stderr, "Couldn't open device %s: %s\n", dev, errbuf);
        return(2);
    }

    if (pcap_compile(handle, &fp, filter_exp, 0, net) == -1) {
        fprintf(stderr, "Couldn't parse filter %s: %s\n", filter_exp, pcap_geterr(handle));
        return(2);
    }

    if (pcap_setfilter(handle, &fp) == -1) {
        fprintf(stderr, "Couldn't install filter %s: %s\n", filter_exp, pcap_geterr(handle));
        return(2);
    }

    pcap_loop(handle, 0, got_packet, NULL);

    pcap_freecode(&fp);
    pcap_close(handle);

    return(0);
}
