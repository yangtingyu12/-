#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "socket_client.h"
#include "mainwindow.h"


/* C++ include C */
#ifdef __cplusplus
extern "C" {
#endif
#include "ringbuffer.h"
#include "capture.h"
#ifdef __cplusplus
}
#endif


#define RECV_BUFFER_SIZE			(1 *1024 *1024)
#define SEND_BUFFER_SIZE			(1 *1024 *1024)
#define HEARTBEAT_INTERVAL_S		10

struct clientInfo client_info;
int global_seq;

extern struct main_mngr_info main_mngr;


int client_0x01_login(struct clientInfo *client, uint8_t *data, int len, uint8_t *ack_data, int size, int *ack_len)
{
	int ret = 0;

	/* return value */
	memcpy(&ret, data, 4);
	if(ret == 0)
	{
		client->state = STATE_LOGIN;
		main_mngr.work_state = WORK_STA_NORMAL;
		printf("Congratulation! Login success.\n");

#if defined(MANAGER_CLIENT_ENABLE) && defined(USER_CLIENT_ENABLE)
		client->identity = IDENTITY_ROOT;
		main_mngr.mngr_handle = client->protoHandle;
		main_mngr.user_handle = client->protoHandle;
		/* get user list from server(backbround app) */
		proto_0x07_getUserList(client->protoHandle);
#elif MANAGER_CLIENT_ENABLE
		client->identity = IDENTITY_MANAGER;
		main_mngr.mngr_handle = client->protoHandle;
		/* get user list from server(backbround app) */
		proto_0x07_getUserList(client->protoHandle);
#else
		client->identity = IDENTITY_USER;
		main_mngr.user_handle = client->protoHandle;
#endif
	}

	return 0;
}

int client_0x03_heartbeat(struct clientInfo *client, uint8_t *data, int len, uint8_t *ack_data, int size, int *ack_len)
{
	struct tm *ptm;
	struct tm local_info;
	struct tm utc_info;
	struct timeval tv;
	time_t getTime;
	uint32_t svrTime;
	int hour_diff;
	int tmplen = 0;
	int ret;

	if(data==NULL || len<=0)
		return -1;

	memcpy(&ret, data +tmplen, 4);
	tmplen += 4;

	/* bejing time */
	memcpy(&svrTime, data +tmplen, 4);
	tmplen += 4;

	/* check timezone */
	/* Attention: localtime() and gmtime() return pointer is the same memory(shared).  */
	getTime = time(NULL);
	ptm = localtime(&getTime);
	memcpy(&local_info, ptm, sizeof(struct tm));
	ptm = gmtime(&getTime);
	memcpy(&utc_info, ptm, sizeof(struct tm));

	/* differ from utc time */
	hour_diff = (local_info.tm_yday*24 +local_info.tm_hour) - (utc_info.tm_yday*24 +utc_info.tm_hour);
	/* differ from bejing time */
	hour_diff = 8 -hour_diff;

	/* synchronize system time */
	if(abs(time(NULL) -hour_diff*3600 - svrTime) >= +3)
	{
		svrTime += hour_diff*3600;
		tv.tv_sec = svrTime;
		tv.tv_usec = 0;
		ret = settimeofday(&tv , NULL);
		printf("synchronize system time[%d], ret=%d\n", svrTime, ret);
	}

	if(ack_len != NULL)
		*ack_len = 0;

	return 0;
}

int client_0x04_switchWorkSta(struct clientInfo *client, uint8_t *data, int len, uint8_t *ack_data, int size, int *ack_len)
{
	int state = 0;

	/* work state */
	memcpy(&state, data, 4);

	main_mngr.work_state = (workstate_e)state;
	
	return 0;
}

int client_0x05_addUser(struct clientInfo *client, uint8_t *data, int len, uint8_t *ack_data, int size, int *ack_len)
{
	char username[USER_NAME_LEN] = {0};
	int userId = 0;
	int userCnt = 0;
	int tmplen = 0;
	int i;

	/* user count */
	memcpy(&userCnt, data, 4);
	tmplen += 4;

	/* user name */
	for(i=0; i<userCnt; i++)
	{
		memcpy(&userId, data +tmplen, 4);
		tmplen += 4;
		memcpy(username, data +tmplen, USER_NAME_LEN);
		tmplen += USER_NAME_LEN;
		//printf("[%d]name: %s\n", i, username);
		mainwin_set_userList(1, 1, username);
		tmplen += USER_NAME_LEN;
	}

	return 0;
}

int client_0x07_getUserList(struct clientInfo *client, uint8_t *data, int len, uint8_t *ack_data, int size, int *ack_len)
{
	char name[USER_NAME_LEN] = {0};
	int userCnt = 0;
	int tmplen = 0;
	int ret;
	int i;

	/* return value */
	memcpy(&ret, data, 4);
	tmplen += 4;

	/* user count */
	memcpy(&userCnt, data +tmplen, 4);
	tmplen += 4;

	printf("getUserList: [%d]\n", userCnt);
	for(i=0; i<userCnt; i++)
	{
		memcpy(name, data +tmplen, USER_NAME_LEN);
		printf("[%d]name: %s\n", i, name);
		mainwin_set_userList(1, 1, name);
		tmplen += USER_NAME_LEN;
	}

	return 0;
}

