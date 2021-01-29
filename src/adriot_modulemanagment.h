moduleManagment::moduleManagment(){
	modulesValue_checkTimer = new adri_timer(500, "", true);
}

int moduleManagment::currentCnt(){return _pos;}
void moduleManagment::mqqt_setidx(int idx){;}

void moduleManagment::create_lightDimmer(int pin, String username, int idx){create(mn_light, 	mt_lightDimmer,	rt_unk, 	st_unk, 		pin, username, idx);}
void moduleManagment::create_temperature(int pin, String username, int idx){create(mn_sensor, 	mt_sensor,		rt_unk, 	st_dht22, 		pin, username, idx);}
void moduleManagment::create_plug 		(int pin, String username, int idx){create(mn_relay, 	mt_relay,		rt_plug, 	st_unk, 		pin, username, idx);}
void moduleManagment::create_light 		(int pin, String username, int idx){create(mn_relay, 	mt_relay, 		rt_light, 	st_unk, 		pin, username, idx);}
void moduleManagment::create_light 		(mType type, int pin, String username, int idx){	
																			create(mn_light, 	type,			rt_unk, 	st_unk, 		pin, username, idx);}
void moduleManagment::create_sensor		(sensorType type, int pin, String username, int idx){
																			create(mn_sensor, 	mt_sensor, 		rt_unk, 	type, 			pin, username, idx);}

void moduleManagment::create(mModule mName, mType moType, relayType rType, sensorType sType, int pin, String username, int idx){
	moduleClassArray[_pos] = new moduleClass(mName, moType, rType, sType, pin, username);
	moduleClassArray[_pos]->_mqttidx = idx;
	_pos++;
}	
void moduleManagment::getByName(String search, int & ret){
	String name = "";
	for (int i = 0; i < _pos; ++i) {
		name = "";
		moduleClassArray[i]->username_get(name);		
		if (search == name) {ret = i; break;}
	}
}
void moduleManagment::getIdByName(String search, int & ret){
	String name = "";
	for (int i = 0; i < _pos; ++i) {
		name = "";
		moduleClassArray[i]->username_get(name);
		if (search == name) {moduleClassArray[i]->id_get(ret); break;}
	}
}
void moduleManagment::getIdByPos(int search, int & ret){
	moduleClassArray[search]->id_get(ret);
}


moduleClass * moduleManagment::module(int pos){
	return moduleClassArray[pos];
}

void moduleManagment::print(){
	fsprintf("\n[moduleManagment::print]\n");
	for (int i = 0; i < _pos; ++i) {
		moduleClassArray[i]->print();
	}	
}

// 	############################ 	SOCKET JSON
// 	###########################################################################
// 	
// 	ALL MODULES LIST + ALL MODULES VALUE
void moduleManagment::json_modulesValueList(String & ret){
	DynamicJsonDocument json(2048);
	JsonObject root = json.to<JsonObject>();	
	JsonObject object = root.createNestedObject("mValues");
	jsonObject_modulesValue(object);
	object = root.createNestedObject("mListe");
	jsonObject_modules(object);
	ret= "";
	serializeJson(json, ret);
	#ifdef DEBUG
		fsprintf("\n[moduleManagment::json_modulesValueList]\n%s\n", ret.c_str());
	#endif
}

// 	ALL MODULES VALUE
void moduleManagment::jsonObject_modulesValue(JsonObject & root){
	float 		t;
	boolean 	state;
	int 		id;
	sensorType	sType;
	for (int i = 0; i < _pos; ++i) {
		moduleClassArray[i]->id_get(id);
		moduleClassArray[i]->sType_get(sType);
		if (sType==st_dht22) {
			adriot_mainPtr->_dht22Managment->module(id)->read_temperature(t, state);
			if (state) moduleClassArray[i]->json_value(root);		
		} else {
			moduleClassArray[i]->json_value(root);	
		}
	}	
}
void moduleManagment::json_modulesValue(String & ret){
	DynamicJsonDocument json(1024);
	JsonObject root = json.to<JsonObject>();	
	JsonObject object = root.createNestedObject("mValues");
	jsonObject_modulesValue(object);
	ret= "";
	serializeJson(json, ret);
	#ifdef DEBUG
		fsprintf("\n[moduleManagment::json_modulesValue]\n%s\n", ret.c_str());
	#endif
}

