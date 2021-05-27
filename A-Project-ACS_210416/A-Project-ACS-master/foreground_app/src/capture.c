#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/videodev2.h>
#include <linux/input.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <pthread.h>
#include "capture.h"
#include "public.h"
#include "config.h"


struct v4l2cap_info capture_info = {0};
extern struct main_mngr_info main_mngr;


int capture_init(struct v4l2cap_info *capture)
{
	struct v4l2_fmtdesc fmtdesc;
	struct v4l2_format format;
	struct v4l2_requestbuffers reqbuf_param;
	struct v4l2_buffer buffer[QUE_BUF_MAX_NUM];
	int v4l2_fmt[2] = {V4L2_PIX_FMT_MJPEG, V4L2_PIX_FMT_JPEG};
	int i, ret;

	memset(capture, 0, sizeof(struct v4l2cap_info));

	pthread_mutex_init(&capture->frameMut, NULL);

	capture->fd = open(CONFIG_CAPTURE_DEV(main_mngr.config_ini), O_RDWR);
	if(capture->fd < 0)
	{
		printf("ERROR: open video dev [%s] failed !\n", CONFIG_CAPTURE_DEV(main_mngr.config_ini));
		ret = -1;
		goto ERR_1;
	}
	printf("open video dev [%s] successfully .\n", CONFIG_CAPTURE_DEV(main_mngr.config_ini));

	/* get supported format */
	memset(&fmtdesc, 0, sizeof(struct v4l2_fmtdesc));
	fmtdesc.index = 0;
	fmtdesc.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	do{
		ret = ioctl(capture->fd, VIDIOC_ENUM_FMT, &fmtdesc);
		if(ret == 0)
		{
			printf("[ret:%d]video description: %s\n", ret, fmtdesc.description);
			fmtdesc.index ++;
		}
	}while(ret == 0);

	for(i=0; i<sizeof(v4l2_fmt)/sizeof(int); i++)
	{
		/* configure video format */
		memset(&format, 0, sizeof(struct v4l2_format));
		format.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		format.fmt.pix.width = CONFIG_CAPTURE_WIDTH(main_mngr.config_ini);
		format.fmt.pix.height = CONFIG_CAPTURE_HEIGH(main_mngr.config_ini);
		format.fmt.pix.pixelformat = v4l2_fmt[i];
		format.fmt.pix.field = V4L2_FIELD_INTERLACED;
		ret = ioctl(capture->fd, VIDIOC_S_FMT, &format);
		if(ret < 0)
		{
			ret = -2;
			goto ERR_2;
		}
		printf("[try %d] set v4l2 format = %d\n", i, v4l2_fmt[i]);

		/* get video format */
		capture->format.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		ret = ioctl(capture->fd, VIDIOC_G_FMT, &capture->format);
		if(ret < 0)
		{
			printf("ERROR: get video format failed[ret:%d] !\n", ret);
			ret = -3;
			goto ERR_3;
		}
		
		if(capture->format.fmt.pix.pixelformat == v4l2_fmt[i])
		{
			printf("get video width * height = %d * %d\n", capture->format.fmt.pix.width, capture->format.fmt.pix.height);
			printf("video pixelformat: ");
			switch(capture->format.fmt.pix.pixelformat)
			{
				case V4L2_PIX_FMT_JPEG: printf("V4L2_PIX_FMT_JPEG \n");
					break;
				case V4L2_PIX_FMT_YUYV: printf("V4L2_PIX_FMT_YUYV \n");
					break;
				case V4L2_PIX_FMT_MJPEG: printf("V4L2_PIX_FMT_MJPEG \n");
					break;
				
				default:
					printf("ERROR: value is illegal !\n");
			}
			break;
		}
	}
	if(i >= sizeof(v4l2_fmt)/sizeof(int))
	{
		printf("ERROR: Not support capture foramt !!!\n");
		ret = -4;
		goto ERR_4;
	}

	capture->frameBuf = (unsigned char *)calloc(1, FRAME_BUF_SIZE);
	if(capture->frameBuf == NULL)
	{
		ret = -5;
		goto ERR_5;
	}

	memset(&reqbuf_param, 0, sizeof(struct v4l2_requestbuffers));
	reqbuf_param.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	reqbuf_param.memory = V4L2_MEMORY_MMAP;
	reqbuf_param.count = QUE_BUF_MAX_NUM;
	ret = ioctl(capture->fd, VIDIOC_REQBUFS, &reqbuf_param);
	if(ret < 0)
	{
		ret = -6;
		goto ERR_6;
	}

	/* set video queue buffer */
	for(i=0; i<QUE_BUF_MAX_NUM; i++)
	{
		memset(&buffer[i], 0, sizeof(struct v4l2_buffer));
		buffer[i].type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buffer[i].memory = V4L2_MEMORY_MMAP;
		buffer[i].index = i;
		ret = ioctl(capture->fd, VIDIOC_QUERYBUF, &buffer[i]);
		if(ret < 0)
		{
			ret = -7;
			goto ERR_7;
		}

		capture->buffer[i].len = buffer[i].length;
		capture->buffer[i].addr = (unsigned char *)mmap(NULL, buffer[i].length, PROT_READ | PROT_WRITE, \
									MAP_SHARED, capture->fd, buffer[i].m.offset);
		printf("buffer[%d]: addr = %p, len = %d\n", i, capture->buffer[i].addr, capture->buffer[i].len);

		ret = ioctl(capture->fd, VIDIOC_QBUF, &buffer[i]);
		if(ret < 0)
		{
			ret = -8;
			goto ERR_8;
		}
	}

	return 0;
	
	ERR_8:
	ERR_7:
		for(; i>=0; i--)
		{
			if(capture->buffer[i].addr != NULL)
				munmap(capture->buffer[i].addr, capture->buffer[i].len);
		}
	ERR_6:
		free(capture->frameBuf);
	ERR_5:
	ERR_4:
	ERR_3:
	ERR_2:
		close(capture->fd);

	ERR_1:

	return ret;
}

