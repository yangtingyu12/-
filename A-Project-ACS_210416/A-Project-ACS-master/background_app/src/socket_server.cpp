#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/socket.h>
#include "opencv_face_process.h"
#include "socket_server.h"
#include "user_mngr.h"
#include "config.h"


/* C++ include C */
#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif


static struct serverInfo server_info;

extern struct main_mngr_info main_mngr;
extern struct userMngr_Stru	user_mngr_unit;

int server_0x01_login(struct clientInfo *client, uint8_t *data, int len, uint8_t *ack_data, int size, int *ack_len)
{
	uint8_t usr_name[32] = {0};
	uint8_t passwd[32] = {0};
	int tmplen = 0;
	int ret = 0;

	/* user name */
	memcpy(usr_name, data +tmplen, 32);
	tmplen += 32;

	/* password */
	memcpy(passwd, data +tmplen, 32);
	tmplen += 32;

	if(strcmp(ROOT_CLIENT_NAME, (char *)usr_name) == 0)
	{
		client->identity = IDENTITY_MANAGER;
		main_mngr.mngr_handle = client->protoHandle;
		main_mngr.user_handle = client->protoHandle;
		printf("##### ROOT Login [handle: %d]: %s, passwd: %s\n", client->protoHandle, usr_name, passwd);
	}
	else if(strcmp(MNGR_CLIENT_NAME, (char *)usr_name) == 0)
	{
		client->identity = IDENTITY_MANAGER;
		main_mngr.mngr_handle = client->protoHandle;
		printf("##### MANAGER Login [handle: %d]: %s, passwd: %s\n", client->protoHandle, usr_name, passwd);
	}
	else
	{
		client->identity = IDENTITY_USER;
		main_mngr.user_handle = client->protoHandle;
		printf("##### USER Login [handle: %d]:: %s, passwd: %s\n", client->protoHandle, usr_name, passwd);
	}

	/* ack part */
	tmplen = 0;
	memcpy(ack_data, &ret, 4);
	tmplen += 4;
	
	*ack_len = tmplen;

	return 0;
}

int server_0x03_heartbeat(struct clientInfo *client, uint8_t *data, int len, uint8_t *ack_data, int size, int *ack_len)
{
	uint32_t tmpTime;
	int tmplen = 0;
	int ret;

	/* request part */
	memcpy(&tmpTime, data, 4);
	//printf("%s: time: %ld\n", __FUNCTION__, tmpTime);

	/* ack part */
	ret = 0;
	memcpy(ack_data +tmplen, &ret, 4);
	tmplen += 4;
	
	tmpTime = (uint32_t)time(NULL);
	memcpy(ack_data +tmplen, &tmpTime, 4);
	tmplen += 4;

	*ack_len = tmplen;

	return 0;
}

int server_0x04_switchWorkSta(struct clientInfo *client, uint8_t *data, int len, uint8_t *ack_data, int size, int *ack_len)
{
	int state = 0;
	int tmplen = 0;

	/* work state */
	memcpy(&state, data, 4);
	tmplen += 4;

	/* if add user */
	if(state == WORK_STA_ADDUSER)
	{
		memcpy(&user_mngr_unit.newid, data +tmplen, 4);
		tmplen += 4;

		memcpy(user_mngr_unit.newname, data +tmplen, 32);
		tmplen += 4;
	}

	/* create user dir */
	memset(user_mngr_unit.add_userdir, 0, sizeof(user_mngr_unit.add_userdir));
	user_create_dir((char *)FACES_DATABASE_PATH, user_mngr_unit.newid, user_mngr_unit.newname, user_mngr_unit.add_userdir);
	user_mngr_unit.add_index = 0;

	main_mngr.work_state = (workstate_e)state;
	
	printf("%s: get work state: %d, id: %d, name: %s\n", __FUNCTION__, state, user_mngr_unit.newid, user_mngr_unit.newname);

	return 0;
}

int client_0x06_deleteUser(struct clientInfo *client, uint8_t *data, int len, uint8_t *ack_data, int size, int *ack_len)
{
	char username[USER_NAME_LEN] = {0};
	int userCnt = 0;
	int tmplen = 0;
	int i;

	/* user count */
	memcpy(&userCnt, data, 4);
	tmplen += 4;

	/* user name */
	for(i=0; i<userCnt; i++)
	{
		memcpy(username, data +tmplen, USER_NAME_LEN);
		//printf("[%d]name: %s\n", i, username);
		user_delete(1, username);
		userdb_delete_byName(user_mngr_unit.userdb, username);
		tmplen += USER_NAME_LEN;
	}

	/* retrain face data base */
	face_database_train();

	return 0;
}

