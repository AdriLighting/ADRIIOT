// ADC_MODE(ADC_VCC); 		// FOR TEST AS SENSOR MODULE


#define ADRIOTOOLS_USETELNET

#define ADRIIOT_TFTILI9341 	1
#define ADRIIOT_TFTOLED 	2
#define ADRIIOT_TFT 		0

#define ADRIIOT_MQTT 	1
#define ADRIIOTMQTT		ADRIIOT_MQTT

#define ADRIOTOOLS_USELOGGER 1

#include "secret.h"

#include <adriiot.h>



// region ################################################ PTR
adri_webserver			clientServer(80);
adri_socket				socketServer(81);	

adriiot_main 			* adriiotMain;
moduleManagment_spiff	* adriiot_spiff;

adriToolsv2_serialRead	* _serial;
adri_toolsV2 			* _tools;
adri_timer 				* timerCloud;

int 					setup_id = -1;	
int 					pump_id = -1;	
int 					soil_id = -1;	

#ifdef ADRIOTOOLS_USETELNET
adri_telnet * _adri_telnet;	
#endif

#if ADRIIOT_TFT==ADRIIOT_TFTILI9341
tft_ui * _tft_ui;
#endif
// endregion >>>> PTR


void setup()
{

	Serial.begin(115200);
  	for(unsigned long const serialBeginTime = millis(); !Serial && (millis() - serialBeginTime > 5000); ) { }
  	Serial.println(F("\n##################################################\n\n"));

// region ################################################ TOOLS
	int freeHeap = ESP.getFreeHeap();
	Serial.printf("\n[freeHeap] %d", freeHeap);  	
	_tools = new adri_toolsV2(1024);
	_tools->heap_print();	
	_tools->ESP_core_info();
	_tools->tempStr_print();
	_tools->ESP_flash_info();
	_tools->tempStr_print();
	_tools->ESP_boot_info();
	_tools->tempStr_print();
// endregion >>>> TOOLS

// region ################################################ CONSTRUCTOR
  	#if ADRIIOTMQTT == ADRIIOT_MQTT
		adriiotMain = new adriiot_main((char *)"adriiot", mp_domoticz, "domoticz/in", "domoticz/out", "192.168.0.135");  	
  	#else
  		adriiotMain = new adriiot_main((char *)"adriiot");
  	#endif		
// endregion >>>> CONSTRUCTOR

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
    _serial->cmd_item_add(1, "screen next",			"h",		"", _serial_screenNext);
    _serial->cmd_array(2, 6); //					!+touche=cmd
    _serial->cmd_item_add(2, "cmd",					"a",		"", _serial_cmd);
    _serial->cmd_item_add(2, "websocket",			"z",		"", _serial_websocket);
    _serial->cmd_item_add(2, "loggerRegion",		"q",		"", adriToolLogger_serialMenu_region);
    _serial->cmd_item_add(2, "logger_regionAddLine","s",		"", adriToolLogger_serialMenu_regionAddLine);
    _serial->cmd_item_add(2, "logger_regionSerial",	"d",		"", adriToolLogger_serialMenu_regionSerialPrint);
    _serial->cmd_item_add(2, "logger",				"e",		"", adriToolLogger_serialMenu_cmd);    
	// _serial->menu(); // Print menu	
// endregion >>>> KEYBOARD MENU

// region ################################################ telenet
	#ifdef ADRIOTOOLS_USETELNET
		_adri_telnet = new adri_telnet();
		adri_toolsv2Ptr_get()->_telnetSetup 	= _adri_telnet->telnet_setup;
		adri_toolsv2Ptr_get()->_telnetLoop 		= _adri_telnet->telnet_loop;
		adri_toolsv2Ptr_get()->_telnetPut 		= _adri_telnet->telnet_put;
		adri_toolsv2Ptr_get()->_telnetGet 		= _adri_telnet->telnet_get;	
	#endif	
// endregion >>>> telenet

// region ################################################ logger
	adriToolsLogger * _looger = adriToolsLogger_ptrGet();
	_looger->activateByRegion_add("module check");
	_looger->activateByRegion_add("sockett receive/send"); 	
	_looger->activateByRegion_add("mqtt receive/send"); 	
	_looger->activateByRegion_add("mqtt parse"); 	
	_looger->activateByRegion_add("sockett parse"); 	
	// _looger->activateByRegion_toggleAddLine(0);
	// _looger->activateByRegion_toggleSerial(0);
	// _looger->activateByRegion_toggleSerial(1);
	// _looger->activateByRegion_toggleSerial(2);
	// _looger->activateByRegion_toggleSerial(3);
	// _looger->activateByRegion_toggleSerial(4);
	// _looger->spiffAddLine_otherRegion_toggle();
	// _looger->spiff_toggle();
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
//											STRIP RGB/RGBW Drived by Adafruit neopixel	
	adriiotMain->_moduleManagment->create_lightRGB(		D2,10,	"ruban led rgb",	7		); 															// 1 |LEDS BUIT-IN BLUE
	                                            		  		            		 		   															// 				
//											RELAY POUR CONTROLLER UN ECLAIRAGE 0/220	
//	adriiotMain->_moduleManagment->create(	mn_relay, 	mt_relay, 		rt_light,		st_unk, 			2,		"blue_led",			1); 			// 0 |CREATE WITH MOD
	// adriiotMain->_moduleManagment->create_light(		2,		"blue_led", 		1		); 															// 1 |LEDS BUIT-IN BLUE

// 											CONTROLLER UN ECLAIRAGE AVEC VARIATION DE LA LUMINOSITÉE PAR RELAY 
//	adriiotMain->_moduleManagment->create(	mn_light, 	mt_lightDimmer,	rt_unk,			st_unk, 			16,		"red_led",			2); 			// 0 |CREATE WITH MOD
	adriiotMain->_moduleManagment->create_lightDimmer(	16,		"red_led",  		2		); 															// 1 |LEDS BUIT-IN RED	

// 											CAPTEUR DE TYPE ANALOG POUR HUMIDITÉE DU SOL
	adriiotMain->_moduleManagment->create(	mn_sensor, 	mt_sensor, 		rt_unk, 		st_soilmoisture, 	A0,		"ADC", 		8);						// 0 |ESP.getvcc()
	adriiotMain->_moduleManagment->getIdByName("ADC", soil_id);	                                           			    	                  	 		   	 														// 

// 											CAPTEUR DE TYPE DHT22 POUR LA TEMPÉRATURE ET L'HUMIDITÉE
//	adriiotMain->_moduleManagment->create(	mn_sensor, 	mt_sensor, 		rt_unk, 		st_dht22, 			5,		"chambre d'adri",	3);				// 0 |CREATE WITH MOD
	// adriiotMain->_moduleManagment->create_temperature(	4,		"chambre d'adri", 	3 		); 															// 1 |DHT22
	                                                 	   		                  	  		   															// 
//	adriiotMain->_moduleManagment->create(	mn_sensor, 	mt_sensor, 		rt_unk, 		st_ds18b20,			5,		"chambre d'adri",	3);				// 0 |CREATE WITH MOD
	adriiotMain->_moduleManagment->create_temperatureEx(D1,		"ds2812b", 			6 		); 															// 1 |DS18B20 	

// 											RELAY POUR CONTROLLER UNE PRISE 0/220
//	adriiotMain->_moduleManagment->create(	mn_relay, 	mt_relay, 		rt_plug, 		st_unk, 			D5,		"prise",			4);				// 0 |CREATE WITH MOD
	adriiotMain->_moduleManagment->create_plugWater(			D3, 	"pump",				4		); 	 														// 1 |NULL
	adriiotMain->_moduleManagment->getIdByName("pump", pump_id);	                                           			    	                  	 		   	 														// 
	
	// adriiotMain->_moduleManagment->create_plug(			D6, 	"machinne a bobnbon",	4		); 	 														// 1 |NULL
	// adriiotMain->_moduleManagment->create_plug(			D6, 	"machinne a biére",	4		); 	 														// 1 |NULL
// endregion >>>> MODULES

// region ################################################ wificonnect
	delay(1000);
	adriiotMain->_moduleManagment->getIdByName("ruban led rgb", setup_id);	                                           			    	                  	 		   	 														// 
	adriiotMain->_RGBneoManagment->module(setup_id)->leds_rgb(255, 0, 0);

	adriiotMain->wifiConnect(SECRET_SSID, SECRET_PASS);	

	adriiotMain->_RGBneoManagment->module(setup_id)->leds_rgb(0, 255, 0);	
// endregion >>>> wificonnect

	#ifdef ADRIOTOOLS_USETELNET
		adri_toolsv2Ptr_get()->_telnetSetup();	
	#endif

	
// region ################################################ tft
	#if ADRIIOT_TFT==ADRIIOT_TFTILI9341
		meteo_update(true); 

		_tft_ui = new tft_ui();

		adriTFTscreen_set_pos(0);
		adriTFTscreen_display();
			
		new adriiot_tft_home();	
		new adriiot_tft_device();	

		int count = adriiot_main_ptrGet()->_moduleManagment->_pos;
		for (int i = 0; i < count; ++i)
		{
			adriiot_tft_update(i);
		}
	#endif
// endregion >>>> tft

	timerCloud = new adri_timer(100, "", true)	;

	_tools->heap_print();
}

