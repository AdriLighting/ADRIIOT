// region ################################################ HOME constructor

adriiot_tft_home::adriiot_tft_home(){
	adriiot_tft_home_ptr = this;
	int count = adriiot_main_ptrGet()->_moduleManagment->_pos;
	for (int i = 0; i < count; ++i)
	{
		_txtBox[i] = new adriTFTUI_txtBox(&tft, u8g2);
		_txtBox[i]->textColor(ILI9341_WHITE, _color_home_1_bgClock);
		_txtBox[i]->u8g2_mod(1);
		_txtBox[i]->u8g2_font(font_default);
		_txtBox[i]->text("");
		_txtBox[i]->u8g2_setup();

		_txtBoxValue[i] = new adriTFTUI_txtBox(&tft, u8g2);
		_txtBoxValue[i]->textColor(ui.color565(255, 119, 0), _color_home_1_bgClock);
		_txtBoxValue[i]->u8g2_mod(1);
		_txtBoxValue[i]->u8g2_font(font_default);
		_txtBoxValue[i]->text("");
		_txtBoxValue[i]->u8g2_setup();				
	}	
	init();
}		
// endregion >>>> HOME constructor




template<typename T> void GetVal(String & ret, T nvalue) {
	ret = nvalue;
}

// region ################################################ HOME INITIIALISATION
void adriiot_tft_home::init(){
	int count = adriiot_main_ptrGet()->_moduleManagment->_pos;
	int cnt = 0;
	int stY = _sY;
	int stX = _sX;
	int difX = 140;
	int difY = 60;

	for (int i = 0; i < count; ++i)
	{	
		if (i>3) break;

		_aX[i] = stX;
		_aY[i] = stY;
		_txtBoxValue[i]->textPos(_aX[i] + 45, _aY[i] + 20);
		_txtBox[i]->textPos(stX + 20, stY + 45);

		cnt++;
		if (cnt > 1 ) {
			stX = _sX + difX;
			stY = _sY;
			cnt = 0;
		} else {
			stY+= difY;	
		}
	}	
}	
// endregion >>>> INITISIALISATION


// region ################################################ HOME update
void adriiot_tft_home::update(int i){
	fsprintf("\n%s\n",adriTFTscreen_get_name());
			// if (adriTFTscreen_get_name() != (const char*)"home") return;
			int pos = -1;
			adriTFTscreen_get_pos(pos);
			if (pos != _pos) return;
			if (i>3) return;

			int 		id;
			mSensorType	sType;
			mType 		moduleType;
			mRelayType	relayType;
			boolean 	state;
			String 		sValue;
			String 		dName;
			uint16_t color_off = ui.color565(0,0,0);
			uint16_t color_on = ui.color565(0,80,0);
			moduleClassArray[i]->username_get(dName);

			moduleClassArray[i]->id_get(id);
			moduleClassArray[i]->mType_get(moduleType);

			_txtBoxValue[i]->u8g2_draw();
			

			if (moduleType == mt_sensor) {
					moduleClassArray[i]->sType_get(sType);
					if (sType==st_soilmoisture) {
					
					}
					if (sType==st_dht22) {
						// tft.fillRect(_aX[i], _aY[i], 40, 40, 0);
						tft.drawBitmap(_aX[i], _aY[i], thermometherbitmap, 40, 40, ui.color565(47, 74, 196));
						float v;
						adriiot_mainPtr->_dht22Managment->module(id)->read_temperature(v,state);
						GetVal(sValue, v);	
						// ADRI_LOGV(-1, 2, 2, dName, "%.02f", v);					
					}	
					if (sType==st_ds18b20) {
						tft.drawBitmap(_aX[i], _aY[i], thermometherbitmap, 40, 40, ui.color565(47, 74, 196));
						float v;
						adriiot_mainPtr->_ds18b20managment->module(id)->read_temperature(v,state);
						GetVal(sValue, v);
						// ADRI_LOGV(-1, 2, 2, dName, "%.02f", v);	
						// 
					}
			} 
			if (moduleType == mt_relay) {
				moduleClassArray[i]->rType_get(relayType);
				if (relayType==rt_plug) {
					boolean v;
					adriiot_mainPtr->_relayManagment->module(id)->getStatus(v);
					GetVal(sValue, v);		
					if (v) 	{tft.drawBitmap(_aX[i], _aY[i], plugbitmap, 40, 40, color_on);sValue = "On";	}
					else 	{tft.drawBitmap(_aX[i], _aY[i], plugbitmap, 40, 40, color_off);sValue = "Off";}					
					ADRI_LOGV(-1, 2, 2, dName, "%d", v);		
				}	
				if (relayType==rt_light) {
					boolean v;
					adriiot_mainPtr->_relayManagment->module(id)->getStatus(v);
					if (v) 	{tft.drawBitmap(_aX[i], _aY[i], bulbBitmap, 40, 40, color_on);GetVal(sValue, v);	}
					else 	{tft.drawBitmap(_aX[i], _aY[i], bulbBitmap, 40, 40, color_off);sValue = "Off";}
					ADRI_LOGV(-1, 2, 2, dName, "%d", v);	
				}								
			} 
			if (moduleType == mt_lightRGB) {
				boolean v;			
				adriiot_mainPtr->_RGBneoManagment->module(id)->getStatus(v);
				if (v) 	{
					int bri = 0;
					adriiot_mainPtr->_RGBneoManagment->module(id)->getBri(bri);
					boolean isRgb = false;
					int * gRgb = adriiot_mainPtr->_RGBneoManagment->module(id)->getRgb(isRgb);					
					ADRI_LOGV(-1, 2, 2, dName, "isRgb: %d", isRgb);
					if (isRgb){
						tft.drawBitmap(_aX[i], _aY[i], rgbsBitmap, 40, 40, ui.color565(gRgb[0], gRgb[1], gRgb[2]));	
					}
					else {
						tft.drawBitmap(_aX[i], _aY[i], rgbsBitmap, 40, 40, color_on);
					}
					GetVal(sValue, bri);
				}
				else {
					tft.drawBitmap(_aX[i], _aY[i], rgbsBitmap, 40, 40, color_off);
					sValue = "Off";
				}				
				ADRI_LOGV(-1, 2, 2, dName, "%d", v);								
			} 			
			if (moduleType == mt_lightDimmer) {
				boolean v;
				adriiot_mainPtr->_lightDimmerManagment->module(id)->getStatus(v);
				if (v) 	{
					tft.drawBitmap(_aX[i], _aY[i], bulbBitmap, 40, 40, color_on);
					int aValue = 0;
					adriiot_mainPtr->_lightDimmerManagment->module(id)->getValue(aValue);
					GetVal(sValue, aValue);	
				}
				else {
					tft.drawBitmap(_aX[i], _aY[i], bulbBitmap, 40, 40, color_off);	
					sValue = "Off";	
				}			
				ADRI_LOGV(-1, 2, 2, dName, "%d", v);				
			} 
			_txtBoxValue[i]->u8g2_drawRect();
			_txtBoxValue[i]->text(sValue);
			_txtBoxValue[i]->u8g2_setup();
			_txtBoxValue[i]->u8g2_drawRect(sValue);
			_txtBox[i]->text(sValue);
			_txtBox[i]->u8g2_setup();
			_txtBox[i]->u8g2_drawRect(dName);
}	
// endregion >>>> HOME update


