#ifndef _SOCKET_CLIENT_H_
#define _SOCKET_CLIENT_H_

#include <netinet/in.h>
#include "type.h"

/* C++ include C */
#ifdef __cplusplus
extern "C" {
#endif
#include "ringbuffer.h"
#include "protocol.h"
#ifdef __cplusplus
}
#endif


typedef enum
{
	STATE_DISABLE,
	STATE_DISCONNECT,
	STATE_CONNECTED,
	STATE_LOGIN,
}sockState_e;

struct clientInfo
{
	int fd;
	int protoHandle;
	sockState_e state;
	struct sockaddr_in 	srv_addr;		// server ip addr
	struct ringbuffer recvRingBuf;			// socket receive data ring buffer
	struct detect_info detectInfo;
	uint8_t packBuf[PROTO_PACK_MAX_LEN];		// protocol packet data buffer
	int packLen;
	uint8_t ack_buf[PROTO_PACK_MAX_LEN];
	uint8_t tmpBuf[PROTO_PACK_MAX_LEN];
	int identity;		// client_identity_e
};

int start_socket_client_task(void);


#endif	// _SOCKET_CLIENT_H_
