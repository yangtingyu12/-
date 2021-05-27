#include <iostream>
#include <QApplication>
#include "mainwindow.h"
#include "socket_client.h"

/* C++ include C */
#ifdef __cplusplus
extern "C" {
#endif
#include "capture.h"
#ifdef __cplusplus
}
#endif


using namespace std;

struct main_mngr_info main_mngr;


int main(int argc, char* argv[])
{
    QApplication qtApp(argc, argv);
	
	cout << "hello foreground_app" << endl;

	memset(&main_mngr, 0, sizeof(struct main_mngr_info));
	/* load config file */
	main_mngr.config_ini = iniparser_load(PATH_CONFIG_INI);
	if(main_mngr.config_ini == NULL)
	{
		printf("ERROR: %s: load [%s] failed!\n", __FUNCTION__, PATH_CONFIG_INI);
		//return -1;	// will use default value
	}
	main_mngr.work_state = WORK_STA_DISCONNECT;
	main_mngr.user_handle = -1;
	main_mngr.mngr_handle = -1;
	
	start_mainwindow_task();

#ifdef USER_CLIENT_ENABLE
	start_capture_task();
#endif
	start_socket_client_task();


	return qtApp.exec();		// start qt application, message loop ...
}
