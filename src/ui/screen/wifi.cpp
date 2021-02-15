#include "wifi.h"
#include <adri_tools_v2.h>
#include "../fonts/SansSerif_plain_10.h"
#include "../tft_touch.h"
#include "menuicon.h"
#include "../ui_colors.h"
#include <adri_wifiConnect.h>

namespace {
	uiScreen_wifi * ptr;

	void _main(boolean init){
		ptr->main(init);
	}
	void _loop(){
		ptr->loop();
	}
}


uiScreen_wifi::uiScreen_wifi(const String &id) : ui_screen(id)  {
	ptr = this;
	sprintf(_name, "%s", id.c_str());
	_screen = new adriTFTscreen(_name,	_main, _loop);
	_screen_wifi_infos = new adriTFTUI_lblValue("wifiInfos", &ui, &tft, u8g2);
	_screen_wifi_infos->_c_sep 		= _color_lblSep_1;
	_screen_wifi_infos->_c_value 	= _color_lblValue_1;
	_screen_wifi_infos->_c_name 	= _color_lblName_1;
	_screen_wifi_infos->_u8g2Font 	= font_default;	
	_screen_wifi_infos->_w_name_max	= 100;	
	_screen_wifi_infos->_font 		= &SansSerif_plain_10;	
	_screen_wifi_infos->_u8g2_text 	= false;	
}

String  _string_to_split(String name, String value, String sep){
    return name + sep + value;
}
String  _string_to_split(String name, String value){
    return name + ";" + value + "\n";
}

void uiScreen_wifi::main(boolean init){
	// fsprintf("\n[uiScreen_wifi] init: %d\n", init);
	tft.fillScreen(ILI9341_BLACK);
	String str;

	str+=_string_to_split("ip", 		wifiConnect_instance()->currentIp_get());
	str+=_string_to_split("ssid", 	wifiConnect_instance()->currentSSID_get());
	
	str+=_string_to_split("init", String(init));
	str+="\n";

	// String str = esp_wifi_settings();
	_screen_wifi_infos->lines_clear();	
	_screen_wifi_infos->lineSplit_add(str);	
	// str = core_info();
	// _screen_wifi_infos->lineSplit_add(str);	
	// tft.fillScreen(ILI9341_BLACK);
	_screen_wifi_infos->xy(10,30);	
	_screen_wifi_infos->rect_clear(0);	
	_screen_wifi_infos->lines_create(10,30);
	

	ui_menuicon_instance()->footer_display(init, _name, _color_home);
	// ui_menuicon_instance()->left_display(init, _name, _color_home);
	#ifdef ILI9341_USETOUCH
		button_create(_name);	
	#endif	
}
// adri_timeNtp_instance()
void uiScreen_wifi::loop(){

	
}
void uiScreen_wifi::loadValue(){

	
}