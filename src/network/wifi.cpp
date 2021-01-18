#include "wifi.h"

#include <ESP8266HTTPClient.h>
#include <adri_tools.h>


wifiClass * wifiClass_ptr;
wifiClass * wifiClassPtr_get(){
    return wifiClass_ptr;
}
wifiClass::wifiClass(const char * value) : wifiConnect(){
	wifiClass_ptr = this;
	_checkConnected_timer 	= new adri_timer(180000, 	"", false);
	_connectModTimer 		= new adri_timer(2000, 		"", false);
	_hostname 				= value;
	new wifi_credential_ap("");
	_ntpTime 				= new adri_timeNtp();
	
}




mod_wifiConnect_error wifiClass::error_get() {
	return _error_setup;
}

int 	wifiClass::_connectMod_get	() 				{ return _connectMod; }

void 	wifiClass::_connectMod_set	(int value) 	{ _connectMod = value; }

void 	wifiClass::_hostname_get		(String & ret) 	{ ret = ch_toString(_hostname);}	

void 	wifiClass::_otaEnabled_set 	(boolean ret)	{ _otaEnabled = ret;}

boolean wifiClass::_setup(WIFICONNECT_MOD cMod, WIFICONNECTSSID_MOD sMod) {

	if (!wifi_credential_sta_fromSPIFF()){
		wifi_credential_set(
			0, 	
			"",		
			"", 	
			"",
			"",
			""
		);
		wifi_credential_sta_toSpiff(); 
		return false;
	}
	// wifi_credential_sta_print();

	
	credential_sta_pos_set 		(0);
	connect_set 				(cMod);
	connectSSID_set 			(sMod);
	station_set 				(WIFI_STA);
	hostName_set 				(_hostname);
	setup_id					();
	print_cfg 					();

	// if (!_ap->load_fromSpiif()) {
	wifi_credentialAp_ptr_get()->hostname_set(ch_toString(_hostname));
	wifi_credentialAp_ptr_get()->psk_set("adriot1234");
	wifi_credentialAp_ptr_get()->ip_set("192.168.4.1");
	// wifi_credentialAp_ptr_get()->print();
	return true;
}
    // {(char *)"connectSSID",         wifiConnect_get_connectSSID},
    // {(char *)"statu_connectSSID",   wifiConnect_get_statu_connectSSID},
boolean wifiClass::_setupFromSpiff() {
	String s;
	if (!wifi_credential_sta_fromSPIFF()){
		wifi_credential_set(
			0, 	
			"",		
			"", 	
			"",
			"",
			""
		);
		wifi_credential_sta_toSpiff(); 
	}	
	if (!wifiConnect_load_fromSPIFF(s))				return false;
	if (literal_value("connectSSID", s) == "ap") 	return false;
	// fsprintf("\n[_setupFromSpiff connectSSID]%s\n", literal_value("connectSSID", s).c_str());
	// fsprintf("\n[_setupFromSpiff connect]%s\n", 	literal_value("connect", s).c_str());
	if (literal_value("connectSSID", s) == "loop") {
		connect_set 	(AWC_LOOP);
		connectSSID_set (AWCS_NORMAL);
		if (!_setup(AWC_LOOP, AWCS_NORMAL)) return false;
	}
	else if (literal_value("connectSSID", s) == "setup") {
		connect_set 	(AWC_SETUP);
		connectSSID_set (AWCS_NORMAL);		
		if (!_setup(AWC_SETUP, AWCS_NORMAL)) return false;
	}	
	else {
		connect_set 	(AWC_SETUP);
		connectSSID_set (AWCS_NORMAL);			
		if (!_setup(AWC_SETUP, AWCS_NORMAL)) return false;
	}

	return true;
}
boolean wifiClass::_setupAp(WIFICONNECT_MOD cMod, WIFICONNECTSSID_MOD sMod) {

	credential_sta_pos_set 		(0);
	connect_set 				(cMod);
	connectSSID_set 			(sMod);
	station_set 				(WIFI_STA);
	hostName_set 				(_hostname);
	setup_id();
	wifi_credentialAp_ptr_get()->hostname_set(ch_toString(_hostname));
	wifi_credentialAp_ptr_get()->psk_set("adriot1234");
	wifi_credentialAp_ptr_get()->ip_set("192.168.4.1");
	return true;
}
boolean wifiClass::_connect(WIFICONNECT_MOD cMod) {

	// lampPeripheralsInstance()->oled_clear();
	// lampPeripheralsInstance()->wificonnect("Connect wifiClass en cour");

	if (cMod == AWC_SETUP) {

		setup();

		// lampPeripheralsInstance()->oled_clear();
		// lampPeripheralsInstance()->wifiPrint();

		if(!_otaEnabled)	MDSN_begin			();
		else 				arduinoOTA_setup	(_hostname);

		ntpTime_setup();

		_connectModTimer->set_duration_max(2000);
		_connectModTimer->activate();
		_connectMod 		= 0;
		_connectMod_setTo 	= 1;

	}

	if (cMod == AWC_LOOP) {
		_connectModTimer->set_duration_max(2000);
		_connectModTimer->activate();
		_connectMod 		= 0;
		_connectMod_setTo 	= 2;
	}
	return true;
}
boolean wifiClass::_connectFromSpiff() {

	// lampPeripheralsInstance()->oled_clear();
	// lampPeripheralsInstance()->wificonnect("Connect wifiClass en cour");
	String s;
	WIFICONNECTSSID_MOD_toString(_connectSSID, s);
	fsprintf("DEBUG:%s\n",s.c_str());
	WIFICONNECT_MOD_toString(wifiConnect_instance()->_connect, s);
	fsprintf("DEBUG:%s\n",s.c_str());
	_connect(wifiConnect_instance()->_connect);
	if (_connectSSID==AWCS_AP) {

	} else {

	}
	return true;
}

