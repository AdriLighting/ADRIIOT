#include "adriiot_main.h"
#include <adri_tools_v2.h>

#define DEBUG

WiFiClient 		PubSubClient_espClient;

// region ################################################ SPIFFS PRINT FILES
int adriiot_print_SPIFFfolder(String path){

	Dir sub_dir = LittleFS.openDir(path);
	
	if (path == "node_modules"){ fsprintf("\t[%s][SKIP]\n", path.c_str()); return 0;}
	else fsprintf("\t[%s]\n", path.c_str());
	int totalsize = 0;
	while (sub_dir.next()) {
		if (sub_dir.isDirectory()) adriiot_print_SPIFFfolder(path + "/" + sub_dir.fileName());
		else {
			String sub_fileInfo = sub_dir.fileName() + (sub_dir.isDirectory() ? " [sub_dir]" : String(" (") + sub_dir.fileSize() + " b)");
			fsprintf("\t\t%s\n", sub_fileInfo.c_str());		
			totalsize += sub_dir.fileSize();
		}
	}
	if (totalsize > 0) fsprintf("\t\t\t[totalsize: %d b]\n", totalsize);	
	return totalsize;
}
void adriiot_print_SPIFF(String path){
	Dir dir = LittleFS.openDir(path);
	Serial.println("");
	Serial.println( F("List of files at root of filesystem:"));
	int totalsize = 0;
	while (dir.next()) {
		String fileInfo = dir.fileName() + (dir.isDirectory() ? " [DIR]" : String(" (") + dir.fileSize() + " b)");
		if (dir.isDirectory()) {
			int dSize = adriiot_print_SPIFFfolder(dir.fileName());
			totalsize += dSize;
		} else  {
			Serial.println(fileInfo);
			totalsize += dir.fileSize();
		}
	}
	fsprintf("\n[totalsize: %d b]\n", totalsize);
	Serial.println();
}	
// endregion >>>> SPIFFS PRINT FILES

// region ################################################ PTR
moduleClass 			* moduleClassArray[MAX_MODULE];

relayManagment			adriiot_relayManagement;
dht22Managment			adriiot_dht22Management;
DS18B20Managment		adriiot_ds18b20Management;
soilmoistureManagment	adriiot_soilmoistureManagment;

moduleManagment			adriiot_moduleManagemnt;

adriiot_main 			* adriiot_mainPtr;
adri_timer 				* timer_test;
// endregion >>>> PTR

// region ################################################ MQTT
adriiot_mqtt::adriiot_mqtt(const char * topicin, const char * topicout, const char * serverIp){
	_topicin 	= topicin;
	_topicout 	= topicout;
	_serverIp 	= serverIp;
	_client 	= new PubSubClient(PubSubClient_espClient);
	fsprintf("\n[adriiot_mqtt::adriiot_mqtt] %s - %s - %s\n", _topicin, _topicout, _serverIp);
}
void adriiot_mqtt::reconnect() {
	while (!_client->connected()) {
			fsprintf("\n[adriiot_mqtt]\n\tconnection in progress\n");
			String clientId = "ESP8266Client-";
			clientId += String(random(0xffff), HEX);
		if (_client->connect(clientId.c_str())) {
			fsprintf("\n[adriiot_mqtt]\n\tconnection success\n");
			_client->subscribe("domoticz/out");
		} else {
			fsprintf("\n[adriiot_mqtt]\n\tconnection failed, rc= %d\n", _client->state());
			delay(5000);
		}
	}
}
void adriiot_mqtt::loop(){
	if (!_client->connected()) {
		reconnect();
	}
	_client->loop();
}
void adriiot_mqtt::connect() {
	_client->setServer(_serverIp, _serverPort);
}
void adriiot_mqtt::publish(const char* payload) {
	_client->publish(_topicin, payload);	
}
void adriiot_mqtt::publish(String jsonStr) {
	char buffer[512];
	sprintf(buffer, "%s", jsonStr.c_str());
	_client->publish(_topicin, buffer);	
}	
// endregion >>>> MQTT

// region ################################################ MAIN
void adriiot_main::adriiot_main_setPtr(adriiot_main * ptr){
	adriiot_mainPtr = ptr;
}

adriiot_main::adriiot_main(
		const char * hName,
		boolean arduinoIOT, 
		boolean adriiotMQTT, 
		const char * topicin, 
		const char * topicout , 
		const char * serverIp
	){

	adriiot_mainPtr = this;

	_isArduinoIOT = arduinoIOT;
	_isArdiotMQTT = adriiotMQTT;


	if (_isArdiotMQTT) _adriiot_mqtt = new adriiot_mqtt(topicin, topicout, serverIp);

	fsprintf("\n[adriiot BEGIN]\n\tarduinoIOT: %d\n\tadriiotMQTT! %d\n", _isArduinoIOT, _isArdiotMQTT);	
	
	LittleFS.begin();

	_relayManagment 		= &adriiot_relayManagement;
	_dht22Managment 		= &adriiot_dht22Management;
	_ds18b20managment 		= &adriiot_ds18b20Management;
	_soilmoistureManagment 	= &adriiot_soilmoistureManagment;

	_moduleManagment 		= &adriiot_moduleManagemnt;

	_tools 				= new adri_toolsV2();

	_looger 		= new adriTools_logger();

	_wifi 			= new wifiClass(hName);

	_webServer 		= new ALS_espwebserver();

	timer_test 		= new adri_timer(1000,"",true);

}	
// endregion >>>> MAIN


