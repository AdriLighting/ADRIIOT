

#ifndef ADRIOT_MAIN_H
#define ADRIOT_MAIN_H
	#include <Arduino.h>
	#include "adriot_lib.h"

	#include <ArduinoJson.h>
	#include <adri_tools.h>

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
extern PubSubClient PubSubClient_client;
	#define MAX_MODULE 10
	void PubSubClient_reconnect();
	enum mModule{
		mn_sensor,
		mn_relay,
		mn_light,
		mn_unk
	};
	enum mType{
		mt_sensor,
		mt_relay,
		mt_lightDimmer,
		mt_lightRGB,
		mt_lightRGBW,
		mt_unk
	};
	enum relayType{
		rt_light,
		rt_plug,
		rt_unk
	};
	enum sensorType{
		st_solMoisture,
		st_dht22,
		st_unk
	};	
	class moduleClass
	{
		private:
			String 		_name 		= "myModule";
			int 		_nameId		= -1;
			mModule		_mName 		= mn_unk;
			mType 		_mType 		= mt_unk;
			relayType	_rType 		= rt_unk;
			sensorType	_sType 		= st_unk;
			int 		_pin 		= -1;
			int 		_id 		= -1;
		public:
			int 		_mqttidx	= -1;

			moduleClass(mModule name, mType module_type, relayType relay_type, int pin, String username);
			moduleClass(mModule name, mType module_type, relayType relay_type, sensorType sType, int pin, String username);
			// ~adriot_module();

			void id_get(int & ret);
			void nameId_get(int & ret);
			void sType_get(sensorType & ret);
			void mType_get(mType & ret);
			void username_get(String & ret);
			void create();
			void print();
			void json_value(JsonObject & root);
			void json_domoticz_value(JsonObject & root);
			void json(JsonObject & root);
	};

	class moduleManagment_spiff
	{
		String mListeFileName = "/spiff_mListe.txt";
		String mListeArray[10];
	public:
		moduleManagment_spiff();
		~moduleManagment_spiff(){};
		void create(mModule mName, mType moType, relayType rType, sensorType sType, int pin, String username, int idx, String & ret);
		void add(int pos, String value);
		boolean toSpiff();
		void load(String file);
	};
	class moduleManagment
	{
		private:
			int _pos = 0;
		public:
			moduleManagment();
			~moduleManagment(){};

			String modulesValue[MAX_MODULE];
			void modulesValue_check();
			adri_timer * modulesValue_checkTimer;

			void mqqt_setidx(int idx);


			void create(mModule mName, mType moType, relayType rType, sensorType sType, int pin, String username, int idx = -1);
			void create_lightDimmer	(int pin, String username, int idx = -1);
			void create_temperature	(int pin, String username, int idx = -1);
			void create_plug 		(int pin, String username, int idx = -1);
			void create_light 		(int pin, String username, int idx = -1);
			void create_light 		(mType type, int pin, String username, int idx = -1);
			void create_sensor		(sensorType type, int pin, String username, int idx = -1);


			moduleClass * module(int pos);

			void toggleRelay(unsigned long delay);

			void print();

			int currentCnt();


			void json_modules(String & ret);
			void jsonObject_modules(JsonObject & root);

			void json_modulesValue(String & ret);
			void jsonObject_modulesValue(JsonObject & root);
			void jsonObject_modulesValue(int pos, JsonObject & root);
			void json_modulesValue(int pos, String & ret, boolean debug = true);
			void json_modulesValue(String pos, String & ret);
			void jsonObject_modulesValue(String pos, JsonObject & root);

			void json_modulesValueList(String & ret);
	
			void jsonObject_domoticz_modulesValue(int pos, JsonObject & root);
			void json_domoticz_modulesValue(int pos, String & ret, boolean debug = true);
			void jsonObject_domoticz_modulesValue(JsonObject & root);
			void json_domoticz_modulesValue(String & ret);
			
			void json_mName(String & ret);		
			void jsonObject_mName(JsonObject & root);		
			void json_mType(String & ret);		
			void jsonObject_mType(JsonObject & root);		
			void jsonObject_rtype(JsonObject & object);
			void json_rType(String & ret);	
			void jsonObject_stype(JsonObject & object);
			void json_sType(String & ret);

			void getByName(String search, int & ret);
			void getIdByName(String search, int & ret);
			void getIdByPos(int search, int & ret);

			void mNameToString(mModule value, String & result); 
			void mTypeToString(mType value, String & result); 	
			void rTypeToString(relayType value, String & result); 	
			void sTypeToString(sensorType value, String & result); 	

	};


