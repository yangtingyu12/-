#ifndef _CONFIG_H_
#define _CONFIG_H_

/******************** get configure value ********************/

// [WINDOW]
#define CONFIG_WINDOW_TITLE(ini)        iniparser_getstring(ini, "WINDOW:windowTitle", DEFAULT_WINDOW_TITLE)
#define CONFIG_WINDOW_WIDTH(ini)        iniparser_getint(ini, "WINDOW:windowWidth", DEFAULT_WINDOW_WIDTH)
#define CONFIG_WINDOW_HEIGHT(ini)       iniparser_getint(ini, "WINDOW:windowHeight", DEFAULT_WINDOW_HEIGHT)
#define CONFIG_WINDOW_FONT_SIZE(ini)   iniparser_getint(ini, "WINDOW:windowFontSize", DEFAULT_WINDOW_FONT_SIZE)

// [CAPTURE]
#define CONFIG_CAPTURE_DEV(ini)     iniparser_getstring(ini, "CAPTURE:captureDev", DEFAULT_CAPTURE_DEV)
#define CONFIG_CAPTURE_WIDTH(ini)    iniparser_getint(ini, "CAPTURE:capuretWidth", DEFAULT_CAPTURE_WIDTH)
#define CONFIG_CAPTURE_HEIGH(ini)    iniparser_getint(ini, "CAPTURE:captureHeight", DEFAULT_CAPTURE_HEIGH)

// [SERVER]
#define CONFIG_SERVER_IP(ini)       iniparser_getstring(ini, "SERVER:serverIp", DEFAULT_SERVER_IP)
#define CONFIG_SERVER_PORT(ini)     iniparser_getint(ini, "SERVER:serverPort", DEFAULT_SERVER_PORT)

// [FACE]
#define CONFIG_FACE_RECOTHRES00(ini)    iniparser_getdouble(ini, "FACE:recognThreshold00", DEFAULT_FACE_RECOGN_THRES_00)
#define CONFIG_FACE_RECOTHRES80(ini)    iniparser_getdouble(ini, "FACE:recognThreshold80", DEFAULT_FACE_RECOGN_THRES_80)
#define CONFIG_FACE_RECOTHRES100(ini)   iniparser_getdouble(ini, "FACE:recognThreshold100", DEFAULT_FACE_RECOGN_THRES_100)
#define CONFIG_FACE_IMGCNTUSER(ini)     iniparser_getint(ini, "FACE:faceImgPerUser", DEFAULT_FACE_IMG_CNT_USER)
#define CONFIG_FACE_RECOINTERVAL(ini)   iniparser_getint(ini, "FACE:recognInterval", DEFAULT_RECOGN_INTERVAL)
#define CONFIG_FACE_IMGSIZEMIN(ini)     iniparser_getint(ini, "FACE:faceImgSizeMin", DEFAULT_FACE_IMG_SIZE_MIN)


/******************** default configure value ********************/

// [WINDOW]
#define DEFAULT_WINDOW_TITLE		"人脸识别系统"
#define DEFAULT_WINDOW_WIDTH		800
#define DEFAULT_WINDOW_HEIGHT		480
#define DEFAULT_WINDOW_FONT_SIZE	24


// [CAPTURE]
#define DEFAULT_CAPTURE_DEV 		"/dev/video0"
#define DEFAULT_CAPTURE_WIDTH		640
#define DEFAULT_CAPTURE_HEIGH		480


// [SERVER]
#define DEFAULT_SERVER_IP			"127.0.0.1"
#define DEFAULT_SERVER_PORT			9100


// [FACE]
#define DEFAULT_FACE_RECOGN_THRES_00		125.0	// confidence = 0%
#define DEFAULT_FACE_RECOGN_THRES_80		80.0	// confidence = 80%
#define DEFAULT_FACE_RECOGN_THRES_100		50.0	// confidence = 100%
#define DEFAULT_FACE_IMG_SIZE_MIN			60
#define DEFAULT_RECOGN_INTERVAL		        (3*1000)	// delay time after rocognize success
#define DEFAULT_FACE_IMG_CNT_USER		    10		// face image count per user

#define FACE_RECOGN_THRES 		DEFAULT_FACE_RECOGN_THRES_80	// face recognize threshold

#endif	// _CONFIG_H_