void capture_deinit(struct v4l2cap_info *capture)
{
	int i;

	for(i=0; i<QUE_BUF_MAX_NUM; i++)
	{
		munmap(capture->buffer[i].addr, capture->buffer[i].len);
	}
	
	free(capture->frameBuf);

	close(capture->fd);
}

int v4l2cap_start(struct v4l2cap_info *capture)
{
	enum v4l2_buf_type type;
	int ret;

	type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	ret = ioctl(capture->fd, VIDIOC_STREAMON, &type);
	if(ret < 0)
		return -1;

	return 0;
}

void v4l2cap_stop(struct v4l2cap_info *capture)
{
	enum v4l2_buf_type type;

	type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	ioctl(capture->fd, VIDIOC_STREAMOFF, &type);
}

int v4l2cap_flushframe(struct v4l2cap_info *capture)
{
	struct v4l2_buffer v4l2buf;
	static unsigned int index = 0;
	int ret;

	memset(&v4l2buf, 0, sizeof(struct v4l2_buffer));
	v4l2buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	v4l2buf.memory = V4L2_MEMORY_MMAP;
	v4l2buf.index = index % QUE_BUF_MAX_NUM;
	
	ret = ioctl(capture->fd, VIDIOC_DQBUF, &v4l2buf);
	if(ret < 0)
	{
		printf("ERROR: get VIDIOC_DQBUF failed, ret: %d\n", ret);
		return -1;
	}

	pthread_mutex_lock(&capture->frameMut);
	memset(capture->frameBuf, 0, FRAME_BUF_SIZE);
	memcpy(capture->frameBuf, capture->buffer[v4l2buf.index].addr, capture->buffer[v4l2buf.index].len);
	pthread_mutex_unlock(&capture->frameMut);
	capture->frameLen = capture->buffer[v4l2buf.index].len;

	ret = ioctl(capture->fd, VIDIOC_QBUF, &v4l2buf);
	if(ret < 0)
	{
		printf("ERROR: get VIDIOC_QBUF failed, ret: %d\n", ret);
		return -1;
	}

	index ++;

	return 0;
}

int capture_getframe(unsigned char *data, int size, int *len)
{
	struct v4l2cap_info *capture = &capture_info;
	int tmpLen;

	if(!capture->run)
		return -1;

	if(data==NULL || size<=0)
		return -1;

	tmpLen = (capture->frameLen <size ? capture->frameLen:size);
	if(tmpLen < capture->frameLen)
	{
		printf("Warning: %s: bufout size[%d] < frame size[%d] !!!\n", __FUNCTION__, size, capture->frameLen);
	}
	if(tmpLen <= 0)
	{
		//printf("Warning: %s: no data !!!\n", __FUNCTION__);
		return -1;
	}

	pthread_mutex_lock(&capture->frameMut);
	memcpy(data, capture->frameBuf, tmpLen);
	pthread_mutex_unlock(&capture->frameMut);
	*len = tmpLen;

	return 0;
}


void *capture_thread(void *arg)
{
	struct v4l2cap_info *capture = &capture_info;
	int ret;

	ret = capture_init(capture);
	if(ret != 0)
	{
		printf("ERROR: capture init failed, ret: %d\n", ret);
		return NULL;
	}
	printf("capture init successfully .\n");

	v4l2cap_start(capture);
	capture->run = 1;

	while(capture->run)
	{
	
		ret = v4l2cap_flushframe(capture);
		if(ret == 0)
		{
		}
		else
		{
			printf("ERROR: get capture frame failed, ret: %d\n", ret);
		}
	}
	capture->run = 0;

	v4l2cap_stop(capture);

	capture_deinit(capture);
	printf("%s: exit --\n", __FUNCTION__);
	return NULL;
}

int start_capture_task(void)
{
	pthread_t tid;
	int ret;

	if(capture_info.run)
		return 0;

	ret = pthread_create(&tid, NULL, capture_thread, NULL);
	if(ret != 0)
	{
		return -1;
	}

	return 0;
}

int capture_task_stop(void)
{
	capture_info.run = 0;
	return 0;
}