boolean arroseMoi = false;
boolean jeTarrose = false;
boolean jeTarroseUpd = false;
void loop()
{

	// if (timerCloud->loop_stop()) {
	if (timerCloud->loop()) {
		// adriTFTscreen_next(1);
		// int count = adriiot_main_ptrGet()->_moduleManagment->_pos;
		// for (int i = 0; i < 10; ++i)
		// {
		// 	adriiot_tft_device_ptr->_init[i] = false;
		// }			
		// for (int i = 0; i < count; ++i)
		// {
		// 	adriiot_tft_update(i);
		// }		
		// adriToolsLogger_ptrGet()->activateByRegion_toggleAddLine(0);
		// 
		// 
		if (adriiotMain->_moduleManagment->module(pump_id)->_waterPumpSatu == wps_auto) {
			adriiotMain->_soilmoistureManagment->module(soil_id)->loop(arroseMoi);	
			if (arroseMoi) {
				// adriiotMain->_relayManagment->module(pump_id)->getStatus(jeTarrose);	
				// if (!jeTarrose) {
					if (!jeTarroseUpd) {fsprintf("\n[ARROSE]\n"); adriiotMain->_relayManagment->module(pump_id)->open();jeTarroseUpd=true;delay(500);}
					// if (timerCloud->loop()) adriiotMain->_moduleManagment->modulesValue_check(true);
				// }
			} else {
				adriiotMain->_relayManagment->module(pump_id)->getStatus(jeTarrose);	
				if (jeTarroseUpd) {fsprintf("\n[ARROSE PAS]\n"); adriiotMain->_relayManagment->module(pump_id)->close();jeTarroseUpd=false;delay(500);	}	
				// if (timerCloud->loop()) adriiotMain->_moduleManagment->modulesValue_check(true);
			}
		}	
	}



	_serial->loop();

	adriiotMain->loop();

	#if ADRIIOT_TFT==ADRIIOT_TFTILI9341
		_tft_ui->mainLoop();
	#endif
}