// region ################################################ DEVICE constructor
adriiot_tft_device::adriiot_tft_device(){
	adriiot_tft_device_ptr = this;
	int count = adriiot_main_ptrGet()->_moduleManagment->_pos;
	for (int i = 0; i < count; ++i)
	{
		_txtBox[i] = new adriTFTUI_txtBox(&tft, u8g2);
		_txtBox[i]->textColor(ILI9341_WHITE, _color_home_2);
		_txtBox[i]->u8g2_mod(1);
		_txtBox[i]->u8g2_font(font_default);
		_txtBox[i]->text("");
		_txtBox[i]->u8g2_setup();

		_txtBoxValue[i] = new adriTFTUI_txtBox(&tft, u8g2);
		_txtBoxValue[i]->textColor(ui.color565(255, 119, 0), _color_home_2);
		_txtBoxValue[i]->u8g2_mod(1);
		_txtBoxValue[i]->u8g2_font(font_default);
		_txtBoxValue[i]->text("");
		_txtBoxValue[i]->u8g2_setup();				
	}	
	init();
}		
// endregion >>>> DEVICE constructor

// region ################################################ DEVICE INITIIALISATION
void adriiot_tft_device::init(){
	int count = adriiot_main_ptrGet()->_moduleManagment->_pos;
	int stY = _sY;
	int stX = _sX;
	int difY = 55;
	for (int i = 0; i < count; ++i)
	{	
		if (i>3) break;
		_aX[i] = stX;
		_aY[i] = stY;
		_init[i] = false;
		stY+= difY;	
	}	
}	
// endregion >>>> DEVICE INITISIALISATION
// region ################################################ DEVICE UPDATE
void adriiot_tft_device::update(int i){

			int pos = -1;

			adriTFTscreen_get_pos(pos);

			if (pos != _pos) return;
			if (i>3) return;

			int w, h;
			int 		id;
			mSensorType	sType;
			mType 		moduleType;
			mRelayType	relayType;
			boolean 	state;
			String 		sValue;
			String 		dName;
			uint16_t 	color_off = ui.color565(30,30,30);
			uint16_t 	color_on = ui.color565(0,80,0);

			moduleClassArray[i]->username_get(dName);
			moduleClassArray[i]->id_get(id);
			moduleClassArray[i]->mType_get(moduleType);

			if (!_init[i]) {
				tft.fillRect(_aX[i],_aY[i], tft.width()-30, 50, _color_home_2);
				tft.drawRect(_aX[i],_aY[i], tft.width()-30, 50, _color_bg_2);
				_init[i] = true;
			}

				
			if (moduleType == mt_sensor) {
					moduleClassArray[i]->sType_get(sType);
					if (sType==st_soilmoisture) {
					
					}
					if (sType==st_dht22) {
						// tft.fillRect(_aX[i], _aY[i], 40, 40, 0);
						tft.drawBitmap(_aX[i]+5, _aY[i]+5, thermometherbitmap, 40, 40, ui.color565(47, 74, 196));
						float v;
						adriiot_mainPtr->_dht22Managment->module(id)->read_temperature(v,state);
						GetVal(sValue, v);	
						// ADRI_LOGV(-1, 2, 2, dName, "%.02f", v);					
					}	
					if (sType==st_ds18b20) {
						tft.drawBitmap(_aX[i]+5, _aY[i]+5, thermometherbitmap, 40, 40, ui.color565(47, 74, 196));
						float v;
						adriiot_mainPtr->_ds18b20managment->module(id)->read_temperature(v,state);
						GetVal(sValue, v);
						// ADRI_LOGV(-1, 2, 2, dName, "%.02f", v);	
						// 
					}
			} 
			if (moduleType == mt_relay) {
				moduleClassArray[i]->rType_get(relayType);
				if (relayType==rt_plug) {
					boolean v;
					adriiot_mainPtr->_relayManagment->module(id)->getStatus(v);
					GetVal(sValue, v);		
					if (v) 	{tft.drawBitmap(_aX[i]+5, _aY[i]+5, plugbitmap, 40, 40, color_on);sValue = "On";	}
					else 	{tft.drawBitmap(_aX[i]+5, _aY[i]+5, plugbitmap, 40, 40, color_off);sValue = "Off";}					
					ADRI_LOGV(-1, 2, 2, dName, "%d", v);		
				}	
				if (relayType==rt_light) {
					boolean v;
					adriiot_mainPtr->_relayManagment->module(id)->getStatus(v);
					if (v) 	{tft.drawBitmap(_aX[i]+5, _aY[i]+5, bulbBitmap, 40, 40, color_on);GetVal(sValue, v);	}
					else 	{tft.drawBitmap(_aX[i]+5, _aY[i]+5, bulbBitmap, 40, 40, color_off);sValue = "Off";}
					ADRI_LOGV(-1, 2, 2, dName, "%d", v);	
				}								
			} 
			if (moduleType == mt_lightRGB) {
				boolean v;			
				adriiot_mainPtr->_RGBneoManagment->module(id)->getStatus(v);
				if (v) 	{
					int bri = 0;
					adriiot_mainPtr->_RGBneoManagment->module(id)->getBri(bri);
					boolean isRgb = false;
					int * gRgb = adriiot_mainPtr->_RGBneoManagment->module(id)->getRgb(isRgb);					
					ADRI_LOGV(-1, 2, 2, dName, "isRgb: %d", isRgb);
					if (isRgb){
						tft.drawBitmap(_aX[i]+5, _aY[i]+5, rgbsBitmap, 40, 40, ui.color565(gRgb[0], gRgb[1], gRgb[2]));	
					}
					else {
						tft.drawBitmap(_aX[i]+5, _aY[i]+5, rgbsBitmap, 40, 40, color_on);
					}
					GetVal(sValue, bri);
				}
				else {
					tft.drawBitmap(_aX[i]+5, _aY[i]+5, rgbsBitmap, 40, 40, color_off);
					sValue = "Off";
				}				
				ADRI_LOGV(-1, 2, 2, dName, "%d", v);								
			} 			
			if (moduleType == mt_lightDimmer) {
				boolean v;
				adriiot_mainPtr->_lightDimmerManagment->module(id)->getStatus(v);
				if (v) 	{
					tft.drawBitmap(_aX[i]+5, _aY[i]+5, bulbBitmap, 40, 40, color_on);
					int aValue = 0;
					adriiot_mainPtr->_lightDimmerManagment->module(id)->getValue(aValue);
					GetVal(sValue, aValue);	
				}
				else {
					tft.drawBitmap(_aX[i]+5, _aY[i]+5, bulbBitmap, 40, 40, color_off);	
					sValue = "Off";	
				}			
				ADRI_LOGV(-1, 2, 2, dName, "%d", v);				
			} 

		_txtBox[i]->textPos(_aX[i] + 50, _aY[i] + 27);
		_txtBox[i]->text(dName);
		_txtBox[i]->u8g2_setup();
		_txtBox[i]->u8g2_drawRect(dName);
		_txtBoxValue[i]->textPos(tft.width()- (80), _aY[i] + 27);
		_txtBoxValue[i]->u8g2_drawRect();	
		_txtBoxValue[i]->text(sValue);
		_txtBoxValue[i]->u8g2_setup();	
		_txtBoxValue[i]->u8g2_drawRect(sValue);	
}	
// endregion >>>> DEVICE UPDATE