int server_0x07_getUserList(struct clientInfo *client, uint8_t *data, int len, uint8_t *ack_data, int size, int *ack_len)
{
	struct userdb_user userInfo;
	int userCnt = 0;
	int cursor = 0;
	int tmplen = 0;
	int ret = 0;
	int i;

	/* request part */
	// NULL

	/* ack part */
	/* return value */
	ret = 0;
	memcpy(ack_data, &ret, 4);
	tmplen += 4;
	
	/* user count */
	userCnt = userdb_get_total(user_mngr_unit.userdb);
	memcpy(ack_data +tmplen, &userCnt, 4);
	tmplen += 4;

	/* user name */
	for(i=0; i<userCnt +1; i++)
	{
		ret = userdb_traverse_user(user_mngr_unit.userdb, &cursor, &userInfo);
		if(ret == -1)
			break;
		memcpy(ack_data +tmplen, userInfo.name, 32);
		tmplen += 32;
	}

	if(ack_len != NULL)
		*ack_len = tmplen;

	return 0;
}

int server_0x10_getOneFrame(struct clientInfo *client, uint8_t *data, int len, uint8_t *ack_data, int size, int *ack_len)
{
	uint8_t type = 0;
	int frame_len = 0;
	uint8_t *frame = NULL;
	int32_t tmpLen = 0;
	int ret;

	memcpy(&ret, data, 4);
	tmpLen += 4;

	type = data[tmpLen];
	tmpLen += 1;
	(void)type;

	memcpy(&frame_len, data+tmpLen, 4);
	tmpLen += 4;
	
	frame = data + tmpLen;
	tmpLen += frame_len;

	//printf("*** recv one frame data: type: %d, data_len: %d\n", type, frame_len);

	/* put frame to detect */
	opencv_put_frame_detect(frame, frame_len);

	return 0;
}



int server_init(struct serverInfo *server, int port)
{
	int ret;

	memset(server, 0, sizeof(struct serverInfo));

	server->fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(server->fd < 0)
	{
		ret = -1;
		goto ERR_0;
	}

	server->srv_addr.sin_family = AF_INET;
	server->srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server->srv_addr.sin_port = htons(port);

	ret = bind(server->fd, (struct sockaddr *)&server->srv_addr, sizeof(server->srv_addr));
	if(ret != 0)
	{
		ret = -2;
		goto ERR_1;
	}

	ret = listen(server->fd, MAX_LISTEN_NUM);
	if(ret != 0)
	{
		ret = -3;
		goto ERR_2;
	}

	proto_init();

	return 0;

ERR_2:
	
ERR_1:
	close(server->fd);

ERR_0:
	
	return ret;
}

void server_deinit(void)
{
	
}

int server_sendData(int sodkfd, uint8_t *data, int len)
{
	int total = 0;
	int ret;

	if(data == NULL)
		return -1;
	
	do{
		ret = send(sodkfd, data +total, len -total, 0);
		if(ret < 0)
		{
			usleep(1000);
			continue;
		}
		total += ret;
	}while(total < len);

	return total;
}

int server_recvData(struct clientInfo *client)
{
	uint8_t *tmpBuf = client->tmpBuf;
	int len;

	if(client == NULL)
		return -1;

	memset(tmpBuf, 0, PROTO_PACK_MAX_LEN);
	len = recv(client->fd, tmpBuf, PROTO_PACK_MAX_LEN, 0);

	if(len > 0)
	{
		len = ringbuf_write(&client->recvRingBuf, tmpBuf, len);
	}

	return len;
}

