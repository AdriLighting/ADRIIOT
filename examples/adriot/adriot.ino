
#include <ADRIOT.h>
#include <adri_tools.h>
#include <adri_espwebserver.h>

#define DEBUG

adriot_main * adriotMain;

solmoistureClass * sensorSolMoisture;

int		relayPump 				= -1;
boolean relayPump_statu 		= false;
boolean sensorSolMoisture_cap 	= false;

dht22Class sensor_temperature(D2);

adri_webserver		clientServer(80); // instance adri_webserver 	- ESP8266WebServer _server

adri_timer * timeDisplay;

void setup()
{
	Serial.begin(115200);
  	for(unsigned long const serialBeginTime = millis(); !Serial && (millis() - serialBeginTime > 5000); ) { }

	LittleFS.begin();

  	#ifdef DEBUG
  		fsprintf("\n[ADRIOT BEGIN]\n");	
  	#endif
	adriotMain = new adriot_main((char *)"ADRIOT");



	if (!wifiClassPtr_get()->_setupFromSpiff()) { 
		// fsprintf("\n[_setupFromSpiff AWCS_AP]\n");	
		wifiClassPtr_get()->_setupAp(AWC_SETUP, AWCS_AP);
		wifiClassPtr_get()->_connect(AWC_SETUP);
	} else {
		// fsprintf("\n[_setupFromSpiff AWC_SETUP]\n");	
		wifiClassPtr_get()->_connect(AWC_SETUP);
	}
	wifi_connect_statu();

	clientServer.filesystem_ok(true); 		// ENABLED FILE SYSTEM BROWSER
	clientServer.filesystem_set(&LittleFS);

	clientServer.initialize(80);
	clientServer.begin();

	#ifdef DEBUG
		fsprintf("\n[ADRIOT SOL MOISTURE BEGIN]\n");	
	#endif
	sensorSolMoisture = new solmoistureClass(false, A0);

	#ifdef DEBUG
		fsprintf("\n[ADRIOT RELAY MOISTURE PUMP BEGIN]\n");	
	#endif
	adriotMain->_relayManagment->create(D2, relayPump);

	timeDisplay = new adri_timer(1000,"",true);
}


void loop()
{
	wifiClassPtr_get()->_loop();
	if (wifiClassPtr_get()->_connectMod == 1) {
		wifiClassPtr_get()->_connectMod = 0;
		wifiClassPtr_get()->_isConnect = true;		
	}
	if (wifiClassPtr_get()->_isConnect) {

		wifiClassPtr_get()->ntpTime_loop();

		if(!wifiClassPtr_get()->_otaEnabled) 	wifiClassPtr_get()->MDSN_loop();
		else 									arduinoOTA_loop();	

		clientServer.handleLoop();	

		// if(timeDisplay->loop()){
		// 	String ret = wifiClassPtr_get()->ntpTime_toString(adri_timeNtp_instance()->timeget());	
		// 	Serial.write(27);	
		// 	fsprintf("\n[timer]%s\n", ret.c_str());	
		// }			
	}	
	

	// adriotMain->_wifi->loop();

/*
	relayPump_statu 		= adriotMain->_relayManagment->relay(relayPump)->getStatus();	
	sensorSolMoisture->loop(sensorSolMoisture_cap);
	if (sensorSolMoisture_cap) {
		if (!relayPump_statu) 	adriotMain->_relayManagment->relay(relayPump)->open();
	} else {
		if (relayPump_statu) 	adriotMain->_relayManagment->relay(relayPump)->close();
	}
*/	
}