#include "adriot_main.h"
#include <adri_tools.h>


relayManagement adriot_relayManagement;
dht22Management adriot_dht22Management;


adriot_main::adriot_main(const char * hName){
	

	_relayManagment = &adriot_relayManagement;
	_dht22Managment = &adriot_dht22Management;


	_wifi 			= new wifiClass(hName);
	_webServer 		= new ALS_espwebserver();


	#ifdef DEBUG
		fsprintf("\n[ADRIOT WIFI SETUP]\n");	
	#endif

	wifiConnect_instance()->connect_set(AWC_SETUP);
	wifiConnect_instance()->connectSSID_set(AWCS_NORMAL);		
	wifiConnect_instance()->savToSpiff();	

	if (!_wifi->_setupFromSpiff()) { 
		_wifi->_setupAp(AWC_SETUP, AWCS_AP);
		_wifi->_connect(AWC_SETUP);
	} else {
		_wifi->_connect(AWC_SETUP);
	}
	wifi_connect_statu();


	_webServer->serverFS(true); 	
	_webServer->serverInitialize();
	_webServer->serverBegin();
	_webServer->socketBegin();


}


void adriot_main::loop(){

	_wifi->_loop();

	if (_wifi->_connectMod == 1) {
		_wifi->_connectMod = 0;
		_wifi->_isConnect = true;
	}
	if (_wifi->_isConnect) {

		_wifi->ntpTime_loop();

		if(!_wifi->_otaEnabled)	_wifi->MDSN_loop();
		else					arduinoOTA_loop();	

		_webServer->serverLoop();	
		_webServer->socketLoop();	
	}		

}