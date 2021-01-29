moduleClass::moduleClass(mModule name, mType module_type, relayType relay_type, int pin, String username){
	_nameId = adriot_moduleManagemnt.currentCnt();
	_name 	= username;
	_mName 	= name;	
	_mType 	= module_type;	
	_rType 	= relay_type;	
	_pin 	= pin;

	create();
}
moduleClass::moduleClass(mModule mName, mType moType, relayType rType, sensorType sType, int pin, String username){
	_nameId = adriot_moduleManagemnt.currentCnt();
	_name 	= username;
	_mName 	= mName;	
	_mType 	= moType;	
	_rType 	= rType;	
	_sType 	= sType;	
	_pin 	= pin;

	create();
}
void moduleClass::print(){
	float 		temperature;
	float 		temperatureIndice;
	int 		value;
	boolean 	state;
	String 		sName;
	String 		sType;
	String 		seType;
	String 		relayType;

	adriot_moduleManagemnt.mNameToString(_mName, sName);
	adriot_moduleManagemnt.mTypeToString(_mType, sType);
	adriot_moduleManagemnt.sTypeToString(_sType, seType);
	adriot_moduleManagemnt.rTypeToString(_rType, relayType);

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
	    		case st_solMoisture:
			    	adriot_mainPtr->_solmoistureManagment->module(_id)->read(value);
			    	valueMod = 1;
	    		break;
	    		case st_dht22:
			    	adriot_mainPtr->_dht22Managment->module(_id)->read_temperature(temperature, state);
			    	adriot_mainPtr->_dht22Managment->module(_id)->read_temperatureIndice(temperatureIndice, state);
			    	valueMod = 2;
	    		break;	    		
	    		default:
	    			break;	    		
	    	}
	    break;
	    case mt_relay:
	    	switch (_rType) {
	    		case rt_light:
					adriot_mainPtr->_relayManagment->module(_id)->getStatus(state);
	    		break;
	    		case rt_plug:
					adriot_mainPtr->_relayManagment->module(_id)->getStatus(state);
	    		break;
	    		default:
	    			break;

	    	}
	    break;
	    case mt_lightDimmer:
			adriot_mainPtr->_relayManagment->module(_id)->getStatus(state);
	    break; 
	    case mt_lightRGB:
			adriot_mainPtr->_relayManagment->module(_id)->getStatus(state);
	    break;	   
	    case mt_lightRGBW:
			adriot_mainPtr->_relayManagment->module(_id)->getStatus(state);
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
void moduleClass::username_get(String & ret){ret = _name;}

void moduleClass::create(){
	switch (_mType) {
	    case mt_sensor:
	    	switch (_sType) {
	    		case st_solMoisture:
					adriot_mainPtr->_solmoistureManagment->create(false, _pin, _id);    		
	    		break;
	    		case st_dht22:
					adriot_mainPtr->_dht22Managment->create(_pin, _id);		    		
	    		break;	    		
	    		default:
	    			break;	    		
	    	}
	    break;
	    case mt_relay:
	    	adriot_mainPtr->_relayManagment->create(_pin, _id);
	    break;
	    case mt_lightDimmer:
	    	adriot_mainPtr->_relayManagment->create(_pin, _id);
	    break; 
	    case mt_lightRGB:
	    	adriot_mainPtr->_relayManagment->create(_pin, _id);
	    break;	   
	    case mt_lightRGBW:
	    	adriot_mainPtr->_relayManagment->create(_pin, _id);
	    break;		         	
	    default:
	    	break;
	}		
}

void moduleClass::id_get(int & ret) 			{ret = _id;}
void moduleClass::nameId_get(int & ret)			{ret = _nameId;}
void moduleClass::sType_get(sensorType & ret) 	{ret = _sType;}
void moduleClass::mType_get(mType & ret) 		{ret = _mType;}
void moduleClass::json_domoticz_value(JsonObject & object){
	// JsonObject object = root.createNestedObject(String(_nameId));
	object[F("idx")] = _mqttidx;
	switch (_mType) {
	    case mt_sensor:
	    	switch (_sType) {
	    		case st_solMoisture:
	    			// object[F("command")] = F("udevice");
					adriot_mainPtr->_solmoistureManagment->module(_id)->domoticzJson(object);	
	    		break;
	    		case st_dht22:
	    			// object[F("command")] = F("udevice");
					adriot_mainPtr->_dht22Managment->module(_id)->domoticzJson(object);	    		
	    		break;	    		
	    		default:
	    			break;	    		
	    	}
	    break;
	    case mt_relay:
	    	switch (_rType) {
	    		case rt_plug:
	    			object[F("command")] = F("switchlight");
					adriot_mainPtr->_relayManagment->module(_id)->domoticzJson(object);	
	    		break;
	    		case rt_light:
	    			object[F("command")] = F("switchlight");
					adriot_mainPtr->_relayManagment->module(_id)->domoticzJson(object);	    		
	    		break;	    		
	    		default:
	    			break;	    		
	    	}	    
	    break;
	    case mt_lightDimmer:
	    	object[F("command")] = F("switchlight");
	    	adriot_mainPtr->_relayManagment->module(_id)->domoticzJson(object);
	    break; 
	    case mt_lightRGB:
	    	adriot_mainPtr->_relayManagment->module(_id)->domoticzJson(object);
	    break;	   
	    case mt_lightRGBW:
	    	adriot_mainPtr->_relayManagment->module(_id)->domoticzJson(object);
	    break;		         	
	    default:
	    	break;
	}		
}
void moduleClass::json_value(JsonObject & root){
	JsonObject object = root.createNestedObject(String(_nameId));
	switch (_mType) {
	    case mt_sensor:
	    	switch (_sType) {
	    		case st_solMoisture:

					adriot_mainPtr->_solmoistureManagment->module(_id)->json(object);	
	    		break;
	    		case st_dht22:
					 adriot_mainPtr->_dht22Managment->module(_id)->json(object);	    		
	    		break;	    		
	    		default:
	    			break;	    		
	    	}
	    break;
	    case mt_relay:
	    	adriot_mainPtr->_relayManagment->module(_id)->json(object);
	    break;
	    case mt_lightDimmer:
	    	adriot_mainPtr->_relayManagment->module(_id)->json(object);
	    break; 
	    case mt_lightRGB:
	    	adriot_mainPtr->_relayManagment->module(_id)->json(object);
	    break;	   
	    case mt_lightRGBW:
	    	adriot_mainPtr->_relayManagment->module(_id)->json(object);
	    break;		         	
	    default:
	    	break;
	}		
}
void moduleClass::json(JsonObject & root){
	JsonObject object = root.createNestedObject(String(_nameId));

	object[F("1")] 	= _name;
	object[F("2")] 	= _mName;
	object[F("3")] 	= _mType;
	object[F("4")] 	= _rType;
	object[F("5")] 	= _sType;
	object[F("6")] 	= _pin;
	object[F("7")] 	= _id;
}
