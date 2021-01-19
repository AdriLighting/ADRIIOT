

#ifndef ADRIOT_MAIN_H
#define ADRIOT_MAIN_H
	#include <Arduino.h>
	#include "adriot_lib.h"

	#include <ArduinoJson.h>

	class adriot_module
	{
		
		enum mModule{
			mn_solMoisture,
			mn_relay,
			mn_temperature,
			mn_unk
		};
		enum mType{
			mt_sensor,
			mt_relay,
			mt_unk
		};
		mModule	_mName 	= mn_unk;
		mType 	_mType 	= mt_unk;
		int 	_pin 	= -1;
		int 	_id 	= -1;
		public:
			adriot_module(mModule name, mType type, int pin);
			// ~adriot_module();
			void nameToString(mModule value, String & result); 
			void typeToString(mType value, String & result); 
			void create();
	};
	
	class adriot_main
	{

		public:
			relayManagement 	* _relayManagment;
			dht22Management 	* _dht22Managment;

			wifiClass 			* _wifi;
			ALS_espwebserver 	* _webServer;

			adriot_main(const char * hName);
			~adriot_main(){};

			void loop();
		
	};


#endif // ADRIOT_MAIN_H