// ############################################

	class adriot_mqtt
	{
		const char * _topicin	= "in";
		const char * _topicout  = "out";
		const char * _serverIp  = "out";
	public:
		adriot_mqtt(const char * topicin, const char * topicout, const char * serverIp);
		~adriot_mqtt(){};
		
	};


	extern relayManagment			adriot_relayManagement;
	extern dht22Managment			adriot_dht22Management;
	extern solmoistureManagment		adriot_solmoistureManagment;

	extern moduleManagment			adriot_moduleManagemnt;

	extern adri_timer 				* timer_test;
	// extern adriot_main 				* adriot_mainPtr;

	void adriot_print_SPIFF(String path = "");

	extern adri_socket				socketServer;
	void _whenWebsocketIsConnect();

	class adriot_main
	{

		public:
			relayManagment 			* _relayManagment;
			dht22Managment 			* _dht22Managment;
			moduleManagment 		* _moduleManagment;
			solmoistureManagment 	* _solmoistureManagment;

			wifiClass 				* _wifi;
			ALS_espwebserver 		* _webServer 	= nullptr;
			adriot_mqtt 			* _adriot_mqtt 	= nullptr;

			boolean 				_isArduinoIOT = false;
			boolean 				_isArdiotMQTT = false;

			adriot_main(
					const char * hName,
					boolean arduinoIOT = false, 
					boolean adriotMQTT = false, 
					const char * topicin = "", 
					const char * topicout = "", 
					const char * serverIp = ""
				);
			~adriot_main(){};

			void adriot_main_setPtr(adriot_main * ptr);

			void 	wifiConnect(String ssid, String psk);
			boolean wifiIsConnect();

			void loop(){

				
				_wifi->_loop();
				

				if (wifiIsConnect()) {

						fsprintf("\n[connected timer]\n");

						fsprintf("\t - _webServer begin\n");
						_webServer->serverFS(true); 	
						_webServer->serverInitialize();
						_webServer->serverBegin();
						_webServer->socketBegin();	
						socketServer._whenIsConnected = _whenWebsocketIsConnect;

					if (!_isArduinoIOT) {
						fsprintf("\t - ota begin\n");
						if(!_wifi->_otaEnabled)	_wifi->MDSN_begin	();
						else 					arduinoOTA_setup	(_wifi->_hostname);	

						fsprintf("\t - ntp begin\n");
						_wifi->ntpTime_setup();	

					} else {
						wifi_connect_statu();	
						fsprintf("\n");	
					}
					
					int freeHeap = ESP.getFreeHeap();
					fsprintf("\n[freeHeap] %d", freeHeap);
					
					_wifi->_connectMod = 0;
					_wifi->_isConnect = true;
				}

				if (_wifi->_isConnect) {

					if (!PubSubClient_client.connected()) {
						PubSubClient_reconnect();
					}
					PubSubClient_client.loop();

					_moduleManagment->modulesValue_check();

					if (!_isArduinoIOT) {
						_wifi->ntpTime_loop();
						if(!_wifi->_otaEnabled)	_wifi->MDSN_loop();
						else					arduinoOTA_loop();	
					}

						_webServer->serverLoop();	
						_webServer->socketLoop();	
				}		

			}

		
	};


#endif // ADRIOT_MAIN_H