// MODULE VALUE BY POS
void moduleManagment::jsonObject_modulesValue(int pos, JsonObject & root){
	float 		t;
	boolean 	state;
	int 		id;
	sensorType	sType;
		moduleClassArray[pos]->id_get(id);
		moduleClassArray[pos]->sType_get(sType);
		if (sType==st_dht22) {
			adriot_mainPtr->_dht22Managment->module(id)->read_temperature(t, state);
			if (state) moduleClassArray[pos]->json_value(root);		
		} else {
			moduleClassArray[pos]->json_value(root);
		}

}
void moduleManagment::json_modulesValue(int pos, String & ret, boolean debug){
	const size_t serializeSize = 512 * 2;	
	DynamicJsonDocument json(serializeSize);
	JsonObject root = json.to<JsonObject>();	
	JsonObject object = root.createNestedObject("mValue");
	jsonObject_modulesValue(pos, object);
	ret= "";
	serializeJson(json, ret);
	#ifdef DEBUG
		if (debug) fsprintf("\n[moduleManagment::json_modulesValue]\n%s\n", ret.c_str());
	#endif
}

// MODULE VALUE BY NAME
void moduleManagment::jsonObject_modulesValue(String name, JsonObject & root){	
	int pos = -1;
	getByName(name, pos);
	if (pos == -1) return;
	moduleClassArray[pos]->json_value(root);
}
void moduleManagment::json_modulesValue(String name, String & ret){	
	int pos = -1;
	getByName(name, pos);
	if (pos == -1) return;
	DynamicJsonDocument json(1024);
	JsonObject root = json.to<JsonObject>();	
	JsonObject object = root.createNestedObject("mValue");
	jsonObject_modulesValue(name, object);
	ret= "";
	serializeJson(json, ret);
	#ifdef DEBUG
		fsprintf("\n[moduleManagment::json_modulesValue]\n%s\n", ret.c_str());
	#endif
}

// 
void moduleManagment::jsonObject_modules(JsonObject & root){
	for (int i = 0; i < _pos; ++i) {
		moduleClassArray[i]->json(root);
	}
}
void moduleManagment::json_modules(String & ret){
	const size_t serializeSize = 512 * 2;	
	DynamicJsonDocument json(serializeSize);
	JsonObject root = json.to<JsonObject>();
	JsonObject object = root.createNestedObject("mListe");
	jsonObject_modules(object);
	ret= "";
	serializeJson(json, ret);
	#ifdef DEBUG
		fsprintf("\n[moduleManagment::json_modules]\n%s\n", ret.c_str());
	#endif
}

// 	############################ 	>>> SOCKET JSON END


// 	############################ 	DOMOTICZ JSON
// 	###########################################################################
// 	
// 	ALL MODULES VALUE
void moduleManagment::jsonObject_domoticz_modulesValue(JsonObject & root){
	float 		t;
	boolean 	state;
	int 		id;
	sensorType	sType;
	for (int i = 0; i < _pos; ++i) {
		JsonObject object = root.createNestedObject(String(i));
		moduleClassArray[i]->id_get(id);
		moduleClassArray[i]->sType_get(sType);
		if (sType==st_dht22) {
			adriot_mainPtr->_dht22Managment->module(id)->read_temperature(t, state);
			if (state) moduleClassArray[i]->json_domoticz_value(object);		
		} else {
			moduleClassArray[i]->json_domoticz_value(object);	
		}
	}	
}
void moduleManagment::json_domoticz_modulesValue(String & ret){
	#ifdef DEBUG
		fsprintf("\n[moduleManagment::json_domoticz_modulesValue]\n");
	#endif	
	DynamicJsonDocument json(1024);
	String 		jsonStr;
	float 		t;
	boolean 	state;
	int 		id;
	String 		username;
	char 		buffer[512];
	sensorType	sType;
	for (int i = 0; i < _pos; ++i) {
		
		JsonObject root = json.to<JsonObject>();

		moduleClassArray[i]->id_get(id);
		moduleClassArray[i]->sType_get(sType);
		moduleClassArray[i]->username_get(username);
		if (sType==st_dht22) {
			adriot_mainPtr->_dht22Managment->module(id)->read_temperature(t, state);
			if (state) moduleClassArray[i]->json_domoticz_value(root);		
		} else {
			moduleClassArray[i]->json_domoticz_value(root);	
		}
		jsonStr = "";
		serializeJson(json, jsonStr);
		sprintf(buffer, "%s", jsonStr.c_str());
		PubSubClient_client.publish("domoticz/in", buffer);		
		#ifdef DEBUG
			fsprintf("\t[MQTT][%18s] json: %s\n", username.c_str(), buffer);	
		#endif				
	}


}