int server_protoAnaly(struct clientInfo *client, uint8_t *pack, uint32_t pack_len)
{
	uint8_t *ack_buf = client->ack_buf;
	uint8_t *tmpBuf = client->tmpBuf;
	uint8_t seq = 0, cmd = 0;
	int data_len = 0;
	uint8_t *data = NULL;
	int ack_len = 0;
	int tmpLen = 0;
	int ret;

	if(pack==NULL || pack_len<=0)
		return -1;

	ret = proto_analyPacket(pack, pack_len, &seq, &cmd, &data_len, &data);
	if(ret != 0)
		return -1;
	//printf("%s: cmd: 0x%02x, seq: %d, pack_len: %d, data_len: %d\n", __FUNCTION__, cmd, seq, pack_len, data_len);

	switch(cmd)
	{
		case 0x01:
			ret = server_0x01_login(client, data, data_len, ack_buf, PROTO_PACK_MAX_LEN, &ack_len);
			break;

		case 0x02:
			break;

		case 0x03:
			ret = server_0x03_heartbeat(client, data, data_len, ack_buf, PROTO_PACK_MAX_LEN, &ack_len);
			break;

		case 0x04:
			ret = server_0x04_switchWorkSta(client, data, data_len, ack_buf, PROTO_PACK_MAX_LEN, &ack_len);
			break;

		case 0x06:
			ret = client_0x06_deleteUser(client, data, data_len, ack_buf, PROTO_PACK_MAX_LEN, &ack_len);
			break;

		case 0x07:
			ret = server_0x07_getUserList(client, data, data_len, ack_buf, PROTO_PACK_MAX_LEN, &ack_len);
			break;

		case 0x10:
			ret = server_0x10_getOneFrame(client, data, data_len, ack_buf, PROTO_PACK_MAX_LEN, &ack_len);
			break;

		default:
			printf("ERROR: protocol cmd[0x%02x] not exist!\n", cmd);
			break;
	}

	/* send ack data */
	if(ret==0 && ack_len>0)
	{
		proto_makeupPacket(seq, cmd, ack_len, ack_buf, tmpBuf, PROTO_PACK_MAX_LEN, &tmpLen);
		server_sendData(client->fd, tmpBuf, tmpLen);
	}

	return 0;
}

int server_protoHandle(struct clientInfo *client)
{
	int recv_ret;
	int det_ret;

	if(client == NULL)
		return -1;

	recv_ret = server_recvData(client);
	det_ret = proto_detectPack(&client->recvRingBuf, &client->detectInfo, client->packBuf, \
							sizeof(client->packBuf), &client->packLen);
	if(det_ret == 0)
	{
		server_protoAnaly(client, client->packBuf, client->packLen);
	}

	if(recv_ret<=0 && det_ret!=0)
	{
		usleep(200*1000);
	}

	return 0;
}

void *socket_handle_thread(void *arg)
{
	struct clientInfo *client = (struct clientInfo *)arg;
	int flags = 0;
	int ret;

	printf("%s %d: enter ++\n", __FUNCTION__, __LINE__);

	flags = fcntl(client->fd, F_GETFL, 0);
	fcntl(client->fd, F_SETFL, flags | O_NONBLOCK);

	ret = ringbuf_init(&client->recvRingBuf, RECV_BUFFER_SIZE);
	if(ret < 0)
		return NULL;

	client->protoHandle = proto_register(client->fd, server_sendData, SEND_BUFFER_SIZE);
	client->identity = -1;

	while(1)
	{
		server_protoHandle(client);
	}

	ringbuf_deinit(&client->recvRingBuf);
}

void *socket_listen_thread(void *arg)
{
	struct serverInfo *server = &server_info;
	struct sockaddr_in cli_addr;
	pthread_t tid;
	int tmpSock, client_index;
	int tmpLen;
	int ret;
	int i;

	ret = server_init(server, CONFIG_SERVER_PORT(main_mngr.config_ini));
	if(ret != 0)
	{
		return NULL;
	}

	while(1)
	{
	
		// ps: only support 1 client now
		if(server->client_cnt >= MAX_CLIENT_NUM)
		{
			sleep(3);
			continue;
		}
		
		memset(&cli_addr, 0, sizeof(struct sockaddr_in));
		tmpSock = accept(server->fd, (struct sockaddr *)&cli_addr, (socklen_t *)&tmpLen);
		if(tmpSock < 0)
			continue;
		printf("%s %d: *************** accept socket success, sock fd: %d ...\n", __FUNCTION__, __LINE__, tmpSock);

		for(i=0; i<MAX_CLIENT_NUM; i++)
		{
			if(server->client_used[i] == 0)		// can use this
			{
				client_index = i;
				break;
			}
		}

		server->client[client_index].fd = tmpSock;
		memcpy(&server->client[client_index].addr, &cli_addr, sizeof(struct sockaddr_in));
		server->client_used[client_index] = 1;
		server->client_cnt ++;
		
		ret = pthread_create(&tid, NULL, socket_handle_thread, &server->client[client_index]);
		if(ret != 0)
		{
			printf("ERROR: %s %d: pthread_create failed !!!\n", __FUNCTION__, __LINE__);
		}

	}

	server_deinit();

}


int start_socket_server_task(void)
{
	pthread_t tid;
	int ret;

	ret = pthread_create(&tid, NULL, socket_listen_thread, NULL);
	if(ret != 0)
	{
		return -1;
	}

	return 0;
}





