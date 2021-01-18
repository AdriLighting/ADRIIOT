

#include <ADRIOT.h>
#include <adri_tools.h>


#define DEBUG


adriot_main 		* adriotMain;
adri_webserver		clientServer(80);
adri_socket			socketServer(81);
adri_timer 			* timeDisplay 			= nullptr;
wifiClass 			* _wifi;
ALS_espwebserver	* _webServer;


solmoistureClass 	* sensorSolMoisture 	= nullptr;
boolean 			sensorSolMoisture_cap 	= false;

int					relayPump 				= -1;
boolean 			relayPump_statu 		= false;

dht22Class 			sensor_temperature(D2);



void setup()
{
	Serial.begin(115200);
  	for(unsigned long const serialBeginTime = millis(); !Serial && (millis() - serialBeginTime > 5000); ) { }

	LittleFS.begin();

  	#ifdef DEBUG
  		fsprintf("\n[ADRIOT BEGIN]\n");	
  	#endif
	adriotMain = new adriot_main((char *)"ADRIOT");

	_wifi 		= wifiClassPtr_get();
	_webServer 	= ALS_espwebserverPtr_get();

	#ifdef DEBUG
		fsprintf("\n[ADRIOT WIFI SETUP]\n");	
		
	#endif
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


/*
	#ifdef DEBUG
		fsprintf("\n[ADRIOT SOL MOISTURE BEGIN]\n");	
	#endif
	sensorSolMoisture = new solmoistureClass(false, A0);
*/
/*	
	#ifdef DEBUG
		fsprintf("\n[ADRIOT RELAY MOISTURE PUMP BEGIN]\n");	
	#endif
	adriotMain->_relayManagment->create(D2, relayPump);
*/
/*	
	timeDisplay = new adri_timer(1000,"",true);
*/

	
}


void loop()
{


	_wifi->_loop();
	if (_wifi->_connectMod == 1) {
		_wifi->_connectMod = 0;
		_wifi->_isConnect = true;
		fsprintf("\n[_isConnect]\n");		
	}
	if (_wifi->_isConnect) {

		_wifi->ntpTime_loop();

		if(!_wifi->_otaEnabled)	_wifi->MDSN_loop();
		else					arduinoOTA_loop();	

		_webServer->serverLoop();	
		_webServer->socketLoop();	

		// if(timeDisplay->loop()){
		// 	String ret = _wifi->ntpTime_toString(adri_timeNtp_instance()->timeget());	
		// 	Serial.write(27);	
		// 	fsprintf("\n[timer]%s\n", ret.c_str());	
		// }			
	}	
	

	if ((relayPump!=-1) && (sensorSolMoisture!=nullptr)) {
		relayPump_statu 		= adriotMain->_relayManagment->relay(relayPump)->getStatus();	
		sensorSolMoisture->loop(sensorSolMoisture_cap);
		if (sensorSolMoisture_cap) {
			if (!relayPump_statu) 	adriotMain->_relayManagment->relay(relayPump)->open();
		} else {
			if (relayPump_statu) 	adriotMain->_relayManagment->relay(relayPump)->close();
		}		
	}


}
