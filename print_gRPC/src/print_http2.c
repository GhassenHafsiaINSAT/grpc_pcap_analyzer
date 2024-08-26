#include "common.h"
const char http2_preface[] = {
    0x50, 0x52, 0x49, 0x20, 0x2a, 0x20, 0x48, 0x54, 
    0x54, 0x50, 0x2f, 0x32, 0x2e, 0x30, 0x0d, 0x0a,
    0x0d, 0x0a, 0x53, 0x4d, 0x0d, 0x0a, 0x0d, 0x0a
};
    
int is_http2(const unsigned char *ptr, int length) {
    if (length < HTTP2_FRAME_HEADER_SIZE) {
        return 0;
    }

    char type = ptr[3];
    printf("Type: %0x\n" ,type); 
    if (length >= (int)(sizeof(http2_preface) - 1) && 
        memcmp(ptr, http2_preface, sizeof(http2_preface) - 1) == 0)
    {
        printf("HELLO FROM HTTP2"); 
        return 1; 
    }
         
    if (type <= 9)
    {
        return 1;  
    }
    
    return 0;
}
