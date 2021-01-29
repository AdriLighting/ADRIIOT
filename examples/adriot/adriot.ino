ADC_MODE(ADC_VCC); 		// FOR TEST AS SENSOR MODULE


#define ADRIOT_UNOIOT 	0
#define ADRIOT_MQTT 	1
#define MQTT 			ADRIOT_MQTT

#include "secret.h"
#include <ADRIOT.h>

#define DEBUG

#if MQTT == ADRIOT_UNOIOT
	#include <adriot_arduinoiot.h>
	WiFiConnectionHandler 	ArduinoIoTPreferredConnection(SSID, PASS);	
#endif

adri_webserver			clientServer(80);
adri_socket				socketServer(81);	

adriot_main 			* adriotMain;
moduleManagment_spiff	* adriot_spiff;

adriTools_serialRead    * _serial;

adri_timer 				* timerCloud;

int 					setup_id = -1;


void setup()
{

	Serial.begin(115200);
  	for(unsigned long const serialBeginTime = millis(); !Serial && (millis() - serialBeginTime > 5000); ) { }
  	fsprintf("\n##################################################\n\n");


  	// 	INITIALISATION SERIALREAD MENU POUR DEBUG
    _serial = new adriTools_serialRead();
    _serial->cmd_array(1, 6); // 						touche
    _serial->cmd_item_add(1, "menu",					"a", 			"", _serial_menu);
    _serial->cmd_item_add(1, "_serial_ESPreset",		"z", 			"", _serial_ESPreset);
    _serial->cmd_item_add(1, "_serial_freeHeap",		"r", 			"", _serial_freeHeap);
    _serial->cmd_item_add(1, "_serial_print",			"q", 			"", _serial_print);
    _serial->cmd_item_add(1, "_serial_printJson",		"s", 			"", _serial_printJson);
    _serial->cmd_item_add(1, "_serial_print_spiff",		"d", 			"", _serial_print_spiff);
    _serial->cmd_array(2, 2); // 						!+touche=cmd
    _serial->cmd_item_add(2, "_serial_cmd",				"a", 			"", _serial_cmd);
    _serial->cmd_item_add(2, "_serial_websocket",		"z", 			"", _serial_websocket);
	// _serial->menu(); // Print menu


  	#if MQTT == ADRIOT_UNOIOT
		adriotMain = new adriot_main((char *)"ADRIOT", true);  	
  	#elif MQTT == ADRIOT_MQTT
		adriotMain = new adriot_main((char *)"ADRIOT", false, true, "domoticz/in", "domoticz/out", "192.168.0.135");  	
  	#else
  		adriotMain = new adriot_main((char *)"ADRIOT");
  	#endif	


	adriot_spiff = new moduleManagment_spiff();
	String json;
		

	// 	INITIALISATION DES MODULES POUR TEST (10MODULES MAX)
	// 								PARAM :
	// 	0									MODULE 		TYPE DE MODULE 	TYPE DE RELAY	TYPE DE SENSOR 		PIN 	USERNAME			MQTTIDX	
	// 	1												PIN		USERNAME			MQTT IDX
	// 	2																																		RESULT AS STRING
	// 																																			
// 											RELAY POUR CONTROLLER UN ECLAIRAGE 0/220											
//					adriot_spiff->create(	mn_relay, 	mt_relay, 		rt_light,		st_unk, 			2,		"blue_led", 		1, 		json); 	// 2 |MODULE TO JSON FILE
//					adriot_spiff->load(json); 																											// CREATE FROM JSON FILE
//					
//											RELAY POUR CONTROLLER UN ECLAIRAGE 0/220	
//	adriotMain->_moduleManagment->create(	mn_relay, 	mt_relay, 		rt_light,		st_unk, 			2,		"blue_led",			1); 			// 0 |CREATE WITH MOD
	adriotMain->_moduleManagment->create_light(			2,		"blue_led", 		1		); 															// 1 |LEDS BUIT-IN BLUE

// 											CONTROLLER UN ECLAIRAGE AVEC VARIATION DE LA LUMINOSITÉE PAR RELAY OU AUTRE
//	adriotMain->_moduleManagment->create(	mn_light, 	mt_lightDimmer,	rt_unk,			st_unk, 			16,		"red_led",			2); 			// 0 |CREATE WITH MOD
	adriotMain->_moduleManagment->create_lightDimmer(	16, 	"red_led",  		2		); 															// 1 |LEDS BUIT-IN RED	

// 											CAPTEUR DE TYPE ANALOG POUR HUMIDITÉE DU SOL
	adriotMain->_moduleManagment->create(	mn_sensor, 	mt_sensor, 		rt_unk, 		st_solMoisture, 	A0,		"ADC", 		5);						// 0 |ESP.getvcc()

// 											CAPTEUR DE TYPE DHT22 POUR LA TEMPÉRATURE ET L'HUMIDITÉE
//	adriotMain->_moduleManagment->create(	mn_sensor, 	mt_sensor, 		rt_unk, 		st_dht22, 			5,		"chambre d'adri",	3);				// 0 |CREATE WITH MOD
	adriotMain->_moduleManagment->create_temperature(	5, 		"chambre d'adri", 	3 		); 															// 1 |DHT22

// 											RELAY POUR CONTROLLER UNE PRISE 0/220
//	adriotMain->_moduleManagment->create(	mn_relay, 	mt_relay, 		rt_plug, 		st_unk, 			D5,		"prise",			4);				// 0 |CREATE WITH MOD
	adriotMain->_moduleManagment->create_plug(			D5, 	"machinne a café",	4		); 	 														// 1 |NULL


#if MQTT == ADRIOT_UNOIOT

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
#else

	// 	BEGIN WIFI CONNECT TO ROOTER
	adriotMain->wifiConnect(SECRET_SSID, SECRET_PASS);	
#endif

	
}


