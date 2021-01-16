#ifndef WIFI_H
	#define WIFI_H
	#include <adri_wifiConnect.h>

	class wifiClass
	{

		wifiConnect 			* myWifi;	// PTR pour unr instance statique "wifiConnect"
		wifi_credential_ap		* myWifiAp;	// PTR pour unr instance statique "wifi_credential_ap"

		const char				* hostname = "MY_WIFI"; 	// AP AND DNS HOSTNAME 
															
												// 	AWC_LOOP; 		WIFI CONNECT STARTUP WITH STATIC 
												// 	AWC_SETUP; 		WIFI CONNECT STARTUP WITH STATIC 
		WIFICONNECT_MOD			connectMod 	= 	AWC_SETUP;	

												// 	AWCS_MULTI;		STA CONNECT WITH MULTIPLE SSID
												// 	AWCS_NORMAL;	STA CONNECT WITH THE SELECTED SSID
		WIFICONNECTSSID_MOD 	SSIDMod 		= 	AWCS_NORMAL;	

		boolean 				OTA 			= false; 	// ENABLED OTA
			
		int 					connectDone	= 0;			// WIFI CONNECT LOOP POSTION 

	public:
		wifiClass();
		~wifiClass();
		
	};

#endif // WIFI_H
