// region ################################################ CONSTRUCTOR
moduleClass::moduleClass(mModule mName, mType moType, relayType rType, sensorType sType, int pin, int numLeds, String username){
	_nameId 	= adriiot_moduleManagemnt.currentCnt();
	_name 		= username;
	_mName 		= mName;	
	_mType 		= moType;	
	_rType 		= rType;	
	_sType 		= sType;	
	_pin 		= pin;
	_numLeds	= numLeds;

	create();
}	
moduleClass::moduleClass(mModule mName, mType moType, relayType rType, sensorType sType, int pin, String username){
	_nameId = adriiot_moduleManagemnt.currentCnt();
	_name 	= username;
	_mName 	= mName;	
	_mType 	= moType;	
	_rType 	= rType;	
	_sType 	= sType;	
	_pin 	= pin;

	create();
}	
// endregion >>>> CONSTRUCTOR

// region ################################################ PRINT TO SERIAL
void moduleClass::print(){
	float 		temperature;
	float 		temperatureIndice;
	int 		value;
	boolean 	state;
	String 		sName;
	String 		sType;
	String 		seType;
	String 		relayType;

	adriiot_moduleManagemnt.mNameToString(_mName, sName);
	adriiot_moduleManagemnt.mTypeToString(_mType, sType);
	adriiot_moduleManagemnt.sTypeToString(_sType, seType);
	adriiot_moduleManagemnt.rTypeToString(_rType, relayType);

	fsprintf("[id: %4d][pin: %4d][name: %-15s][module: %15s][type: %15s]",
		_id,
		_pin,
		_name.c_str(),
		sName.c_str(),
		sType.c_str()
	);	

	int valueMod = 0;

	switch (_mType) {

	    case mt_sensor:
	    	switch (_sType) {
	    		case st_soilmoisture:
			    	adriiot_mainPtr->_soilmoistureManagment->module(_id)->read(value);
			    	valueMod = 1;
	    		break;
	    		case st_dht22:
			    	adriiot_mainPtr->_dht22Managment->module(_id)->read_temperature(temperature, state);
			    	adriiot_mainPtr->_dht22Managment->module(_id)->read_temperatureIndice(temperatureIndice, state);
			    	valueMod = 2;
	    		break;
	    		case st_ds18b20:
			    	adriiot_mainPtr->_ds18b20managment->module(_id)->read_temperature(temperature, state);
			    	valueMod = 2;
	    		break;	    			    		
	    		default:
	    			break;	    		
	    	}
	    break;
	    case mt_relay:
	    	switch (_rType) {
	    		case rt_light:
					adriiot_mainPtr->_relayManagment->module(_id)->getStatus(state);
	    		break;
	    		case rt_plug:
					adriiot_mainPtr->_relayManagment->module(_id)->getStatus(state);
	    		break;
	    		default:
	    			break;

	    	}
	    break;
	    case mt_lightDimmer:
			adriiot_mainPtr->_lightDimmerManagment->module(_id)->getStatus(state);
	    break; 
	    case mt_lightRGB:
			adriiot_mainPtr->_RGBneoManagment->module(_id)->getStatus(state);
	    break;	   
	    case mt_lightRGBW:
			adriiot_mainPtr->_relayManagment->module(_id)->getStatus(state);
	    break;		         	
	    default:
	    	break;
	}	
	switch (valueMod) {
	    case 0:
	      	fsprintf("[relayType: %18s][seType: %15s][statu: %10d]\n", relayType.c_str(), seType.c_str(), state);	
	    break;
	    case 1:
	      	fsprintf("[relayType: %18s][seType: %15s][statu: %10d]\n", relayType.c_str(), seType.c_str(), value);	
	    break;
	    case 2:
	    	fsprintf("[relayType: %18s][seType: %15s][statu: %10.2f]\n", relayType.c_str(), seType.c_str(), temperature);	
	    break;
	    default:
	    	break;
	}
}	
// endregion >>>> PRINT TO SERIAL

// region ################################################ CREATE MODULE
void moduleClass::create(){
	switch (_mType) {
	    case mt_sensor:
	    	switch (_sType) {
	    		case st_soilmoisture:
					adriiot_mainPtr->_soilmoistureManagment->create(false, _pin, _id);    		
	    		break;
	    		case st_dht22:
					adriiot_mainPtr->_dht22Managment->create(_pin, _id);		    		
	    		break;	
	    		case st_ds18b20:
					adriiot_mainPtr->_ds18b20managment->create(_pin, _id);		    		
	    		break;		    		    		
	    		default:
	    			break;	    		
	    	}
	    break;
	    case mt_relay:
	    	adriiot_mainPtr->_relayManagment->create(_pin, _id);
	    break;
	    case mt_lightDimmer:
	    	adriiot_mainPtr->_lightDimmerManagment->create(_pin, _id);
	    break; 
	    case mt_lightRGB:
	    	adriiot_mainPtr->_RGBneoManagment->create(_id, _numLeds, _pin, 0);
	    break;	   
	    case mt_lightRGBW:
	    	adriiot_mainPtr->_relayManagment->create(_pin, _id);
	    break;		         	
	    default:
	    	break;
	}		
}	
// endregion >>>> CREATE MODULE

