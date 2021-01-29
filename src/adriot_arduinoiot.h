#ifndef ADRIOT_ARDUINOIOT_H
	#define ADRIOT_ARDUINOIOT_H

	#include <ArduinoIoTCloud.h>
	#include <Arduino_ConnectionHandler.h>

	extern WiFiConnectionHandler ArduinoIoTPreferredConnection;

	const char THING_ID[]           = SECRET_THING_ID;
	const char DEVICE_LOGIN_NAME[]  = SECRET_LOGIN_NAME;

	const char SSID[]               = SECRET_SSID;
	const char PASS[]               = SECRET_PASS;
	const char DEVICE_KEY[]  		= SECRET_DEVICE_KEY:


	float 		aic_temperature	= 1;
	boolean 	aic_relay 		= true;
	
#endif // ADRIOT_ARDUINOIOT_H