// MODULE VALUE BY POS
void moduleManagment::jsonObject_domoticz_modulesValue(int pos, JsonObject & root){
	float 		t;
	boolean 	state;
	int 		id;
	sensorType	sType;
		moduleClassArray[pos]->id_get(id);
		moduleClassArray[pos]->sType_get(sType);
		if (sType==st_dht22) {
			adriot_mainPtr->_dht22Managment->module(id)->read_temperature(t, state);
			if (state) moduleClassArray[pos]->json_domoticz_value(root);		
		} else {
			moduleClassArray[pos]->json_domoticz_value(root);
		}

}
void moduleManagment::json_domoticz_modulesValue(int pos, String & ret, boolean debug){
	const size_t serializeSize = 1024;	
	DynamicJsonDocument json(serializeSize);
	JsonObject root = json.to<JsonObject>();	
	jsonObject_domoticz_modulesValue(pos, root);
	ret= "";
	serializeJson(json, ret);
	#ifdef DEBUG
		if (debug) fsprintf("\n[moduleManagment::json_domoticz_modulesValue]\n%s\n", ret.c_str());
	#endif
}
// 	############################ 	>>> DOMOTICZ JSON END


void moduleManagment::mNameToString(mModule value, String & result){
	switch (value) {
	    case mn_sensor: 		result = "capteur";					break;
	    case mn_relay:			result = "relay"; 					break;
	    case mn_light: 			result = "luminaire"; 				break;	      	
	    default: 				result = ""; 						break;
	}
}
void moduleManagment::mTypeToString(mType value, String & result){
	switch (value) {
	    case mt_sensor:			result = "sensor";			break;
	    case mt_relay: 			result = "relay";			break;
	    case mt_lightDimmer: 	result = "lightDimmer";		break;	      	
	    case mt_lightRGB: 		result = "lightRGB";		break;	      	
	    case mt_lightRGBW: 		result = "lightRGBW";		break;	      	
	    default: 				result = "";				break;
	}
}
void moduleManagment::rTypeToString(relayType value, String & result){
	switch (value) {
	    case rt_light:			result = "luminaire";					break;
	    case rt_plug: 			result = "prise de courrant";			break;
	    default: 				result = "";							break;
	}
}
void moduleManagment::sTypeToString(sensorType value, String & result){
	switch (value) {
	    case st_solMoisture:	result = "solMoisture";	break;
	    case st_dht22:			result = "dht22";	break;
	    default: 				result = "";			break;
	}
}
mModule mModuleArray[] { 
    mn_sensor,
    mn_relay,
    mn_light,
    mn_unk
};
void moduleManagment::jsonObject_mName(JsonObject & object){
    for (int i = mn_sensor; i < mn_unk; ++i) {
    	String value = "";
    	mNameToString( mModuleArray[i], value);
        object[String(i)] = value; 
    }  
}
void moduleManagment::json_mName(String & ret){
	const size_t serializeSize = 512 * 2;	
	DynamicJsonDocument json(serializeSize);
	JsonObject root = json.to<JsonObject>();
	JsonObject object = root.createNestedObject(F("mName"));
	jsonObject_mName(object);
	ret= "";
	serializeJson(json, ret);
	#ifdef DEBUG
		fsprintf("\n[moduleManagment::json_mName]\n%s\n", ret.c_str());
		String v="";
		for (int i = mn_sensor; i < mn_unk; ++i) { 
			mNameToString(mModuleArray[i],  v);
			fsprintf("\t[%15s][%d]\n",v.c_str(),mModuleArray[i]);
		}			
	#endif    
}
mType mTypeArray[] { 
    mt_sensor,
    mt_relay,
    mt_lightDimmer,
    mt_lightRGB,
    mt_lightRGBW,
    mt_unk
};
void moduleManagment::jsonObject_mType(JsonObject & object){
    for (int i = mt_sensor; i < mt_unk; ++i) {
    	String value = "";
    	mTypeToString( mTypeArray[i], value);
        object[String(i)] = value; 
    }  
}
void moduleManagment::json_mType(String & ret){
	const size_t serializeSize = 512 * 2;	
	DynamicJsonDocument json(serializeSize);
	JsonObject root = json.to<JsonObject>();
	JsonObject object = root.createNestedObject(F("mType"));
	jsonObject_mType(object);
	ret= "";
	serializeJson(json, ret);
	#ifdef DEBUG
		fsprintf("\n[moduleManagment::json_mType]\n%s\n", ret.c_str());
		String v="";
		for (int i = mt_sensor; i < mt_unk; ++i) { 
			mTypeToString(mTypeArray[i],  v);
			fsprintf("\t[%15s][%d]\n",v.c_str(),mTypeArray[i]);
		}		
	#endif     
}
relayType rTypeArray[] { 
    rt_light,
    rt_plug,
    rt_unk
};
void moduleManagment::jsonObject_rtype(JsonObject & object){
    for (int i = rt_light; i < rt_unk; ++i) {
    	String value = "";
    	rTypeToString( rTypeArray[i], value);
        object[String(i)] = value; 
    }  
}
void moduleManagment::json_rType(String & ret){
	const size_t serializeSize = 512 * 2;	
	DynamicJsonDocument json(serializeSize);
	JsonObject root = json.to<JsonObject>();
	JsonObject object = root.createNestedObject(F("relayType"));
	jsonObject_rtype(object);
	ret= "";
	serializeJson(json, ret);
	#ifdef DEBUG

		fsprintf("\n[moduleManagment::json_rType]\n%s\n", ret.c_str());
		String v="";
		for (int i = rt_light; i < rt_unk; ++i) { 
			rTypeToString(rTypeArray[i],  v);
			fsprintf("\t[%15s][%d]\n",v.c_str(),rTypeArray[i]);
		}		
	#endif    
}

