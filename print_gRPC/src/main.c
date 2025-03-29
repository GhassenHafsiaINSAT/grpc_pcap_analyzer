#include "pcap_parser_apis.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pcap file>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    pcap_t *handle;
    char errbuf[PCAP_ERRBUF_SIZE];

    handle = pcap_open_offline(filename, errbuf);
    if (handle == NULL) {
        fprintf(stderr, "Could not open file %s: %s\n", filename, errbuf);
        return 1;
    }
    
    link_type = pcap_datalink(handle);

    pcap_loop(handle, 0, packet_handler_wrapper, NULL); 

    pcap_close(handle);
    return 0;
}