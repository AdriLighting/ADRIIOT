ADC_MODE(ADC_VCC); 		// FOR TEST AS SENSOR MODULE


#define adriiot_UNOIOT 	0
#define adriiot_MQTT 	1
#define MQTT 			adriiot_MQTT

#include "secret.h"
#include <adriiot.h>

#define DEBUG

// region ################################################ PTR
#if MQTT == adriiot_UNOIOT
	#include <adriiot_arduinoiot.h>
	WiFiConnectionHandler 	ArduinoIoTPreferredConnection(SSID, PASS);	
#endif

adri_webserver			clientServer(80);
adri_socket				socketServer(81);	

adriiot_main 			* adriiotMain;
moduleManagment_spiff	* adriiot_spiff;

adriToolsv2_serialRead	* _serial;

adri_timer 				* timerCloud;

int 					setup_id = -1;	
// endregion >>>> PTR


void setup()
{

	Serial.begin(115200);
  	for(unsigned long const serialBeginTime = millis(); !Serial && (millis() - serialBeginTime > 5000); ) { }
  	fsprintf("\n##################################################\n\n");

// region ################################################ KEYBOARD MENU
  	// 	INITIALISATION SERIALREAD MENU POUR DEBUG
    _serial = new adriToolsv2_serialRead();
    _serial->cmd_array(1, 9); // 					touche
    _serial->cmd_item_add(1, "menu",				"a",		"", _serial_menu);
    _serial->cmd_item_add(1, "ESPreset",			"z",		"", _serial_ESPreset);
    _serial->cmd_item_add(1, "freeHeap",			"r",		"", _serial_freeHeap);
    _serial->cmd_item_add(1, "print",				"q",		"", _serial_print);
    _serial->cmd_item_add(1, "printJson_module",	"s",		"", _serial_printJson_module);
    _serial->cmd_item_add(1, "printJson_mod",		"d",		"", _serial_printJson_mod);
    _serial->cmd_item_add(1, "printJson_domoticz",	"f",		"", _serial_printJson_domoticz);
    _serial->cmd_item_add(1, "print_spiff",			"g",		"", _serial_print_spiff);
    _serial->cmd_item_add(1, "adriTrace",			"h",		"", _serial_adriTrace);
    _serial->cmd_array(2, 4); //					!+touche=cmd
    _serial->cmd_item_add(2, "cmd",					"a",		"", _serial_cmd);
    _serial->cmd_item_add(2, "websocket",			"z",		"", _serial_websocket);
    _serial->cmd_item_add(2, "serial_loggerRegion",	"s",		"", _serial_logger_region);
    _serial->cmd_item_add(2, "serial_logger",		"q",		"", _serial_logger);    
	// _serial->menu(); // Print menu	
// endregion >>>> KEYBOARD MENU

// region ################################################ CONSTRUCTOR
  	#if MQTT == adriiot_UNOIOT
		adriiotMain = new adriiot_main((char *)"adriiot", true);  	
  	#elif MQTT == adriiot_MQTT
		adriiotMain = new adriiot_main((char *)"adriiot", false, true, "domoticz/in", "domoticz/out", "192.168.0.135");  	
  	#else
  		adriiotMain = new adriiot_main((char *)"adriiot");
  	#endif		
// endregion >>>> CONSTRUCTOR

// region ################################################ logger
	adriTools_logger * _looger = adriTools_logger_ptrGet();
	_looger->activateByVariable_add("module update");
	_looger->activateByVariable_add("sockett/mqtt"); 	
// endregion >>>> logger

// region ################################################ MODULE FROM SPIFF
	adriiot_spiff = new moduleManagment_spiff();
	String json;	
// endregion >>>> MODULE FROM SPIFF CONTRUCTOR
		
// region ################################################ MODULES
	// 	INITIALISATION DES MODULES POUR TEST (10MODULES MAX)
	// 								PARAM :
	// 	0									MODULE 		TYPE DE MODULE 	TYPE DE RELAY	TYPE DE SENSOR 		PIN 	USERNAME			MQTTIDX	
	// 	1												PIN		USERNAME			MQTT IDX
	// 	2																																		RESULT AS STRING
	// 																																			
// 											RELAY POUR CONTROLLER UN ECLAIRAGE 0/220											
//					adriiot_spiff->create(	mn_relay, 	mt_relay, 		rt_light,		st_unk, 			2,		"blue_led", 		1, 		json); 	// 2 |MODULE TO JSON FILE
//					adriiot_spiff->load(json); 																											// CREATE FROM JSON FILE
//					
//											RELAY POUR CONTROLLER UN ECLAIRAGE 0/220	
//	adriiotMain->_moduleManagment->create(	mn_relay, 	mt_relay, 		rt_light,		st_unk, 			2,		"blue_led",			1); 			// 0 |CREATE WITH MOD
	adriiotMain->_moduleManagment->create_light(			2,	"blue_led", 		1		); 															// 1 |LEDS BUIT-IN BLUE

// 											CONTROLLER UN ECLAIRAGE AVEC VARIATION DE LA LUMINOSITÉE PAR RELAY OU AUTRE
//	adriiotMain->_moduleManagment->create(	mn_light, 	mt_lightDimmer,	rt_unk,			st_unk, 			16,		"red_led",			2); 			// 0 |CREATE WITH MOD
	adriiotMain->_moduleManagment->create_lightDimmer(	16, 	"red_led",  		2		); 															// 1 |LEDS BUIT-IN RED	

// 											CAPTEUR DE TYPE ANALOG POUR HUMIDITÉE DU SOL
	// adriiotMain->_moduleManagment->create(	mn_sensor, 	mt_sensor, 		rt_unk, 		st_soilmoisture, 	A0,		"ADC", 		5);						// 0 |ESP.getvcc()

// 											CAPTEUR DE TYPE DHT22 POUR LA TEMPÉRATURE ET L'HUMIDITÉE
//	adriiotMain->_moduleManagment->create(	mn_sensor, 	mt_sensor, 		rt_unk, 		st_dht22, 			5,		"chambre d'adri",	3);				// 0 |CREATE WITH MOD
	adriiotMain->_moduleManagment->create_temperature(	4,		"chambre d'adri", 	3 		); 															// 1 |DHT22
	                                                 	   		                  	  		   															// 
//	adriiotMain->_moduleManagment->create(	mn_sensor, 	mt_sensor, 		rt_unk, 		st_ds18b20,			5,		"chambre d'adri",	3);				// 0 |CREATE WITH MOD
	adriiotMain->_moduleManagment->create_temperatureEx(	5,	"ds2812b", 			6 		); 															// 1 |DS18B20 	

// 											RELAY POUR CONTROLLER UNE PRISE 0/220
//	adriiotMain->_moduleManagment->create(	mn_relay, 	mt_relay, 		rt_plug, 		st_unk, 			D5,		"prise",			4);				// 0 |CREATE WITH MOD
	adriiotMain->_moduleManagment->create_plug(			D5, 	"machinne a café",	4		); 	 														// 1 |NULL
// endregion >>>> MODULES

#if MQTT == adriiot_UNOIOT
// region ################################################ ARDUINOIOT CLOUD
	fsprintf("\n[ArduinoCloud setup]\n");

	// 	INITITIALISATION DUR SERVEUR MQTT
	ArduinoCloud.setBoardId(DEVICE_LOGIN_NAME);
	ArduinoCloud.setSecretDeviceKey(DEVICE_KEY);
	ArduinoCloud.setThingId(THING_ID);

	// 	MISE EN MEMOIR DES FONCTION ASSOCIER AUX VARRIABLES
	ArduinoCloud.addProperty(aic_temperature, READ, ON_CHANGE, NULL, 1);
	ArduinoCloud.addProperty(aic_relay, READWRITE, ON_CHANGE, onAicRelayChange);

	// 	BEGIN WIFI CONNECT TO ROOTER
	ArduinoCloud.begin(ArduinoIoTPreferredConnection);
	setDebugMessageLevel(2);
	ArduinoCloud.printDebugInfo();
	fsprintf("\n[ArduinoCloud begin]\n");

	// 	TIMER POUR METTRE A JOUR LES VARIABLES
	timerCloud = new adri_timer(1000, "", true);	
// endregion >>>> ARDUINOIOT CLOUD
#else
	// 	BEGIN WIFI CONNECT TO ROOTER
	adriiotMain->wifiConnect(SECRET_SSID, SECRET_PASS);	
#endif
	
}


