/*
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that: (1) source code
 * distributions retain the above copyright notice and this paragraph
 * in its entirety, and (2) distributions including binary code include
 * the above copyright notice and this paragraph in its entirety in
 * the documentation or other materials provided with the distribution.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND
 * WITHOUT ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, WITHOUT
 * LIMITATION, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE.
 */

/* \summary: Hypertext Transfer Protocol (HTTP) printer */

#include <config.h>
#include <string.h> 
#include "netdissect-stdinc.h"
#include "netdissect.h"

/*
 * Includes WebDAV requests.
 */
static const char *httpcmds[] = {
	"GET",
	"PUT",
	"COPY",
	"HEAD",
	"LOCK",
	"MOVE",
	"POLL",
	"POST",
	"BCOPY",
	"BMOVE",
	"MKCOL",
	"TRACE",
	"LABEL",
	"MERGE",
	"DELETE",
	"SEARCH",
	"UNLOCK",
	"REPORT",
	"UPDATE",
	"NOTIFY",
	"BDELETE",
	"CONNECT",
	"OPTIONS",
	"CHECKIN",
	"PROPFIND",
	"CHECKOUT",
	"CCM_POST",
	"SUBSCRIBE",
	"PROPPATCH",
	"BPROPFIND",
	"BPROPPATCH",
	"UNCHECKOUT",
	"MKACTIVITY",
	"MKWORKSPACE",
	"UNSUBSCRIBE",
	"RPC_CONNECT",
	"VERSION-CONTROL",
	"BASELINE-CONTROL",
	NULL
};

const unsigned char http2_preface[] = {
    0x50, 0x52, 0x49, 0x20, 0x2a, 0x20, 0x48, 0x54, 
    0x54, 0x50, 0x2f, 0x32, 0x2e, 0x30, 0x0d, 0x0a,
    0x0d, 0x0a, 0x53, 0x4d, 0x0d, 0x0a, 0x0d, 0x0a
};

const unsigned char target_sequence[] = {
    0x40, 0x0c, 0x63, 0x6f, 0x6e, 0x74, 0x65, 0x6e, 0x74, 0x2d, 0x74, 
    0x79, 0x70, 0x65, 0x10, 0x61, 0x70, 0x70, 0x6c, 0x69, 0x63, 0x61, 
    0x74, 0x69, 0x6f, 0x6e, 0x2f, 0x67, 0x72, 0x70, 0x63
};


    
int is_http2(const u_char *ptr, u_int length) {
    
	if (length < sizeof(http2_preface)) {
        return 0;
    }

    char type = ptr[3];
	
	if (length >= (int)(sizeof(http2_preface) - 1) && 
        memcmp(ptr, http2_preface, sizeof(http2_preface) - 1) == 0)
    {
        return 1; 
    }
         
    if (type <= 9)
    {
        return 1;  
    }
    
    return 0;
}


int is_grpc(const u_char *http2_header, u_int packet_len) {

    for (const unsigned char *i = http2_header; i <= http2_header + packet_len - sizeof(target_sequence); i++) {
        if (memcmp(i, target_sequence, sizeof(target_sequence) ) == 0){
            return 1;            
        }
    }

    return 0; 
  
}

void
http_print(netdissect_options *ndo, const u_char *pptr, u_int len)
{    if (is_http2(pptr, len)) {

        if (is_grpc(pptr, len)) {
		
            ND_PRINT("gRPC");

        } else {

            ND_PRINT("HTTP/2");
        }
        return;
    }

	else {
		ndo->ndo_protocol = "http2";
		txtproto_print(ndo, pptr, len, httpcmds, RESP_CODE_SECOND_TOKEN);
	
	}
}
