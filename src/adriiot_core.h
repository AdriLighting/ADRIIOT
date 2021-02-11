	#define DEBUG


	WiFiClient 				PubSubClient_espClient;

	adriiot_domoticz 		* adriiot_domoticz_ptr = nullptr;

	moduleClass 			* moduleClassArray[MAX_MODULE];

	relayManagment			adriiot_relayManagement;
	dht22Managment			adriiot_dht22Management;
	DS18B20Managment		adriiot_ds18b20Management;
	soilmoistureManagment	adriiot_soilmoistureManagment;
	lightDimmerManagment	adriiot_lightDimmerManagment;
	RGBneoManagment			adriiot_RGBneoManagment;

	moduleManagment			adriiot_moduleManagemnt;

	adriiot_main 			* adriiot_mainPtr;
	adri_timer 				* timer_test;


	// region ################################################ LOOP

	/**
	 * @brief      lopp
	 * @fn         void adriiot_main::loop()
	 * 
	 * @author     AdriLighting   
	 * @see        https://github.com/AdriLighting/adri_tools_v2
	 * @date       Sat Feb  6 15:51:26 2021
	 */
	void adriiot_main::loop(){

		_tools->loop();
		_wifi->_loop();
		

		if (wifiIsConnect()) {
			_wifi->_connectMod = 0;

			fsprintf("\n[connected timer]\n");

			fsprintf("\t - mqtt begin\n");
			_adriiot_mqtt->connect();

			fsprintf("\t - _webServer begin\n");
			_webServer->serverFS(true); 	
			_webServer->serverInitialize();
			_webServer->serverBegin();
			_webServer->socketBegin();	
			socketServer._whenIsConnected = _whenWebsocketIsConnect;

			fsprintf("\t - ota begin\n");
			if(!_wifi->_otaEnabled)	_wifi->MDSN_begin	();
			else 					arduinoOTA_setup	(_wifi->_hostname);	

			fsprintf("\t - ntp begin\n");
			_wifi->ntpTime_setup();	
			
			adri_toolsv2Ptr_get()->heap_print();
			
			_wifi->_isConnect = true;
		}

		if (_wifi->_isConnect) {

			_adriiot_mqtt->loop();

			_moduleManagment->modulesValue_check();

			_wifi->ntpTime_loop();
			
			if(!_wifi->_otaEnabled)	_wifi->MDSN_loop();
			else					arduinoOTA_loop();	

			_webServer->serverLoop();	

			_webServer->socketLoop();	
		}		

	}	
	// endregion >>>> LOOP

	// region ################################################ SPIFFS PRINT FILES

	int adriiot_print_SPIFFfolder(String path){

		Dir sub_dir = LittleFS.openDir(path);
		
		if (path == "node_modules"){ fsprintf("\t[%s][SKIP]\n", path.c_str()); return 0;}
		else fsprintf("\t[%s]\n", path.c_str());
		int totalsize = 0;
		while (sub_dir.next()) {
			if (sub_dir.isDirectory()) adriiot_print_SPIFFfolder(path + "/" + sub_dir.fileName());
			else {
				String sub_fileInfo = sub_dir.fileName() + (sub_dir.isDirectory() ? " [sub_dir]" : String(" (") + sub_dir.fileSize() + " b)");
				fsprintf("\t\t%s\n", sub_fileInfo.c_str());		
				totalsize += sub_dir.fileSize();
			}
		}
		if (totalsize > 0) fsprintf("\t\t\t[totalsize: %d b]\n", totalsize);	
		return totalsize;
	}
	/**
	 * @brief      focntion for read folder files and sub from spiff
	 *
	 * @fn         void adriiot_print_SPIFF(String path)
	 * 
	 * @author     AdriLighting   
	 * @see        https://github.com/AdriLighting/adri_tools_v2
	 * @date       Sat Feb  6 15:53:34 2021
	 *
	 * @param[in]  path  The path
	 */
	void adriiot_print_SPIFF(String path){
		Dir dir = LittleFS.openDir(path);
		Serial.println("");
		Serial.println( F("List of files at root of filesystem:"));
		int totalsize = 0;
		while (dir.next()) {
			String fileInfo = dir.fileName() + (dir.isDirectory() ? " [DIR]" : String(" (") + dir.fileSize() + " b)");
			if (dir.isDirectory()) {
				int dSize = adriiot_print_SPIFFfolder(dir.fileName());
				totalsize += dSize;
			} else  {
				Serial.println(fileInfo);
				totalsize += dir.fileSize();
			}
		}
		fsprintf("\n[totalsize: %d b]\n", totalsize);
		Serial.println();
	}	
	// endregion >>>> SPIFFS PRINT FILES

	// region ################################################ MAIN

	adriiot_main* adriiot_main_ptrGet(){
		return adriiot_mainPtr;
	}

	/**
	 * @brief      attribue  the pr "adriiot_mainPtr" to the adriiot_main instance
	 *
	 * @fn         void adriiot_main::adriiot_main_setPtr(adriiot_main * ptr)
	 * 
	 * @author     AdriLighting   
	 * @see        https://github.com/AdriLighting/adri_tools_v2
	 * @date       Sat Feb  6 15:54:35 2021
	 *
	 * @param      ptr   The pointer
	 */
	void adriiot_main::adriiot_main_setPtr(adriiot_main * ptr){
		adriiot_mainPtr = ptr;
	}
	/**
	 * @brief      parser from http/socket request
	 * @fn         void webserver_cmd(String msg){
	 * 
	 * @author     AdriLighting   
	 * @see        https://github.com/AdriLighting/adri_tools_v2
	 * @date       Sat Feb  6 15:55:22 2021
	 * 
	 * @param[in]  msg   The request
	 */
	void webserver_cmd(String msg){
		ADRI_LOGP(false, -1, 2, 2, "%s", msg.c_str());
	}


	/**
	 * @brief      Constructs a new instance of adriiot_main.
	 *
	 * @fn        adriiot_main::adriiot_main
	 * 
	 * @author     AdriLighting   
	 * @see        https://github.com/AdriLighting/adri_tools_v2
	 * @date       Sat Feb  6 15:57:28 2021
	 *
	 * @param[in]  hName        dns name and hostname
	 * @param[in]  adriiotMQTT  activate mqtt
	 * @param[in]  topicin      The topicin
	 * @param[in]  topicout     The topicout
	 * @param[in]  serverIp     The mqtt server ip
	 */
	adriiot_main::adriiot_main(
			const char * hName,
			mMqttPlatforme mqttPlatforme, 
			const char * topicin, 
			const char * topicout , 
			const char * serverIp
		){

		adriiot_mainPtr = this;

		_mqttPlatforme = mqttPlatforme;
		// _isArdiotMQTT = adriiotMQTT;

		if (mqttPlatforme == mp_domoticz) {
			_adriiot_mqtt 		= new adriiot_mqtt(topicin, topicout, serverIp, mqttPlatforme);
			_adriiot_domoticz 	= new adriiot_domoticz();
		}

		fsprintf("\n[adriiot BEGIN]\n");	
		
		LittleFS.begin();

		_relayManagment 		= &adriiot_relayManagement;
		_dht22Managment 		= &adriiot_dht22Management;
		_ds18b20managment 		= &adriiot_ds18b20Management;
		_soilmoistureManagment 	= &adriiot_soilmoistureManagment;
		_lightDimmerManagment 	= &adriiot_lightDimmerManagment;
		_RGBneoManagment 		= &adriiot_RGBneoManagment;

		_moduleManagment 		= &adriiot_moduleManagemnt;

		_tools			= adri_toolsv2Ptr_get();

		_looger 		= new adriToolsLogger(1024);
		_looger->setup();
		
		_wifi 			= new wifiClass(hName);

		int pos = requestReponse_initialize("/httpRequest");
		requestReponse_protocol(pos, 	requestProtocol_socket);
		requestReponse_mod_set(pos, 	requestType_wParam);
		requestReponse_reponseMod(pos, 	requestReponseType_none);
		requestReponse_parseMod(pos, 	requestParseCmd_fromFunc);
		requestReponse_func(pos, 		webserver_cmd);

		_webServer 		= new ALS_espwebserver();

		timer_test 		= new adri_timer(1000,"",true);

	}	
	// endregion >>>> MAIN

	// region ################################################ WIFICONNECT
	void adriiot_main::wifiConnect(String ssid, String psk){
		#ifdef DEBUG
			fsprintf("\n[adriiot WIFI SETUP]\n");	
		#endif

		// #ifdef WIFISPIFF
			wifi_credential_sta_fromSPIFF();
			wifi_credential_set(
				0, 	
				ssid,		
				psk, 	
				"",
				"",
				""
			);
			wifi_credential_sta_toSpiff(); 
			// wifi_credential_sta_print(); 	
			wifiConnect_instance()->connect_set(AWC_SETUP);
			wifiConnect_instance()->connectSSID_set(AWCS_NORMAL);		
			wifiConnect_instance()->savToSpiff();		
		// #endif

		if (!_wifi->_setupFromSpiff()) { 
			_wifi->_setupAp(AWC_SETUP, AWCS_AP);
			_wifi->_connect(AWC_SETUP);
		} else {
			_wifi->_connect(AWC_SETUP);
		}

		// wifi_connect_statu();	
	}
	boolean adriiot_main::wifiIsConnect(){
		
		if (_wifi->_connectMod == 1) {return true;}
		return false;
	}	
	// endregion >>>> WIFICONNECT

	// region ################################################ MQTT
	adriiot_mqtt * adriiot_mqtt_ptr = nullptr;
	adriiot_mqtt::adriiot_mqtt(const char * topicin, const char * topicout, const char * serverIp, mMqttPlatforme mqttPlatforme){
		adriiot_mqtt_ptr 	= this;
		_topicin 			= topicin;
		_topicout 			= topicout;
		_serverIp 			= serverIp;
		_mqttPlatforme 		= mqttPlatforme;
		_client 			= new PubSubClient(PubSubClient_espClient);
		fsprintf("\n[adriiot_mqtt::adriiot_mqtt] %s - %s - %s\n", _topicin, _topicout, _serverIp);
	}
	void adriiot_mqtt::reconnect() {
		while (!_client->connected()) {
				fsprintf("\n[adriiot_mqtt]\n\tconnection in progress\n");
				String clientId = "ESP8266Client-";
				clientId += String(random(0xffff), HEX);
			if (_client->connect(clientId.c_str())) {
				fsprintf("\n[adriiot_mqtt]\n\tconnection success\n");
				_client->subscribe("domoticz/out");
			} else {
				fsprintf("\n[adriiot_mqtt]\n\tconnection failed, rc= %d\n", _client->state());
				delay(5000);
			}
		}
	}
	void adriiot_mqtt::loop(){
		if (!_client->connected()) {
			reconnect();
		}
		_client->loop();
	}
	void adriiot_mqtt::connect() {
		_client->setServer(_serverIp, _serverPort);
		_client->setCallback(callback);

	}
	void adriiot_mqtt::publish(const char* payload) {
		_client->publish(_topicin, payload);	
	}
	void adriiot_mqtt::publish(String jsonStr) {
		char buffer[512];
		sprintf(buffer, "%s", jsonStr.c_str());
		_client->publish(_topicin, buffer);	
	}	

	char adriiot_mqtt_packetBuffer[512]; 
	void adriiot_mqtt::callback(char* topic, byte* payload, unsigned int length) {
		ADRI_LOG(2, -1, 0, "<<<", "");
		adriToolsLogger_ptrGet()->region_start(0);
		ADRI_LOG(2, 0, 2,"","");
		int size = length;
		for (int i = 0; i < size; i++) {
			adriiot_mqtt_packetBuffer[i]=(char)payload[i];
		}
		adriiot_mqtt_packetBuffer[length]=0;
		ADRI_LOGV(2, 2, 1, length, "", "");
		// fsprintf("%s\n", adriiot_mqtt_packetBuffer);
		adriiot_mqtt_ptr->domoticz_parse(adri_toolsv2Ptr_get()->ch_toString(adriiot_mqtt_packetBuffer));
		ADRI_LOG(2, 1, 2,"","");
		adriToolsLogger_ptrGet()->region_end(0);
		ADRI_LOG(2, -1, 0, ">>>", "");	
	}
	void adriiot_mqtt::domoticz_parse(String json){

		ADRI_LOG(3, -2, 0, "----<<<", "");
		ADRI_LOG(3, 0, 2,"","");
		const size_t serializeSize = 512 * 4;	
	    DynamicJsonDocument oject(serializeSize);
	    DeserializationError err = deserializeJson(oject, json);
	    if (err) {
			Serial.print(F("FLASHFS Error parsing settings json file: currentSetting.json"));
	        Serial.println(err.c_str());
	    } else {
			// int c_1 = oject[F("idx")].as<int>();
			// int c_2 = oject[F("nvalue")].as<int>();
			// int c_3 = oject[F("svalue1")].as<int>();
			// ADRI_LOG(3, 2, 1, "%d - %d - %d", c_1, c_2, c_3);
			// adriiot_domoticz_ptr->update_module(c_1, c_2, c_3, 3);
			adriiot_domoticz_ptr->update_module(oject, 3);
	    }   
	    ADRI_LOG(3, 1, 2,"","");
	   	ADRI_LOG(3, -2, 0, "---->>>", "");

	} 

	/*
	StaticJsonDocument<256> doc;
	deserializeJson(doc, input, inputLength);

	int Battery = doc["Battery"]; // 255
	const char* LevelNames = doc["LevelNames"]; // "Off|Level1|Level2|Level3"
	int RSSI = doc["RSSI"]; // 12
	const char* SelectorStyle = doc["SelectorStyle"]; // "0"
	const char* description = doc["description"]; // ""
	const char* dtype = doc["dtype"]; // "Light/Switch"
	const char* hwid = doc["hwid"]; // "4"
	const char* id = doc["id"]; // "00014054"
	int idx = doc["idx"]; // 4
	const char* name = doc["name"]; // "machinne a café"
	int nvalue = doc["nvalue"]; // 0
	const char* stype = doc["stype"]; // "Selector Switch"
	const char* svalue1 = doc["svalue1"]; // "0"
	const char* switchType = doc["switchType"]; // "On/Off"
	int unit = doc["unit"]; // 1
	*/
	// endregion >>>> MQTT
	// 
	// region ################################################ dashboard uodate
	void adriiot_main::socket_send(String msg, int debug){
		ADRI_LOG(debug, 0, 2,"","");
		_webServer->socket_send(msg);
		ADRI_LOG(debug, 1, 2,"","");
	}
	void adriiot_main::mqqt_send(String msg, int debug){
	    unsigned int len = msg.length();
		ADRI_LOG(debug, 0, 2,"%d",len);
		char buffer[len+1];
		fssprintf(buffer, "%s", msg.c_str());
		adriiot_mainPtr->_adriiot_mqtt->publish(buffer);
		ADRI_LOG(debug, 1, 2,"","");
	}
	void adriiot_main::dashboard_webClient_update(String msg, int debug){
		socket_send(msg, debug);	
		mqqt_send(msg, debug);	
	}
	void adriiot_main::dashboard_webClient_update(int pos, int debug){
		String s;
		_moduleManagment->json_domoticz_modulesValue(pos, s, debug);
		mqqt_send(s, debug);
		s= "";
		_moduleManagment->json_modulesValue(pos, s, debug);
		socket_send(s, debug);	
		#if ADRIIOT_TFT==ADRIIOT_TFTILI9341
		adriiot_tft_update(pos);
		#endif
	}	
	void adriiot_main::dashboard_socket_update(int pos, int debug){
		String s;
		_moduleManagment->json_modulesValue(pos, s, debug);
		socket_send(s, debug);	
		#if ADRIIOT_TFT==ADRIIOT_TFTILI9341
		adriiot_tft_update(pos);
		#endif
	}	
	// endregion >>>> dashboard uodate

	// region ################################################ logger
			
	// endregion >>>> logger