void loop()
{

	_serial->loop();

	adriiotMain->loop();

	#if MQTT == adriiot_UNOIOT
		ArduinoCloud.update();	
		/*
		if (timerCloud->loop(250)){
			adriiotMain->_moduleManagment->getIdByName("chambre d'adri", setup_id);
			boolean state;
			adriiotMain->_dht22Managment->module(setup_id)->read_temperature(aic_temperature, state);
			adriiotMain->_moduleManagment->getIdByName("blue_led", setup_id);
			adriiotMain->_relayManagment->module(setup_id)->getStatus(aic_relay);		
		}
		*/
	#endif
}



//	#####################################################################################################
/*
										DEBUG && TESTING FUNCTIONS
	
*/

// region ################################################ USERMENU FUNCTION
#if MQTT == adriiot_UNOIOT
	void onAicRelayChange(){
		adriiotMain->_moduleManagment->getIdByName("blue_led", setup_id);
		adriiotMain->_relayManagment->module(setup_id)->toggle();
		adriiotMain->_relayManagment->module(setup_id)->getStatus(aic_relay);
	}
#endif

String _serial_menu(String cmd, String value) {
    adriToolsv2_serialReadPtr_get()->menu();
    return "";
}
void _whenWebsocketIsConnect(){
	fsprintf("\n[TEST WEN UR CONNECTED]\n");
	String json;
	adriiotMain->_moduleManagment->json_modulesValueList(json);
	adriiotMain->_webServer->socket_send(json);

}	
String _serial_websocket(String cmd, String value){
	String json;
	if (value == "0") {
		adriiotMain->_moduleManagment->json_modules(json);
		adriiotMain->_webServer->socket_send(json);
	}
	if (value == "1") {
		adriiotMain->_moduleManagment->json_modulesValue(json);
		adriiotMain->_webServer->socket_send(json);
	}
    return "";
}	
String _serial_ESPreset(String cmd, String value){
    ESP.restart();
    return "";
}	
String _serial_freeHeap(String cmd, String value){
	int freeHeap = ESP.getFreeHeap();
	fsprintf("\n[freeHeap] %d", freeHeap);
	return "";
}		
String _serial_print(String cmd, String value){
	adriiotMain->_moduleManagment->print();
	return "";
}
String _serial_print_spiff(String cmd, String value){
	adriiot_print_SPIFF("");
	return "";
}
String _serial_printJson_module(String cmd, String value){
	String json;
	adriiotMain->_moduleManagment->json_modulesValue(json);
	adriiotMain->_moduleManagment->json_modules(json);
	return "";
}	
String _serial_printJson_mod(String cmd, String value){
	String json;
	adriiotMain->_moduleManagment->json_mName(json);
	adriiotMain->_moduleManagment->json_mType(json);
	adriiotMain->_moduleManagment->json_rType(json);
	adriiotMain->_moduleManagment->json_sType(json);
	return "";
}		
String _serial_printJson_domoticz(String cmd, String value){
	String json;
	adriiotMain->_moduleManagment->json_domoticz_modulesValue(json);
	return "";
}	
String _serial_cmd(String cmd, String value){
	int id;
	// String 	json;
	adriiotMain->_moduleManagment->getIdByPos(value.toInt(), id);
	adriiotMain->_relayManagment->module(id)->toggle();
	return "";
}
String _serial_adriTrace(String cmd, String value){
	adri_toolsv2_trace =! adri_toolsv2_trace;
	fsprintfv(adri_toolsv2_trace, "\n[adri_toolsv2_trace]\n");
	return "";
}

// endregion >>>> USERMENU FUNCTION
 
//	#####################################################################################################