//	#####################################################################################################
/*
										DEBUG && TESTING FUNCTIONS
	
*/

// region ################################################ USERMENU FUNCTION


String _serial_menu(String cmd, String value) {
    adriToolsv2_serialReadPtr_get()->menu();
    return "";
}
void _whenWebsocketIsConnect(){
	ADRI_LOG(1, -1, 0, "<<<", "");
	ADRI_LOG(1, 0, 2, "", "");
	String json;
	adriiotMain->_moduleManagment->json_modulesValueList(json, 1);
	adriiotMain->socket_send(json, 1);	
	ADRI_LOG(1, 1, 2, "", "");
	ADRI_LOG(1, -1, 0, ">>>", "");
}	
String _serial_websocket(String cmd, String value){
	String json;
	if (value == "0") {
		adriiotMain->_moduleManagment->json_modules(json, 1);
		adriiotMain->socket_send(json, 1);
	}
	if (value == "1") {
		adriiotMain->_moduleManagment->json_modulesValue(json, 1);
		adriiotMain->socket_send(json, 1);
	}
    return "";
}	
String _serial_ESPreset(String cmd, String value){
    ESP.restart();
    return "";
}	
String _serial_freeHeap(String cmd, String value){
	_tools->heap_print();	
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
	adriiotMain->_moduleManagment->json_modulesValue(json, -1);
	adriiotMain->_moduleManagment->json_modules(json, -1);
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
	adriiotMain->_moduleManagment->json_domoticz_modulesValue(json, -1);
	return "";
}	
String _serial_cmd(String cmd, String value){
	int id;
	adriiotMain->_moduleManagment->getIdByPos(value.toInt(), id);
	adriiotMain->_relayManagment->module(id)->toggle();
	return "";
}
String _serial_screenNext(String cmd, String value){
		#if ADRIIOT_TFT > 0
			adriTFTscreen_next(1);
			int count = adriiot_main_ptrGet()->_moduleManagment->_pos;
			for (int i = 0; i < 10; ++i)
			{
				adriiot_tft_device_ptr->_init[i] = false;
			}			
			for (int i = 0; i < count; ++i)
			{
				adriiot_tft_update(i);
			}		
		#endif

	return "";
}

