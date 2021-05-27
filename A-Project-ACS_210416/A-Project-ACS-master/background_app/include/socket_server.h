#ifndef _SOCKET_SERVER_H_
#define _SOCKET_SERVER_H_

#include <netinet/in.h>

/* C++ include C */
#ifdef __cplusplus
extern "C" {
#endif
#include "ringbuffer.h"
#include "protocol.h"
#ifdef __cplusplus
}
#endif

#define MAX_CLIENT_NUM 				2
#define MAX_LISTEN_NUM 				5
#define RECV_BUFFER_SIZE			PROTO_PACK_MAX_LEN
#define SEND_BUFFER_SIZE			PROTO_PACK_MAX_LEN


struct clientInfo
{
	int fd;
	int protoHandle;
	struct sockaddr_in addr;
	struct ringbuffer recvRingBuf;			// socket receive data ring buffer
	struct detect_info detectInfo;
	uint8_t packBuf[PROTO_PACK_MAX_LEN];		// protocol packet data buffer
	int packLen;
	uint8_t ack_buf[PROTO_PACK_MAX_LEN];
	uint8_t tmpBuf[PROTO_PACK_MAX_LEN];
	int identity;		// client_identity_e
};

struct serverInfo
{
	int fd;
	int client_cnt;
	struct sockaddr_in 	srv_addr;		// server ip addr
	struct clientInfo	client[MAX_CLIENT_NUM];
	uint8_t client_used[MAX_CLIENT_NUM];
};


int start_socket_server_task(void);


#endif	// _SOCKET_SERVER_H_
