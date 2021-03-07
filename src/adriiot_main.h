

// #ifndef adriiot_MAIN_H
// #define adriiot_MAIN_H



	#define MAX_MODULE 10

	void adriiot_print_SPIFF(String path = "");

	extern adri_socket socketServer;

	void _whenWebsocketIsConnect();



// region ################################################ mod
		/** @enum mapper::mModule
		 *  \author Adrilignthing
		 *  @brief 	module mod 
		 */
		enum mModule{
			mn_sensor, /** sensor module */
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
		enum mRelayType{
			rt_light,
			rt_plug,
			rt_waterPump,
			rt_unk
		};
		/**
		 * @brief      { enum_description }
		 */
		enum mSensorType{
			st_soilmoisture,
			st_dht22,
			st_ds18b20,
			st_acs712,
			st_unk
		};	

		enum mMqttPlatforme
		{
			mp_domoticz,
			mp_none

		};	

		enum mWaterPumpSatu
		{
			wps_auto, wps_manu, wps_off
		};			
// endregion >>>> mod	

// region ################################################ moduleClass
	class moduleClass
	{
		private:
			String 		_name 		= "myModule";
			int 		_nameId		= -1;
			mModule		_mName 		= mn_unk;
			mType 		_mType 		= mt_unk;
			mRelayType	_rType 		= rt_unk;
			mSensorType	_sType 		= st_unk;
			int 		_pin 		= -1;
			int 		_id 		= -1;
		public:
			int 		_mqttidx	= -1;
			int 		_numLeds	= -1;

			mWaterPumpSatu _waterPumpSatu = wps_auto;

			moduleClass(mModule mName, mType moType, mRelayType rType, mSensorType sType, int pin, int numLeds, String username);
			moduleClass(mModule name, mType module_type, mRelayType relay_type, mSensorType sType, int pin, String username);
			// ~adriiot_module();

			void id_get(int & ret);
			void nameId_get(int & ret);
			void sType_get(mSensorType & ret);
			void mType_get(mType & ret);
			void rType_get(mRelayType & ret);
			void mName_get(mModule & ret);
			void username_get(String & ret);
			void create();
			void print();
			void json_value(JsonObject & root);
			void json_domoticz_value(JsonObject & root);
			void json(JsonObject & root);
	};	
// endregion >>>> moduleClass

// region ################################################ moduleManagment_spiff
	class moduleManagment_spiff
	{
		String mListeFileName = "/spiff_mListe.txt";
		String mListeArray[10];
	public:
		moduleManagment_spiff();
		~moduleManagment_spiff(){};
		void create(mModule mName, mType moType, mRelayType rType, mSensorType sType, int pin, String username, int idx, String & ret);
		void add(int pos, String value);
		boolean toSpiff();
		void load(String file);
	};	
// endregion >>>> moduleManagment_spiff

// region ################################################ moduleManagment
	class moduleManagment
	{
		public:
			int _pos = 0;



			moduleManagment();
			~moduleManagment(){};

			boolean modulesValue_check_skip = false;
			String modulesValue[MAX_MODULE];

			void modulesValue_check(boolean force = false);
			adri_timer * modulesValue_checkTimer;

			void mqqt_setidx(int idx);


			void create(mModule mName, mType moType, mRelayType rType, mSensorType sType, int pin, int numLeds, String username, int idx = -1);
			void create(mModule mName, mType moType, mRelayType rType, mSensorType sType, int pin, String username, int idx = -1);
			void create_lightRGB		(int pin, int numLeds, String username, int idx = -1);
			void create_lightDimmer		(int pin, String username, int idx = -1);
			void create_temperature		(int pin, String username, int idx = -1);
			void create_temperatureEx	(int pin, String username, int idx = -1);
			void create_plug 			(int pin, String username, int idx = -1);
			void create_plugWater		(int pin, String username, int idx = -1);
			void create_light 			(int pin, String username, int idx = -1);
			void create_light 			(mType type, int pin, String username, int idx = -1);
			void create_sensor			(mSensorType type, int pin, String username, int idx = -1);


			moduleClass * module(int pos);

			void toggleRelay(unsigned long delay);

			void print();

			int currentCnt();


			void json_modules(String & ret, int debug = -1);
			void jsonObject_modules(JsonObject & root);

			void json_modulesValue(String & ret, int debug = -1);
			void jsonObject_modulesValue(JsonObject & root);

			void json_modulesValue(int pos, String & ret, int debug = -1);
			void jsonObject_modulesValue(int pos, JsonObject & root);

			void json_modulesValue(String pos, String & ret, int debug = -1);
			void jsonObject_modulesValue(String pos, JsonObject & root);

			void json_modulesValueList(String & ret, int debug = -1);
	
			void json_domoticz_modulesValue(int pos, String & ret, int debug = -1);
			void jsonObject_domoticz_modulesValue(int pos, JsonObject & root);

			void json_domoticz_modulesValue(String & ret, int debug = -1);
			void jsonObject_domoticz_modulesValue(JsonObject & root);
			
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
			void rTypeToString(mRelayType value, String & result); 	
			void sTypeToString(mSensorType value, String & result); 	

			void domoticz_modules_upadte(int idx, int nValue, int sValue);

	};	
// endregion >>>> moduleManagment

// region ################################################ adriiot_domoticz
	class adriiot_domoticz
	{
	private:
	public:
		adriiot_domoticz();
		void update_module(DynamicJsonDocument json, int debug);
	};	
// endregion >>>> adriiot_domoticz

// region ################################################ adriiot_mqtt
	class adriiot_mqtt 
	{
		const char 		* _topicin		= "in";
		const char 		* _topicout  	= "out";
		const char 		* _serverIp  	= "out";
		PubSubClient 	* 	_client;
		uint16_t		_serverPort 	= 1883;
		mMqttPlatforme	_mqttPlatforme 	= mp_none;
	public:
		adriiot_mqtt(const char * topicin, const char * topicout, const char * serverIp, mMqttPlatforme mqttPlatforme);
		~adriiot_mqtt(){};
		static void callback(char* topic, byte* payload, unsigned int length);
		void domoticz_parse(String json);
		void connect();
		void reconnect();
		void loop();
		void publish(const char* payload);
		void publish(String jsonStr);
	};
// endregion >>>> adriiot_mqtt

// region ################################################ adriiot_main
	class adriiot_main
	{

		public:
			relayManagment 			* _relayManagment;
			dht22Managment 			* _dht22Managment;
			moduleManagment 		* _moduleManagment;
			soilmoistureManagment 	* _soilmoistureManagment;
			DS18B20Managment 		* _ds18b20managment;
			lightDimmerManagment	* _lightDimmerManagment;
			RGBneoManagment			* _RGBneoManagment;

			wifiClass 				* _wifi;
			ALS_espwebserver 		* _webServer 		= nullptr;
			adriiot_mqtt 			* _adriiot_mqtt		= nullptr;
			adriiot_domoticz		* _adriiot_domoticz	= nullptr;

			adriToolsLogger 		* _looger;
			adri_toolsV2 			* _tools;

			mMqttPlatforme			_mqttPlatforme = mp_none;

			adriiot_main(
					const char * hName,
					mMqttPlatforme mqttPlatforme = mp_none, 
					const char * topicin = "", 
					const char * topicout = "", 
					const char * serverIp = ""
				);
			~adriiot_main(){};

			void adriiot_main_setPtr(adriiot_main * ptr);

			void 	wifiConnect(String ssid, String psk);
			boolean wifiIsConnect();

			void 	socket_send(String msg, int debug);
			void 	mqqt_send(String msg, int debug);
			void 	dashboard_webClient_update(String msg, int debug);
			void 	dashboard_webClient_update(int pos, int debug);
			void 	dashboard_socket_update(int pos, int debug);

			
			void loop();

		
	};

// endregion >>>> 	

// region ################################################ TFT HOME
#if ADRIIOT_TFT==ADRIIOT_TFTILI9341
	class adriiot_tft_home  {
		private:
			
			int _pos = 0;
			adriTFTUI_txtBox * _txtBox[10];
			adriTFTUI_txtBox * _txtBoxValue[10];
			int _aX[10];
			int _aY[10];
			int _sX = 20;
			int _sY = 120;
		public:
			adriiot_tft_home() ;
			void init();
			void update(int pos);
	};	
	adriiot_tft_home * adriiot_tft_home_ptr;
	adriiot_tft_home * adriiot_tft_home_ptrGet(){
		return adriiot_tft_home_ptr;
	}	
#endif
// endregion >>>> TFT HOME
// region ################################################ TFT DEVICE
#if ADRIIOT_TFT==ADRIIOT_TFTILI9341
	class adriiot_tft_device  {
		private:
			
			int _pos = 1;
			adriTFTUI_txtBox * _txtBox[10];
			adriTFTUI_txtBox * _txtBoxValue[10];
			int _aX[10];
			int _aY[10];
			int _sX = 15;
			int _sY = 12;
			int device_pos;
			adri_timer * _timer;
		public:
			boolean _init[10];
			
			adriiot_tft_device() ;
			void init();
			void update(int pos);
	};	
	adriiot_tft_device * adriiot_tft_device_ptr;
	adriiot_tft_device * adriiot_tft_device_ptrGet(){
		return adriiot_tft_device_ptr;
	}	
#endif
// endregion >>>> TFT DEVICE
void adriiot_tft_update(int pos) {
	#if ADRIIOT_TFT==ADRIIOT_TFTILI9341
		adriiot_tft_device_ptr->update(pos);
		adriiot_tft_home_ptr->update(pos);
	#endif
}


	// ############################################

	#include "adriiot_core.h"

	// ############################################

	#include "adriiot_modulemanagment.h"

	// ############################################

	#include "adriiot_moduleclass.h"

	// ############################################
#if ADRIIOT_TFT==ADRIIOT_TFTILI9341
	#include "adriiot_tft.h"
#endif
	// ############################################