int client_0x10_getOneFrame(struct clientInfo *client, uint8_t *data, int len, uint8_t *ack_data, int size, int *ack_len)
{
	int frame_len = 0;
	int tmplen = 0;
	int ret = 0;

	/* request part */
	// NULL

	/* ack part */
	/* return value */
	memcpy(ack_data +tmplen, &ret, 4);
	tmplen += 4;

	/* type */
	ack_data[tmplen] = 0;
	tmplen += 1;

	/* frame data */
	ret = capture_getframe(ack_data +tmplen +4, size-tmplen, &frame_len);
	if(ret == -1)
		return -1;

	/* frame len */
	memcpy(ack_data +tmplen, &frame_len, 4);
	tmplen += 4;

	tmplen += frame_len;

	if(ack_len != NULL)
		*ack_len = tmplen;

	return 0;
}

int client_0x11_faceDetect(struct clientInfo *client, uint8_t *data, int len, uint8_t *ack_data, int size, int *ack_len)
{
	int x, y, w, h;
	uint8_t count;
	int offset = 0;

	count = data[0];
	offset += 1;

	for(int i=0; i<count; i++)
	{
		x = *((int*)(data+offset));
		offset += 4;
		y = *((int*)(data+offset));
		offset += 4;
		w = *((int*)(data+offset));
		offset += 4;
		h = *((int*)(data+offset));
		offset += 4;
	}
	mainwin_set_rects(x, y, w, h);

	return 0;
}

int client_0x12_faceRecogn(struct clientInfo *client, uint8_t *data, int len, uint8_t *ack_data, int size, int *ack_len)
{
	int face_id = 0;
	uint8_t confidence = 0;
	char face_name[32] = {0};
	int status;
	int offset = 0;

	/* face id */
	memcpy(&face_id, data +offset, 4);
	offset += 4;

	/* confidence */
	confidence = data[offset];
	offset += 1;

	/* face name */
	memcpy(face_name, data +offset, 32);
	offset += 32;

	/* status */
	memcpy(&status, data +offset, 4);
	offset += 4;

	printf("[recogn]: ****** face id: %d, confid: %d, face name: %s\n", face_id, confidence, face_name);
	mainwin_set_recognInfo(face_id, confidence, face_name, status);
	main_mngr.work_state = WORK_STA_RECOGN;

	return 0;
}


int client_init(struct clientInfo *client, char *srv_ip, int srv_port)
{
	int flags = 0;
	int ret;

	memset(client, 0, sizeof(struct clientInfo));

	client->state = STATE_DISCONNECT;

	client->fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(client->fd < 0)
	{
		ret = -1;
		goto ERR_1;
	}

	flags = fcntl(client->fd, F_GETFL, 0);
	fcntl(client->fd, F_SETFL, flags | O_NONBLOCK);

	client->srv_addr.sin_family = AF_INET;
	inet_pton(AF_INET, srv_ip, &client->srv_addr.sin_addr);
	client->srv_addr.sin_port = htons(srv_port);

	ret = ringbuf_init(&client->recvRingBuf, RECV_BUFFER_SIZE);
	if(ret != 0)
	{
		ret = -2;
		goto ERR_2;
	}

	proto_init();

	return 0;

ERR_2:
	close(client->fd);

ERR_1:

	return ret;
}

void client_deinit(struct clientInfo *client)
{
	ringbuf_deinit(&client->recvRingBuf);
	close(client->fd);
}

int client_sendData(int sodkfd, uint8_t *data, int len)
{
	int total = 0;
	int ret;

	if(data == NULL)
		return -1;

	/* add sequence */
	data[PROTO_SEQ_OFFSET] = global_seq++;

	// lock
	do{
		ret = send(sodkfd, data +total, len -total, 0);
		if(ret < 0)
		{
			usleep(1000);
			continue;
		}
		total += ret;
	}while(total < len);
	// unlock

	return total;
}

int client_recvData(struct clientInfo *client)
{
	int len;

	if(client == NULL)
		return -1;

	memset(client->tmpBuf, 0, PROTO_PACK_MAX_LEN);
	len = recv(client->fd, client->tmpBuf, PROTO_PACK_MAX_LEN, 0);

	if(len > 0)
	{
		len = ringbuf_write(&client->recvRingBuf, client->tmpBuf, len);
	}

	return len;
}

