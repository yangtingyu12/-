#ifndef _OPENCV_FACE_PROCESS_H_
#define _OPENCV_FACE_PROCESS_H_

#include <semaphore.h>
#include "opencv2/objdetect.hpp"
#include "type.h"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/face.hpp"

using namespace std;
using namespace cv;
using namespace cv::face;

#define FRONTAL_TACE_HAAR_XML "resource/haarcascade_frontalface_alt.xml"

class face_detect
{
public:
	face_detect(void);
	int face_detect_init(void);
	void face_detect_deinit(void);

public:
	uint8_t *frame_buf;
	uint32_t frame_size;
	sem_t detect_sem;
	CascadeClassifier face_cascade;
};

class face_recogn
{
private:
	
public:
	face_recogn(void);
	int face_recogn_init(void);
	void face_recogn_deinit(void);
	
public:
	Ptr<LBPHFaceRecognizer> mod_LBPH;
	Mat face_mat;
	sem_t recogn_sem;
	int recogn_avalid;	// 0-unavaliable 1-avalidiable
};

int face_database_train(void);
int opencv_put_frame_detect(uint8_t *buf, int len);
int opencv_get_frame_detect(uint8_t *buf, int size);
int start_face_process_task(void);


#endif	// _OPENCV_FACE_PROCESS_H_