// region ################################################ WIFICONNECT
void adriiot_main::wifiConnect(String ssid, String psk){
	#ifdef DEBUG
		fsprintf("\n[adriiot WIFI SETUP]\n");	
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
boolean adriiot_main::wifiIsConnect(){
	if (_isArduinoIOT) {
		if (wifi_connect_result("") && !_wifi->_isConnect) {
			return true;	
		}
	} else {
 		_adriiot_mqtt->connect();
		if (_wifi->_connectMod == 1) return true;
	}
	return false;
}	
// endregion >>>> WIFICONNECT

// region ################################################ dashboard uodate
void adriiot_main::socket_send(String msg){
	ADRI_LOG(1, 0, 2,"","");
	_webServer->socket_send(msg);
	ADRI_LOG(1, 2, 2,"%s",msg.c_str());
	ADRI_LOG(1, 1, 2,"","");
}
void adriiot_main::mqqt_send(String msg){
	ADRI_LOG(1, 0, 2,"","");
	char buffer[255];
	sprintf(buffer, "%s", msg.c_str());
	ADRI_LOG(1, 2, 2,"%s",buffer);
	adriiot_mainPtr->_adriiot_mqtt->publish(buffer);
	ADRI_LOG(1, 1, 2,"","");
}
void adriiot_main::dashboard_webClient_update(String msg){
	socket_send(msg);	
	mqqt_send(msg);	
}
void adriiot_main::dashboard_webClient_update(int pos){
	String s;
	_moduleManagment->json_domoticz_modulesValue(pos, s, false);
	mqqt_send(s);
	s= "";
	_moduleManagment->json_modulesValue(pos, s, false);
	socket_send(s);	
}	
// endregion >>>> dashboard uodate


// region ################################################ logger
String _serial_logger_region(String cmd, String value){
	adriTools_logger * _looger = adriTools_logger_ptrGet();
	ADRI_LOG(-1, 0, 2,"","");
	ADRI_LOG(-1, 2, 2, "cmd: %s - value: %S", cmd.c_str(), value.c_str());	
	int pos = value.toInt();
	_looger->activateByVariable_toggle(pos);
	ADRI_LOG(-1, 1, 2,"","");
	return "";
}

String _serial_logger(String cmd, String value){
	adriTools_logger * _looger = adriTools_logger_ptrGet();
	ADRI_LOG(-1, 0, 2,"","");
	ADRI_LOG(-1, 2, 2, "cmd: %s - value: %S", cmd.c_str(), value.c_str());	
	int pos = value.toInt();
	if (value == "a") {
		_looger->serial_menu();
	} else if (value == "z") {
		_looger->printer_display_toggle();
	} else if (value == "e") {
		_looger->printer_heap_toggle();
	} else if (value == "r") {
		_looger->printer_timestamp_toggle();
	} else if (value == "t") {
		_looger->spiff_toggle();
	} else if (value == "y") {
		_looger->spiff_readCurrent();
	} else if (value == "u") {
		_looger->spiff_removeCurrent();
	} else {
		_looger->printer_display_lvl_set(pos);	
	}
	ADRI_LOG(-1, 1, 2,"","");
	return "";
}		
// endregion >>>> logger



// ############################################

#include "adriiot_modulemanagment.h"

// ############################################

#include "adriiot_moduleclass.h"





/*
soilmoistureClass 	* sensorsoilmoisture 	= nullptr;
boolean 			sensorsoilmoisture_cap 	= false;

int					relayPump 				= -1;
boolean 			relayPump_statu 		= false;

int					sensorTemperature		= -1;


	#ifdef DEBUG
		fsprintf("\n[adriiot SOL MOISTURE SENSOR BEGIN]\n");	
	#endif
	sensorsoilmoisture = new soilmoistureClass(false, A0);


	if ((relayPump!=-1) && (sensorsoilmoisture!=nullptr)) {
		relayPump_statu 		= adriiotMain->_relayManagment->relay(relayPump)->getStatus();	
		sensorsoilmoisture->loop(sensorsoilmoisture_cap);
		if (sensorsoilmoisture_cap) {
			if (!relayPump_statu) 	adriiotMain->_relayManagment->relay(relayPump)->open();
		} else {
			if (relayPump_statu) 	adriiotMain->_relayManagment->relay(relayPump)->close();
		}		
	}
*/