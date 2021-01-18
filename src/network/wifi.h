#ifndef WIFI_H
	#define WIFI_H

	#include <adri_wifiConnect.h>
	#include <adri_tools.h>
	#include <adri_timer.h>
	#include <adri_espwebserver_tools.h>
	#include <adri_timeNtp.h>

	enum mod_wifiConnect_error
	{
		mwce_none, mwce_setup
	};

	class wifiClass : public wifiConnect
	{
		const char 				* _hostname 			= "HELLOWORLD";

		mod_wifiConnect_error 	_error_setup 			= mwce_none;

		adri_timer 				* _checkConnected_timer = nullptr;

		int 					_connectMod_setTo		= 0;
		adri_timer 				* _connectModTimer		= nullptr;

		adri_timeNtp			* _ntpTime;

	public:

		boolean 				_isConnect 		= false;
		int 					_connectMod		= 0;
		int						_eventModStart	= 0;
		boolean					_otaEnabled 	= true;

		wifiClass(const char * value);
		~wifiClass(){fsprintf("\n[wifiClass delete();]\n");};

		mod_wifiConnect_error error_get();
		void 	_connectMod_set 	(int value);
		int 	_connectMod_get 	();	
		void 	_hostname_get 		(String & ret);	
		void 	_otaEnabled_set 	(boolean ret);			
		boolean _setupFromSpiff		();
		boolean _setup 				(WIFICONNECT_MOD cMod = AWC_SETUP, WIFICONNECTSSID_MOD sMod = AWCS_NORMAL);
		boolean _setupAp			(WIFICONNECT_MOD cMod = AWC_SETUP, WIFICONNECTSSID_MOD sMod = AWCS_NORMAL);
		boolean _connect 			(WIFICONNECT_MOD cMod);
		boolean _connectFromSpiff	();
		void 	_loop 				();

		void 	_checkConnected_start 	();
		boolean _checkConnected 		(int & result);
		void 	_checkConnected_loop 	();

		void 	ntpTime_setup 		();
		void 	ntpTime_loop 		();	
		void 	ntpTime_getTime 	(String & ret);
		String 	ntpTime_toString 	(time_t t);
		boolean ntpTime_isSet 		();		

	};

	wifiClass * wifiClassPtr_get();

#endif // WIFI_H


/*
	class wifiClass
	{

		wifiConnect 			* myWifi;	// PTR pour unr instance statique "wifiConnect"
		wifi_credential_ap		* myWifiAp;	// PTR pour unr instance statique "wifi_credential_ap"

		const char				* _hostname = "MY_WIFI"; 	// AP AND DNS HOSTNAME 
			
		int 					_connectDone	= 0;			// WIFI CONNECT LOOP POSTION 

	public:

												// 	AWC_LOOP; 		WIFI CONNECT STARTUP WITH STATIC 
												// 	AWC_SETUP; 		WIFI CONNECT STARTUP WITH STATIC 
		WIFICONNECT_MOD			_connectMod 	= 	AWC_SETUP;	

												// 	AWCS_MULTI;		STA CONNECT WITH MULTIPLE SSID
												// 	AWCS_NORMAL;	STA CONNECT WITH THE SELECTED SSID
		WIFICONNECTSSID_MOD 	_SSIDMod 		= 	AWCS_NORMAL;	

		boolean 				_OTA 			= false; 	// ENABLED OTA

		wifiClass();
		~wifiClass(){};
		void setup(String ssid, String pswd, const char * host);
		void connect();
		void loop();
	};
*/