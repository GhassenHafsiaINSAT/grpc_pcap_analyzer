#include "print_http2.h"
int is_http2_frame(const unsigned char *payload, int len) {
    if (len < 9)
        return 0; 
    
    // Check for HTTP/2 connection preface (first request in a connection)
    const char http2_preface[] = "PRI * HTTP/2.0\r\n\r\nSM\r\n\r\n";
    if (len >= sizeof(http2_preface) - 1 && 
        memcmp(payload, http2_preface, sizeof(http2_preface) - 1) == 0) {
        return 1; 
    }

    // Otherwise, check for valid HTTP/2 frame (length, type, flags, etc.)
    // Further checks might include frame type and flags.

    return 0;
}