// region ################################################ GET ID
void moduleClass::username_get(String & ret) 	{ret = _name;}
void moduleClass::id_get(int & ret) 			{ret = _id;}
void moduleClass::nameId_get(int & ret)			{ret = _nameId;}
// endregion >>>> GET ID

// region ################################################ GET MOD
void moduleClass::sType_get(sensorType & ret) 	{ret = _sType;}
void moduleClass::mType_get(mType & ret) 		{ret = _mType;}	
// endregion >>>> GET MOD

// region ################################################ GET MODULE VALUE AS JSON  - DOMOTICZ
void moduleClass::json_domoticz_value(JsonObject & object){
	// JsonObject object = root.createNestedObject(String(_nameId));
	object[F("idx")] = _mqttidx;
	switch (_mType) {
	    case mt_sensor:
	    	switch (_sType) {
	    		case st_soilmoisture:
	    			// object[F("command")] = F("udevice");
					adriiot_mainPtr->_soilmoistureManagment->module(_id)->domoticzJson(object);	
	    		break;
	    		case st_dht22:
	    			// object[F("command")] = F("udevice");
					adriiot_mainPtr->_dht22Managment->module(_id)->domoticzJson(object);	    		
	    		break;	    
	    		case st_ds18b20:
	    			// object[F("command")] = F("udevice");
					adriiot_mainPtr->_ds18b20managment->module(_id)->domoticzJson(object);	    		
	    		break;	  	    				
	    		default:
	    			break;	    		
	    	}
	    break;
	    case mt_relay:
	    	switch (_rType) {
	    		case rt_plug:
	    			object[F("command")] = F("switchlight");
					adriiot_mainPtr->_relayManagment->module(_id)->domoticzJson(object);	
	    		break;
	    		case rt_light:
	    			object[F("command")] = F("switchlight");
					adriiot_mainPtr->_relayManagment->module(_id)->domoticzJson(object);	    		
	    		break;	    		
	    		default:
	    			break;	    		
	    	}	    
	    break;
	    case mt_lightDimmer:
			adriiot_mainPtr->_lightDimmerManagment->module(_id)->domoticzJson(object);
	    break; 
	    case mt_lightRGB:
			adriiot_mainPtr->_RGBneoManagment->module(_id)->domoticzJson(object);
	    break;	   
	    case mt_lightRGBW:
			adriiot_mainPtr->_relayManagment->module(_id)->domoticzJson(object);
	    break;		         	
	    default:
	    	break;
	}		
}	
// endregion >>>> GET MODULE VALUE AS JSON  - DOMOTICZ

// region ################################################ GET MODULE VALUE AS JSON - SOCKET
void moduleClass::json_value(JsonObject & root){
	JsonObject object = root.createNestedObject(String(_nameId));
	switch (_mType) {
	    case mt_sensor:
	    	switch (_sType) {
	    		case st_soilmoisture:

					adriiot_mainPtr->_soilmoistureManagment->module(_id)->json(object);	
	    		break;
	    		case st_dht22:
					 adriiot_mainPtr->_dht22Managment->module(_id)->json(object);	    		
	    		break;	
	    		case st_ds18b20:
					 adriiot_mainPtr->_ds18b20managment->module(_id)->json(object);	    		
	    		break;	    		    		
	    		default:
	    			break;	    		
	    	}
	    break;
	    case mt_relay:
	    	adriiot_mainPtr->_relayManagment->module(_id)->json(object);
	    break;
	    case mt_lightDimmer:
	    	adriiot_mainPtr->_lightDimmerManagment->module(_id)->json(object);
	    break; 
	    case mt_lightRGB:
	    	adriiot_mainPtr->_RGBneoManagment->module(_id)->json(object);
	    break;	   
	    case mt_lightRGBW:
	    	adriiot_mainPtr->_relayManagment->module(_id)->json(object);
	    break;		         	
	    default:
	    	break;
	}		
}	
// endregion >>>> GET MODULE VALUE AS JSON- MODULE

// region ################################################  GET MODULE INFOS AS JSON  - SOCKET
void moduleClass::json(JsonObject & root){
	JsonObject object = root.createNestedObject(String(_nameId));
	object[F("1")] 	= _name;
	object[F("2")] 	= _mName;
	object[F("3")] 	= _mType;
	object[F("4")] 	= _rType;
	object[F("5")] 	= _sType;
	object[F("6")] 	= _pin;
	object[F("7")] 	= _id;
	object[F("8")] 	= _numLeds;
}	
// endregion >>>>  GET MODULE INFOS AS JSON  - SOCKET
