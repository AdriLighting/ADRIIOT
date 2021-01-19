

#ifndef ADRIOT_MAIN_H
#define ADRIOT_MAIN_H
	#include <Arduino.h>
	#include "adriot_lib.h"

	class adriot_main
	{

		public:
			relayManagement 	* _relayManagment;
			wifiClass 			* _wifi;
			ALS_espwebserver 	* _webServer;
			adriot_main(const char * hName);
			~adriot_main(){};
			void loop();
		
	};

	class adriot_module
	{
		enum module{
			solMoisture,
			relay,
			temperature
		};
		
		public:
			adriot_module();
			// ~adriot_module();

	};
#endif // ADRIOT_MAIN_H