void loop()
{

	_serial->loop();

	adriotMain->loop();

	


	#if MQTT == ADRIOT_UNOIOT
		ArduinoCloud.update();	
		/*
		if (timerCloud->loop(250)){
			adriotMain->_moduleManagment->getIdByName("chambre d'adri", setup_id);
			boolean state;
			adriotMain->_dht22Managment->module(setup_id)->read_temperature(aic_temperature, state);
			adriotMain->_moduleManagment->getIdByName("blue_led", setup_id);
			adriotMain->_relayManagment->module(setup_id)->getStatus(aic_relay);		
		}
		*/
	#endif
}



//	#####################################################################################################
/*
										DEBUG && TESTING FUNCTIONS
	
*/

#if MQTT == ADRIOT_UNOIOT
	void onAicRelayChange(){
		adriotMain->_moduleManagment->getIdByName("blue_led", setup_id);
		adriotMain->_relayManagment->module(setup_id)->toggle();
		adriotMain->_relayManagment->module(setup_id)->getStatus(aic_relay);
	}
#endif

String _serial_menu(String cmd, String value) {
    adriTools_serialReadPtr_get()->menu();
    return "";
}
void _whenWebsocketIsConnect(){
	fsprintf("\n[TEST WEN UR CONNECTED]\n");
	String json;
	adriotMain->_moduleManagment->json_modulesValueList(json);
	adriotMain->_webServer->socket_send(json);

}	
String _serial_websocket(String cmd, String value){
	String json;
	if (value == "0") {
		adriotMain->_moduleManagment->json_modules(json);
		adriotMain->_webServer->socket_send(json);
	}
	if (value == "1") {
		adriotMain->_moduleManagment->json_modulesValue(json);
		adriotMain->_webServer->socket_send(json);
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
	adriotMain->_moduleManagment->print();
	return "";
}
String _serial_print_spiff(String cmd, String value){
	adriot_print_SPIFF("");
	return "";
}
String _serial_printJson(String cmd, String value){
	String json;
	adriotMain->_moduleManagment->json_modulesValue(json);
	adriotMain->_moduleManagment->json_modules(json);
	adriotMain->_moduleManagment->json_domoticz_modulesValue(json);
	adriotMain->_moduleManagment->json_mName(json);
	adriotMain->_moduleManagment->json_mType(json);
	adriotMain->_moduleManagment->json_rType(json);
	adriotMain->_moduleManagment->json_sType(json);
	return "";
}			
String _serial_cmd(String cmd, String value){
	int id;
	// String 	json;
	adriotMain->_moduleManagment->getIdByPos(value.toInt(), id);
	adriotMain->_relayManagment->module(id)->toggle();
	return "";
}
//	#####################################################################################################
