#ifndef METEO_h
#define METEO_h 
	#include "../json/htttpget_jsonreader.h"

	void meteo_update(boolean WifiConnected);
	void meteo_update_loop(boolean WifiConnected);

	extern httpGetJsonReaderCurrent weatherbitCurrentClient;
	extern httpGetJsonReaderCurrent OpenWeatherMapClient;

	void downloadResources() ;
	String getMeteoconIcon_3(String iconText);

#endif