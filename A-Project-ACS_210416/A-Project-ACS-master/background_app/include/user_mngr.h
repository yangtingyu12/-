#ifndef _USER_MNGR_H_
#define _USER_MNGR_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

/* C++ include C */
#ifdef __cplusplus
extern "C" {
#endif
#include "public.h"
#include "user_db.h"
#ifdef __cplusplus
}
#endif

using namespace cv;
using namespace std;

#define FACES_DATABASE_PATH		"faces"
#define FACES_DB_CSV_FILE			(FACES_DATABASE_PATH"/""faces.csv")


struct userMngr_Stru
{
	sqlite3 *userdb;
	char 	add_userdir[DIR_PATH_LEN];	// use when add user
	int 	newid;		// new user id
	char 	newname[USER_NAME_LEN];	// the newest user
	int 	add_index;		// add user num
};


int user_delete(int userCnt, char *username);
int user_create_dir(char *base_dir, int id, char *usr_name, char *usr_dir);
int user_get_faceimg_label(vector<Mat>& images, vector<int>& labels);
int user_mngr_init(void);


#endif	// _USER_MNGR_H_