int client_protoAnaly(struct clientInfo *client, uint8_t *pack, uint32_t pack_len)
{
	uint8_t *ack_buf = client->ack_buf;
	uint8_t *tmpBuf = client->tmpBuf;
	uint8_t seq = 0, cmd = 0;
	int data_len = 0;
	uint8_t *data = 0;
	int ack_len = 0;
	int tmpLen = 0;
	int ret;

	if(pack==NULL || pack_len<=0)
		return -1;

	ret = proto_analyPacket(pack, pack_len, &seq, &cmd, &data_len, &data);
	if(ret != 0)
		return -1;
	//printf("get proto cmd: 0x%02x\n", cmd);

	switch(cmd)
	{
		case 0x01:
			ret = client_0x01_login(client, data, data_len, ack_buf, PROTO_PACK_MAX_LEN, &ack_len);
			break;

		case 0x02:
			break;

		case 0x03:
			ret = client_0x03_heartbeat(client, data, data_len, ack_buf, PROTO_PACK_MAX_LEN, &ack_len);
			break;

		case 0x04:
			ret = client_0x04_switchWorkSta(client, data, data_len, ack_buf, PROTO_PACK_MAX_LEN, &ack_len);
			break;

		case 0x05:
			ret = client_0x05_addUser(client, data, data_len, ack_buf, PROTO_PACK_MAX_LEN, &ack_len);
			break;

		case 0x07:
			ret = client_0x07_getUserList(client, data, data_len, ack_buf, PROTO_PACK_MAX_LEN, &ack_len);
			break;

		case 0x10:
			ret = client_0x10_getOneFrame(client, data, data_len, ack_buf, PROTO_PACK_MAX_LEN, &ack_len);
			break;

		case 0x11:
			ret = client_0x11_faceDetect(client, data, data_len, ack_buf, PROTO_PACK_MAX_LEN, &ack_len);
			break;

		case 0x12:
			ret = client_0x12_faceRecogn(client, data, data_len, ack_buf, PROTO_PACK_MAX_LEN, &ack_len);
			break;

		default:
			printf("ERROR: protocol cmd[0x%02x] not exist!\n", cmd);
			break;
	}

	/* send ack data */
	if(ret==0 && ack_len>0)
	{
		proto_makeupPacket(seq, cmd, ack_len, ack_buf, tmpBuf, PROTO_PACK_MAX_LEN, &tmpLen);
		client_sendData(client->fd, tmpBuf, tmpLen);
	}

	return 0;
}

int client_protoHandle(struct clientInfo *client)
{
	int recv_ret;
	int det_ret;

	if(client == NULL)
		return -1;

	recv_ret = client_recvData(client);
	det_ret = proto_detectPack(&client->recvRingBuf, &client->detectInfo, client->packBuf, \
							sizeof(client->packBuf), &client->packLen);
	if(det_ret == 0)
	{
		//printf("detect protocol pack len: %d\n", client->packLen);
		client_protoAnaly(client, client->packBuf, client->packLen);
	}

	if(recv_ret<=0 && det_ret!=0)
	{
		usleep(200*1000);
	}

	return 0;
}


void *socket_client_thread(void *arg)
{
	struct clientInfo *client = &client_info;
	time_t heartbeat_time = 0;
	time_t login_time = 0;
	time_t tmpTime;
	int ret;

	ret = client_init(client, (char *)CONFIG_SERVER_IP(main_mngr.config_ini), CONFIG_SERVER_PORT(main_mngr.config_ini));
	if(ret != 0)
	{
		return NULL;
	}

	while(1)
	{
		switch (client->state)
		{
			case STATE_DISABLE:
				//printf("%s %d: state STATE_DISABLE ...\n", __FUNCTION__, __LINE__);
				break;

			case STATE_DISCONNECT:
				ret = connect(client->fd, (struct sockaddr *)&client->srv_addr, sizeof(client->srv_addr));
				if(ret == 0)
				{
					client->protoHandle = proto_register(client->fd, client_sendData, SEND_BUFFER_SIZE);
					client->state = STATE_CONNECTED;
					printf("********** socket connect successfully, handle: %d.\n", client->protoHandle);
				}
				break;

			case STATE_CONNECTED:
				tmpTime = time(NULL);
				if(abs(tmpTime - login_time) >= 3)
				{
				#if defined(MANAGER_CLIENT_ENABLE) && defined(USER_CLIENT_ENABLE)
					proto_0x01_login(client->protoHandle, (uint8_t *)ROOT_CLIENT_NAME, (uint8_t *)"pass_word");
				#elif MANAGER_CLIENT_ENABLE
					proto_0x01_login(client->protoHandle, (uint8_t *)MNGR_CLIENT_NAME, (uint8_t *)"pass_word");
				#else
					proto_0x01_login(client->protoHandle, (uint8_t *)USER_CLIENT_NAME, (uint8_t *)"pass_word");
				#endif
					login_time = tmpTime;
				}
				
				break;

			case STATE_LOGIN:
				tmpTime = time(NULL);
				if(abs(tmpTime - heartbeat_time) >= HEARTBEAT_INTERVAL_S)
				{
					proto_0x03_sendHeartBeat(client->protoHandle);
					heartbeat_time = tmpTime;
				}
				break;

			default:
				printf("%s %d: state ERROR !!!\n", __FUNCTION__, __LINE__);
				break;
		}

		if(client->state==STATE_CONNECTED || client->state==STATE_LOGIN)
		{
			client_protoHandle(client);
		}
		else
		{
			usleep(200*1000);
		}
		
	}

	client_deinit(client);

}


int start_socket_client_task(void)
{
	pthread_t tid;
	int ret;

	ret = pthread_create(&tid, NULL, socket_client_thread, NULL);
	if(ret != 0)
	{
		return -1;
	}

	return 0;
}





