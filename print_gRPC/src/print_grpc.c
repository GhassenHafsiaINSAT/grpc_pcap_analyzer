#include "print_grpc.h"

int check_grpc_content_type(unsigned char *http2_header, int packet_len) {

    for (unsigned char *i = http2_header; i <= http2_header + packet_len - sizeof(target_sequence); i++) {
        if (memcmp(i, target_sequence, sizeof(target_sequence)) == 0) {
            return 1; 
        }
    }
    return 0; 
}
