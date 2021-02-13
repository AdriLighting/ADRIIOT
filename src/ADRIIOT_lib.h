	#include <Arduino.h>

	#include <ArduinoJson.h>

	#include <ESP8266WiFi.h>

	#include <PubSubClient.h>


	#if ADRIOTOOLS_USELOGGER==1
		#include <adri_logger.h>
	#endif
	#if ADRIOTOOLS_USELOGGER==2
		#include <adri_soft_logger.h>
	#endif
	#include <adri_tools_v2.h>

	#ifdef ADRIOTOOLS_USETELNET
		#include <adri_tools_v2_telnet.h>
	#endif
	
	#include <adri_tools_v2_serialMenu.h>

	#include <adriiot_soilmoisture.h>
	#include <adriiot_relay.h>
	#include <adriiot_dht22.h>
	#include <adriiot_DS18B20.h>
	#include <ADRIIOT_RGBneo.h>
	#include <ADRIIOT_lightDimmer.h>

	#include <adri_espwebserver.h>
	#include <ALS_espwebserver.h>	

	#include "network\wifi.h"

	#if ADRIIOT_TFT==ADRIIOT_TFTILI9341
		#include "tft_lib.h"
		#include "ui/tft_ui.h"
		#include "meteo/meteo.h"
		#include "ui/screen/icons.h"
		#include "ui/ui_colors.h"
	#endif	