void wifiClass::_loop() {


	if ( _connectModTimer->isActivate() ) {
		if ( _connectModTimer->loop_stop() ) {

			_connectMod = _connectMod_setTo;
			switch(_connectMod) {
				case 1:
				break;
				case 2:
					setupLoop();
				break;
			}
			
		}	
	}	

	wifi_loop();

	if ((!_isConnect) && (wifi_loop_statu()==wifi_statu_sta_isconnected) && (_connectMod == 2)) {
		_connectMod = 3;

		// fsprintf("\n[wifi_loop_statu : wifi_statu_sta_isconnected]\n")
		// lampPeripheralsInstance()->oled_clear();
		// lampPeripheralsInstance()->wifiPrint();

		if(!_otaEnabled)	MDSN_begin			();
		else 				arduinoOTA_setup	(_hostname);

		ntpTime_setup();

		_connectModTimer->set_duration_max(1500);
		_connectModTimer->activate();
		_connectMod_setTo 	= 1;		

	}
}	

void wifiClass::_checkConnected_start(){
	WiFiMode_t wifiMod = WiFi.getMode();
	if (wifiMod == WIFI_AP) return;
	_checkConnected_timer->activate();	
}
boolean wifiClass::_checkConnected(int & result){
    WiFiClient client;
    HTTPClient http;
	if (http.begin(client, "http://jigsaw.w3.org/HTTP/connection.html")) {  // HTTP
		result = http.GET();
		http.end();
		return true;
	} else {
		result = -2;
		return false;
	}
}
void wifiClass::_checkConnected_loop(){
	if (!_checkConnected_timer->isActivate()) return;
	// if (_checkConnected_timer->loop()) {
	// 	int result = -1;
	// 	boolean check = _checkConnected(result);
	// 	if ((!check) || (result <= 0)) {

	// 		char buffer[200];
		   	
	// 	   	String timeStr;
	// 	   	ntpTime_getTime(timeStr);
	// 	   	int wD, sMon, sYear;
	// 	   	adri_timeNtp_instance()->dateGet(wD, sMon, sYear);
	// 	   	String timeStamp = String(wD)+"/"+String(sMon)+"/"+String(sYear)+"_"+timeStr;
		   	
	// 		sprintf(buffer, "[_checkConnected_loop] begin: %d - result: %d", check, result);

	// 		fsprintf("\n%s\n", buffer);

	// 		String logStr = "";
	// 		adri_toolsPtr_get()->log_read(logStr, false);
	// 		adri_toolsPtr_get()->log_write(logStr, timeStamp, String(buffer));		
					
	// 		ESP.restart();
					
	// 	}
	// }
}	


void wifiClass::ntpTime_setup() {
	boolean sWifi = wifi_connect_result("");
	_ntpTime->setup(sWifi);
}
void wifiClass::ntpTime_loop() {
	if (!ntpTime_isSet()) return;
	_ntpTime->loop();
}			
void wifiClass::ntpTime_getTime(String & ret) {
	time_t 	time;
   	if (ntpTime_isSet()){
		time	= adri_timeNtp_instance()->timeget();
		ret 	= ntpTime_toString(time);	   		
   	} else {
   		ret = "";					 
   	}
}
String wifiClass::ntpTime_toString(time_t t) {
    char tmpStr[100];
    sprintf(tmpStr, "%02d:%02d:%02d", hour(t), minute(t), second(t));
    return String(tmpStr);
}
boolean wifiClass::ntpTime_isSet(){
	boolean ret = false;
	if(	_ntpTime->time_isSet ) {
		ret = true;
	} else {
		ret = false;
	}
	return ret;	
}









/*
wifiClass::wifiClass(){
	myWifi 		= new wifiConnect();
	myWifiAp 	= new wifi_credential_ap("");
}
void wifiClass::setup(String ssid, String pswd, const char * host){
	_hostname = host;
	myWifiAp->hostname_set(ch_toString(_hostname));
	wifi_credential_ap_register(myWifiAp);

	wifi_credential_sta_fromSPIFF();
	wifi_credential_set(
		0, 						
		"freebox_123_EXT", 		
		"phcaadax", 			
		"",						
		"",						
		""						
	);	
	wifi_credential_sta_toSpiff();	
	wifi_credential_sta_print();

	myWifi->load_fromSpiif 				();
	myWifi->credential_sta_pos_set 		(0);

	// configuration du lancement de la coonection
	myWifi->connect_set 				(_connectMod);
	if (_connectMod == AWC_LOOP) _SSIDMod = AWCS_NORMAL; 		// wifi connect loop ne supporte pas encor de multiple ssid
	myWifi->connectSSID_set 			(_SSIDMod);


	myWifi->station_set 				(WIFI_STA);
	myWifi->hostName_set 				(_hostname); 			// initialisation dns si ota desactiver
	myWifi->setup_id					();						// initialize les id STA

	//
	myWifiAp->psk_set 					("mywifiappsk");						// pswd AP
	myWifiAp->ip_set 					(myWifi->_credential_sta->ip_get());	// ip 	AP
	myWifiAp->print 					();	


}
void wifiClass::connect(){
	if (_connectMod == AWC_SETUP) {
		myWifi->setup 						();
		if(!_OTA) 	myWifi->MDSN_begin		();
		wifi_connect_statu 					();
		fsprintf("\n[_connectDone] : %s\n", on_time().c_str());
		_connectDone = 1;		
	}
}
void wifiClass::loop(){
	myWifi->MDSN_loop();
}
*/