sensorType sensorTypeArray[] { 
    st_solMoisture,
    st_dht22,
    st_unk
};
void moduleManagment::jsonObject_stype(JsonObject & object){
    for (int i = st_solMoisture; i < st_unk; ++i) {
    	String value = "";
    	sTypeToString( sensorTypeArray[i], value);
        object[String(i)] = value; 
    }  
}
void moduleManagment::json_sType(String & ret){
	const size_t serializeSize = 512 * 2;	
	DynamicJsonDocument json(serializeSize);
	JsonObject root = json.to<JsonObject>();
	JsonObject object = root.createNestedObject(F("sensorType"));
	jsonObject_stype(object);
	ret= "";
	serializeJson(json, ret);
	#ifdef DEBUG

		fsprintf("\n[moduleManagment::json_sType]\n%s\n", ret.c_str());
		String v="";
		for (int i = st_solMoisture; i < st_unk; ++i) { 
			sTypeToString(sensorTypeArray[i],  v);
			fsprintf("\t[%15s][%d]\n",v.c_str(),sensorTypeArray[i]);
		}		
	#endif    
}

// --------------------------------------------

void moduleManagment::toggleRelay(unsigned long delay){
	static boolean state = false;

	if (!timer_test->loop(delay)) return;

	int id = -1;
	for (int i = 0; i < _pos; ++i) {
		moduleClassArray[i]->id_get(id);
		if (state) {
			adriot_mainPtr->_relayManagment->module(id)->open();
		} else {
			adriot_mainPtr->_relayManagment->module(id)->close();
		}
	}
	state = !state;
}

// --------------------------------------------