// endregion >>>> USERMENU FUNCTION
 
//	#####################################################################################################









/*


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
//											STRIP RGB/RGBW Drived by Adafruit neopixel	
//	adriiotMain->_moduleManagment->create(	mn_relay, 	mt_relay, 		rt_light,		st_unk, 			2,		"blue_led",			1); 			// 0 |CREATE WITH MOD
	adriiotMain->_moduleManagment->create_lightRGB(		D5,10,	"rgb",				7		); 															// 1 |LEDS BUIT-IN BLUE
	                                            		  		            		 		   															// 				
//											RELAY POUR CONTROLLER UN ECLAIRAGE 0/220	
//	adriiotMain->_moduleManagment->create(	mn_relay, 	mt_relay, 		rt_light,		st_unk, 			2,		"blue_led",			1); 			// 0 |CREATE WITH MOD
	adriiotMain->_moduleManagment->create_light(		2,		"blue_led", 		1		); 															// 1 |LEDS BUIT-IN BLUE

// 											CONTROLLER UN ECLAIRAGE AVEC VARIATION DE LA LUMINOSITÉE PAR RELAY 
//	adriiotMain->_moduleManagment->create(	mn_light, 	mt_lightDimmer,	rt_unk,			st_unk, 			16,		"red_led",			2); 			// 0 |CREATE WITH MOD
	adriiotMain->_moduleManagment->create_lightDimmer(	16,		"red_led",  		2		); 															// 1 |LEDS BUIT-IN RED	

// 											CAPTEUR DE TYPE ANALOG POUR HUMIDITÉE DU SOL
	// adriiotMain->_moduleManagment->create(	mn_sensor, 	mt_sensor, 		rt_unk, 		st_soilmoisture, 	A0,		"ADC", 		5);						// 0 |ESP.getvcc()

// 											CAPTEUR DE TYPE DHT22 POUR LA TEMPÉRATURE ET L'HUMIDITÉE
//	adriiotMain->_moduleManagment->create(	mn_sensor, 	mt_sensor, 		rt_unk, 		st_dht22, 			5,		"chambre d'adri",	3);				// 0 |CREATE WITH MOD
	adriiotMain->_moduleManagment->create_temperature(	4,		"chambre d'adri", 	3 		); 															// 1 |DHT22
	                                                 	   		                  	  		   															// 
//	adriiotMain->_moduleManagment->create(	mn_sensor, 	mt_sensor, 		rt_unk, 		st_ds18b20,			5,		"chambre d'adri",	3);				// 0 |CREATE WITH MOD
	adriiotMain->_moduleManagment->create_temperatureEx(5,		"ds2812b", 			6 		); 															// 1 |DS18B20 	

// 											RELAY POUR CONTROLLER UNE PRISE 0/220
//	adriiotMain->_moduleManagment->create(	mn_relay, 	mt_relay, 		rt_plug, 		st_unk, 			D5,		"prise",			4);				// 0 |CREATE WITH MOD
	adriiotMain->_moduleMan


*/