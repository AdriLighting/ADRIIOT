#include "adriot_main.h"
#include <adri_tools.h>

#define DEBUG



WiFiClient 		PubSubClient_espClient;
PubSubClient 	PubSubClient_client(PubSubClient_espClient);
long 			PubSubClient_lastMsg = 0;
char 			PubSubClient_msg[50];
int 			PubSubClient_value = 0;
void PubSubClient_reconnect() {
	while (!PubSubClient_client.connected()) {
			Serial.println("");
			Serial.println("");
			Serial.print("Attempting MQTT connection...");
			String clientId = "ESP8266Client-";
			clientId += String(random(0xffff), HEX);
		if (PubSubClient_client.connect(clientId.c_str())) {
			Serial.println("connected");
			PubSubClient_client.subscribe("domoticz/out");
		} else {
			Serial.print("failed, rc=");
			Serial.print(PubSubClient_client.state());
			Serial.println(" try again in 5 seconds");
			delay(5000);
		}
	}
}


int adriot_print_SPIFFfolder(String path){

	Dir sub_dir = LittleFS.openDir(path);
	
	if (path == "node_modules"){ fsprintf("\t[%s][SKIP]\n", path.c_str()); return 0;}
	else fsprintf("\t[%s]\n", path.c_str());
	int totalsize = 0;
	while (sub_dir.next()) {
		if (sub_dir.isDirectory()) adriot_print_SPIFFfolder(path + "/" + sub_dir.fileName());
		else {
			String sub_fileInfo = sub_dir.fileName() + (sub_dir.isDirectory() ? " [sub_dir]" : String(" (") + sub_dir.fileSize() + " b)");
			fsprintf("\t\t%s\n", sub_fileInfo.c_str());		
			totalsize += sub_dir.fileSize();
		}
	}
	if (totalsize > 0) fsprintf("\t\t\t[totalsize: %d b]\n", totalsize);	
	return totalsize;
}
void adriot_print_SPIFF(String path){
	Dir dir = LittleFS.openDir(path);
	Serial.println("");
	Serial.println( F("List of files at root of filesystem:"));
	int totalsize = 0;
	while (dir.next()) {
		String fileInfo = dir.fileName() + (dir.isDirectory() ? " [DIR]" : String(" (") + dir.fileSize() + " b)");
		if (dir.isDirectory()) {
			int dSize = adriot_print_SPIFFfolder(dir.fileName());
			totalsize += dSize;
		} else  {
			Serial.println(fileInfo);
			totalsize += dir.fileSize();
		}
	}
	fsprintf("\n[totalsize: %d b]\n", totalsize);
	Serial.println();
}


// 	###############################################################
moduleClass 			* moduleClassArray[MAX_MODULE];

relayManagment			adriot_relayManagement;
dht22Managment			adriot_dht22Management;
solmoistureManagment	adriot_solmoistureManagment;

moduleManagment			adriot_moduleManagemnt;
// 	###############################################################
adriot_main 			* adriot_mainPtr;
adri_timer 				* timer_test;
// 	###############################################################



adriot_mqtt::adriot_mqtt(const char * topicin, const char * topicout, const char * serverIp){
	_topicin 	= topicin;
	_topicout 	= topicout;
	_serverIp 	= serverIp;
	fsprintf("\n[adriot_mqtt::adriot_mqtt] %s - %s - %s\n", _topicin, _topicout, _serverIp);
}



void adriot_main::adriot_main_setPtr(adriot_main * ptr){
	adriot_mainPtr = ptr;
}

adriot_main::adriot_main(
		const char * hName,
		boolean arduinoIOT, 
		boolean adriotMQTT, 
		const char * topicin, 
		const char * topicout , 
		const char * serverIp
	){

	adriot_mainPtr = this;

	_isArduinoIOT = arduinoIOT;
	_isArdiotMQTT = adriotMQTT;


	if (_isArdiotMQTT) _adriot_mqtt = new adriot_mqtt(topicin, topicout, serverIp);

	fsprintf("\n[ADRIOT BEGIN]\n\tarduinoIOT: %d\n\tadriotMQTT! %d\n", _isArduinoIOT, _isArdiotMQTT);	
	
	LittleFS.begin();

	_relayManagment 		= &adriot_relayManagement;
	_dht22Managment 		= &adriot_dht22Management;
	_solmoistureManagment 	= &adriot_solmoistureManagment;

	_moduleManagment 		= &adriot_moduleManagemnt;


	_wifi 			= new wifiClass(hName);

	_webServer 		= new ALS_espwebserver();

	timer_test 		= new adri_timer(1000,"",true);

}


void adriot_main::wifiConnect(String ssid, String psk){
	#ifdef DEBUG
		fsprintf("\n[ADRIOT WIFI SETUP]\n");	
	#endif

	// #ifdef WIFISPIFF
		wifi_credential_sta_fromSPIFF();
		wifi_credential_set(
			0, 	
			ssid,		
			psk, 	
			"",
			"",
			""
		);
		wifi_credential_sta_toSpiff(); 
		// wifi_credential_sta_print(); 	
		wifiConnect_instance()->connect_set(AWC_SETUP);
		wifiConnect_instance()->connectSSID_set(AWCS_NORMAL);		
		wifiConnect_instance()->savToSpiff();		
	// #endif

	if (!_wifi->_setupFromSpiff()) { 
		_wifi->_setupAp(AWC_SETUP, AWCS_AP);
		_wifi->_connect(AWC_SETUP);
	} else {
		_wifi->_connect(AWC_SETUP);
	}

	// wifi_connect_statu();	
}
boolean adriot_main::wifiIsConnect(){
	if (_isArduinoIOT) {
		if (wifi_connect_result("") && !_wifi->_isConnect) {
			return true;	
		}
	} else {
 		PubSubClient_client.setServer("192.168.0.135", 1883);
		if (_wifi->_connectMod == 1) return true;
	}
	return false;
}



// ############################################

#include "adriot_modulemanagment.h"

// ############################################

#include "adriot_moduleclass.h"





/*
solmoistureClass 	* sensorSolMoisture 	= nullptr;
boolean 			sensorSolMoisture_cap 	= false;

int					relayPump 				= -1;
boolean 			relayPump_statu 		= false;

int					sensorTemperature		= -1;


	#ifdef DEBUG
		fsprintf("\n[ADRIOT SOL MOISTURE SENSOR BEGIN]\n");	
	#endif
	sensorSolMoisture = new solmoistureClass(false, A0);


	if ((relayPump!=-1) && (sensorSolMoisture!=nullptr)) {
		relayPump_statu 		= adriotMain->_relayManagment->relay(relayPump)->getStatus();	
		sensorSolMoisture->loop(sensorSolMoisture_cap);
		if (sensorSolMoisture_cap) {
			if (!relayPump_statu) 	adriotMain->_relayManagment->relay(relayPump)->open();
		} else {
			if (relayPump_statu) 	adriotMain->_relayManagment->relay(relayPump)->close();
		}		
	}
*/