void moduleManagment::modulesValue_check(){
	const size_t serializeSize = 512 ;	
	int 		id;
	int			nameId;
	String 		s;
	String 		sMqtt;
	String 		n;
	sensorType 	sType;
	mType 		moduleType;
	boolean 	state;

	char 		buffer[512];
	DynamicJsonDocument object(serializeSize);

	if (modulesValue_checkTimer->loop()) {
		for (int i = 0; i < _pos; ++i) {

			moduleClassArray[i]->id_get(id);
			moduleClassArray[i]->username_get(n);
			moduleClassArray[i]->nameId_get(nameId);
			moduleClassArray[i]->sType_get(sType);
			moduleClassArray[i]->mType_get(moduleType);
			json_modulesValue(i, s, false);
			json_domoticz_modulesValue(i, sMqtt, false);

			if ( s == "{\"mValue\":{}}" ) {
				#ifdef DEBUG
					fsprintf("\n[next]\n");	
				#endif
				continue;
			}

			if (moduleType == mt_sensor) {

				if ( modulesValue[i] == "") {
					modulesValue[i] = s;
					#ifdef DEBUG
						fsprintf("\n[%S] value Changed\n\t%s\n", n.c_str(), s.c_str());	
					#endif
					adriot_mainPtr->_webServer->socket_send(s);	
				} else {
				    
				    deserializeJson(object, s);
					float v1 = object[F("mValue")][String(nameId)][F("v1")].as<float>();
					deserializeJson(object,  modulesValue[i]);			
					float v2 = object[F("mValue")][String(nameId)][F("v1")].as<float>();	

					float diff=0;
					if (v1>v2) 	diff = v1-v2;
					else 		diff = v2-v1;

					if (sType==st_solMoisture) {
						if (diff>5 ) {
							modulesValue[i] = s;
							#ifdef DEBUG
								fsprintf("\n[%S] st_solMoisture ar changed\n\t[v1: %.2f - v2: %.2f] %s\n", n.c_str() ,v1, v2, s.c_str());	
							#endif
							adriot_mainPtr->_webServer->socket_send(s);						
						}						
					}
					if (sType==st_dht22) {
						if (diff>=(float)0.2 ) {
							float t;
							adriot_mainPtr->_dht22Managment->module(id)->read_temperature(t, state);
							modulesValue[i] = s;
							#ifdef DEBUG
								fsprintf("\n[%S] st_dht22 ar changed\n\t[state: %d][v1: %.2f - v2: %.2f] %s\n", n.c_str(), state ,v1, v2, s.c_str());	
							#endif	
							adriot_mainPtr->_webServer->socket_send(s);	
							sprintf(buffer, "%s", sMqtt.c_str());
							#ifdef DEBUG
								fsprintf("\t[MQTT] %s\n", buffer);	
							#endif
							PubSubClient_client.publish("domoticz/in", buffer);												
						}						
					}					
				}
			} else {
				if (s != modulesValue[i]) {
					modulesValue[i] = s;
					#ifdef DEBUG
						fsprintf("\n[%S] value Changed\n\t%s\n", n.c_str(), s.c_str());	
					#endif
					adriot_mainPtr->_webServer->socket_send(s);	
					sprintf(buffer, "%s", sMqtt.c_str());
					#ifdef DEBUG
						fsprintf("\t[MQTT] %s\n", buffer);	
					#endif
					PubSubClient_client.publish("domoticz/in", buffer);
				}
			}
		}	
	}
}


// ##################################################################

moduleManagment_spiff::moduleManagment_spiff(){
	for (int i = 0; i < MAX_MODULE; ++i)
	{
		mListeArray[i]="";
	}

    File f=LittleFS.open(mListeFileName,"r");	

    if (!f) {

    }else{

    }
}
void moduleManagment_spiff::create(mModule mName, mType moType, relayType rType, sensorType sType, int pin, String username, int idx, String & ret){
	const size_t serializeSize = 512 * 2;	
	DynamicJsonDocument json(serializeSize);
	JsonObject object = json.to<JsonObject>();
	object[F("1")] 	= username;
	object[F("2")] 	= mName;
	object[F("3")] 	= moType;
	object[F("4")] 	= rType;
	object[F("5")] 	= sType;
	object[F("6")] 	= pin;
	object[F("7")] 	= idx;
	serializeJson(json, ret);
	#ifdef DEBUG
		fsprintf("\n[moduleManagment_spiff::create]\n%s\n", ret.c_str());
	#endif	
}
void moduleManagment_spiff::load(String file){
	const size_t serializeSize = 512 * 2;	
    DynamicJsonDocument oject(serializeSize);
    DeserializationError err = deserializeJson(oject, file);
    if (err) {
    	// #ifdef DEBUG
        	Serial.print(F("FLASHFS Error parsing settings json file: currentSetting.json"));
        // #endif
        Serial.println(err.c_str());
    } else {
		String c_1 = oject[F("1")].as<String>();
		int c_2 = oject[F("2")].as<int>();
		int c_3 = oject[F("3")].as<int>();
		int c_4 = oject[F("4")].as<int>();
		int c_5 = oject[F("5")].as<int>();
		int c_6 = oject[F("6")].as<int>();
		int c_7 = oject[F("7")].as<int>();
		fsprintf("\n[moduleManagment_spiff::load]\n");
		fsprintf("1: %s\n", c_1.c_str());
		adriot_mainPtr->_moduleManagment->create(	
			mModuleArray[c_2], 	
			mTypeArray[c_3], 		
			rTypeArray[c_4], 	
			sensorTypeArray[c_5], 				
			c_6,		
			c_1,
			c_7
		);
    }        
}
void moduleManagment_spiff::add(int pos, String value) {
	mListeArray[pos]=value;
}
boolean moduleManagment_spiff::toSpiff() {
	File f=LittleFS.open(mListeFileName,"r");	
	if (!f) return false;
	for (int i = 0; i < MAX_MODULE; ++i) {
		if(mListeArray[i]!=""){
			f.println(mListeArray[i]);
		}
	}
	return true;
}