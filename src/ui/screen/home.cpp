#include "home.h"

#include <adri_wifiConnect.h>
#include <adri_tools_v2.h>

#include "../../meteo/meteo.h"
#include "../fonts/SansSerif_plain_10.h"
#include "../tft_touch.h"
#include "menuicon.h"
#include "icons.h"

namespace {
	uiScreen_home * ptr;

	void _main(boolean init){
		ptr->main(init);
	}
	void _loop(){
		ptr->loop();
	}
}

int clock_loop_min 	= -1;
int clock_loop_hour = -1;
int clock_loop_sec = -1;

int clockRound_loop_min 	= -1;
int clockRound_loop_hour = -1;
int clockRound_loop_sec = -1;

void draw_second_point(int ss);
void draw_HourSegment(int xS, int yS, int hDown, int hUp);

void draw_clock_min(int val);
void draw_clock_hour(int val);
void draw_clock_center();


void draw_7digit(int x, int y, int sep, int w, int16_t c, int16_t bc){
	int y2 		= 95;
	int x2 		= 165;
	time_t ntp_prevDisplay = adri_timeNtp_instance()->timeget();
	if (clock_loop_hour != 	hour(ntp_prevDisplay)){
		clock_loop_hour 	= hour(ntp_prevDisplay);
		draw7Number(&tft, hour(ntp_prevDisplay), 	x, 					y, w, c , bc, 2);	
		int hf_12 		= hourFormat12(ntp_prevDisplay);	
		int tHour 		= map(hf_12, 	0, 12, 0, 120);
		draw_clock_hour(tHour);	
		draw_HourSegment(x2, y2, 60, 90);	
	}	
	if (clock_loop_min != 	minute(ntp_prevDisplay)){
		clock_loop_min 	= minute(ntp_prevDisplay);
		draw7Number(&tft, minute(ntp_prevDisplay), 	x+sep, 				y, w, c , bc, 2);
		int tMin = map(clock_loop_min, 	0, 60, 0, 120);
		draw_clock_min(tMin);		
		draw_HourSegment(x2, y2, 60, 90);
	}	
	if (clock_loop_sec != 	second(ntp_prevDisplay)){
		clock_loop_sec 	= second(ntp_prevDisplay);
		draw7Number(&tft, second(ntp_prevDisplay), 	x+(sep*2), 			y, w, c , bc, 2);	
		draw_second_point(second(ntp_prevDisplay));
	}			
}
void draw_7digit(int x, int y, int sep, int w){
	time_t ntp_prevDisplay = adri_timeNtp_instance()->timeget();
	if (clock_loop_hour != 	hour(ntp_prevDisplay)){
		clock_loop_hour 	= hour(ntp_prevDisplay);
		draw7Number(&tft, hour(ntp_prevDisplay), 	x, 					y, w, _color_7seg_s , _color_bg_7seg_1, 2);	
	}	
	if (clock_loop_min != 	minute(ntp_prevDisplay)){
		clock_loop_min 	= minute(ntp_prevDisplay);
		draw7Number(&tft, minute(ntp_prevDisplay), 	x+sep, 				y, w, _color_7seg_m , _color_bg_7seg_1, 2);
	}	
	if (clock_loop_sec != 	second(ntp_prevDisplay)){
		clock_loop_sec 	= second(ntp_prevDisplay);
		draw7Number(&tft, second(ntp_prevDisplay), 	x+(sep*2), 			y, w, _color_7seg_h , _color_bg_7seg_1, 2);	
	}			
}

void clock_update() {
	time_t ntp_prevDisplay = adri_timeNtp_instance()->timeget();
	if (clockRound_loop_min 	!= 	minute(ntp_prevDisplay)){
		clockRound_loop_min 	= 	minute(ntp_prevDisplay);
		int tMin 				= 	map(minute(ntp_prevDisplay), 	0, 60, 0, 120);
		draw_clock_min(tMin);
		// draw_HourSegment(x, y, 60, 90);
	}
	if (clockRound_loop_hour 	!= hour(ntp_prevDisplay)){
		clockRound_loop_hour 	= 	hour(ntp_prevDisplay);
		int hf_12 		= hourFormat12(ntp_prevDisplay);	
		int tHour 		= map(hf_12, 	0, 12, 0, 120);
		draw_clock_hour(tHour);
		// draw_HourSegment(x, y, 60, 90);
	}	
}

// (120 => 360 degree arc)
void draw_clock_min(int val) {
	int y = 95;
	int x = 165;
	int a = 0;
	fillArc2(&tft, x, y, a, 120,		70, 70, 10, _color_bg_2);
	fillArc2(&tft, x, y, a, val,		70, 70, 10, _color_bg_3);
	draw_HourSegment(x, y, 60, 90);
}
void draw_clock_hour(int val) {
	int y = 95;
	int x = 165;
	int a = 0;
	fillArc2(&tft, x, y, a, 120, 		90, 90, 10, _color_bg_2);
	fillArc2(&tft, x, y, a, val, 		90, 90, 10, _color_bg_3);
	draw_HourSegment(x, y, 60, 90);
}
void draw_clock_center() {
	time_t ntp_prevDisplay = adri_timeNtp_instance()->timeget();
	int hf_12 	= hourFormat12(ntp_prevDisplay);	
	int tHour 	= map(hf_12, 					0, 12, 0, 120);
	int tMin 	= map(minute(ntp_prevDisplay), 	0, 60, 0, 120);
	int y 		= 95;
	int x 		= 165;
	int a 		= 0;
	fillArc2(&tft, x, y, a, 120,		70, 70, 10, _color_bg_2);
	fillArc2(&tft, x, y, a, tMin,		70, 70, 10, _color_bg_3);
	fillArc2(&tft, x, y, a, 120, 		90, 90, 10, _color_bg_2);
	fillArc2(&tft, x, y, a, tHour, 		90, 90, 10, _color_bg_3);
	draw_HourSegment(x, y, 60, 90);
}
float draw_aiguille_osx=0;
float draw_aiguille_osy=0;
float draw_aiguille_omx=0;
float draw_aiguille_omy=0;
float draw_aiguille_ohx=0;
float draw_aiguille_ohy=0;
void draw_aiguille(int ss, int mm, int hh, int S, int M, int H, int yS_1/*120*/, int yS_2/*121*/){
	int y = 95;
	int x = 165;


	// Pre-compute hand degrees, x & y coords for a fast screen update
	float sdeg = ss*6;                  // 0-59 -> 0-354
	float mdeg = mm*6+sdeg*0.01666667;  // 0-59 -> 0-360 - includes seconds
	float hdeg = hh*30+mdeg*0.0833333;  // 0-11 -> 0-360 - includes minutes and seconds
	float hx = cos((hdeg-90)*0.0174532925);    
	float hy = sin((hdeg-90)*0.0174532925);
	float mx = cos((mdeg-90)*0.0174532925);    
	float my = sin((mdeg-90)*0.0174532925);
	float sx = cos((sdeg-90)*0.0174532925);    
	float sy = sin((sdeg-90)*0.0174532925);
	int a = 50;
	int b = 50;
	int c = 165;
	int d = 95;

      tft.drawLine(draw_aiguille_ohx, draw_aiguille_ohy, c, d, 0);
      draw_aiguille_ohx = hx*b+c;    
      draw_aiguille_ohy = hy*b+d;
      tft.drawLine(draw_aiguille_omx, draw_aiguille_omy, c, d, 0);
      draw_aiguille_omx = mx*b+c;    
      draw_aiguille_omy = my*b+d;

      tft.drawLine(draw_aiguille_osx, draw_aiguille_osy, c, d, 0);
      draw_aiguille_osx = sx*a+c;    
      draw_aiguille_osy = sy*a+d;
      tft.drawLine(draw_aiguille_osx, draw_aiguille_osy, c, d, ILI9341_RED);
      tft.drawLine(draw_aiguille_ohx, draw_aiguille_ohy, c, d, C_YELLOW);
      tft.drawLine(draw_aiguille_omx, draw_aiguille_omy, c, d, C_WHITE);      
      tft.drawLine(draw_aiguille_osx, draw_aiguille_osy, c, d, C_GREEN);

}

void draw_second_point(int ss){
	int a = 75;
	int b = 50;
	int c = 165;
	int d = 95;

	float sdeg = ss*6;      
	float sx = cos((sdeg-90)*0.0174532925);    
	float sy = sin((sdeg-90)*0.0174532925);

	tft.fillCircle(draw_aiguille_osx, draw_aiguille_osy,3, 0);
	draw_aiguille_osx = sx*a+c;    
	draw_aiguille_osy = sy*a+d;
	tft.fillCircle(draw_aiguille_osx, draw_aiguille_osy,3, C_WHITE);
	tft.fillCircle(draw_aiguille_osx, draw_aiguille_osy,3, C_WHITE);
     
}
void draw_aiguille(){
	time_t ntp_prevDisplay = adri_timeNtp_instance()->timeget();
	draw_aiguille(
		second(ntp_prevDisplay), minute(ntp_prevDisplay), hourFormat12(ntp_prevDisplay),
	30, 95, 95, 165/*x*/, 95/*121*/);
		Serial.printf("\n%d:%d:%d\n", second(ntp_prevDisplay), minute(ntp_prevDisplay), hourFormat12(ntp_prevDisplay));
}
void draw_HourSegment(int xS, int yS, int hDown, int hUp){
	float sx = 0, sy = 1;
	uint16_t x0=0, x1=0, yy0=0, yy1=0;

	for(int i = 0; i<360; i+= 30) {
		sx = cos((i-90)*0.0174532925);
		sy = sin((i-90)*0.0174532925);
		x0 = sx*hUp+xS;
		yy0 = sy*hUp+yS;
		x1 = sx*hDown+xS;
		yy1 = sy*hDown+yS;

		tft.drawLine(x0, yy0, x1, yy1, 0);
	}	
}


uiScreen_home::uiScreen_home(const String &id) : ui_screen(id)  {
	ptr = this;
	sprintf(_name, "%s", id.c_str());
	_screen = new adriTFTscreen(_name,	_main, _loop);
	_screen_device_infos = new adriTFTUI_lblValue("deviceInfos", &ui, &tft, u8g2);
	_screen_device_infos->_c_sep 		= _color_lblSep_1;
	_screen_device_infos->_c_value 		= _color_lblValue_1;
	_screen_device_infos->_c_name 		= _color_lblName_1;
	_screen_device_infos->_u8g2Font 	= font_default;	
	_screen_device_infos->_w_name_max	= 100;	
	_screen_device_infos->_font 		= &SansSerif_plain_10;	
	_screen_device_infos->_u8g2_text 	= false;	

}

void uiScreen_home::main(boolean init){
	// fsprintf("\n[uiScreen_home] init: %d\n", init);

	
	 clock_loop_min 	= -1;
	 clock_loop_hour 	= -1;
	 clock_loop_sec 	= -1;

	adriTFTUI_txtBox txt(&tft, u8g2);

	_color_home = _color_home_1;

	tft.fillScreen(_color_home);


	int x = 30;
	int y = 120;
	int sep = 60;
	draw7Number(&tft, hour(		adri_timeNtp_instance()->timeget()), 		x,		y, 2, _color_7seg_s , _color_bg_7seg, 2);	
	draw7Number(&tft, minute(	adri_timeNtp_instance()->timeget()), 	x+sep,		y, 2, _color_7seg_m , _color_bg_7seg, 2);
	draw7Number(&tft, second(	adri_timeNtp_instance()->timeget()), 	x+(sep*2),	y, 2, _color_7seg_h , _color_bg_7seg, 2);	

	tft.fillRect(10, 		tft.height() - 130, tft.width()-20, tft.height() -(tft.height() - 130), _color_home_1_bgClock);
	// tft.drawRect(5, 		tft.height() - 65, 	tft.width()-10, 65, _color_bg_3);
	// tft.drawFastHLine(30, 	tft.height() - 65, 	tft.width()-60, 	_color_bg_3);
	// tft.drawFastHLine(30, 	tft.height() - 135,	tft.width()-150, 	_color_bg_3);

		char* 		cDay 			= dayStr(weekday());
					// Serial.printf("\n[screen_main_display] datNbr: %d\n", cDay);
		String		curr_dayStr 	= calendar_date_get_dowStr("en", String(cDay)); 
		String		curr_day 		= String(day());
		String		curr_month 		= String(month());
		char* 		cMonth 			= monthStr(month());
		String		curr_monthStr 	= calendar_date_get_monStr("en", String(cMonth)); 
		String 		date  			= curr_dayStr + " " + curr_day + " " + curr_monthStr;

	boolean wifi_sta_connected = wifi_connect_result();

	int date_w, date_h;
	int xDate = tft.width() - 105;
	txt.u8g2_font(font_default);
	txt.u8g2_mod(0);
	txt.u8g2_dir(0);
	txt.textPos(xDate, 	30);
	txt.text(date);
	txt.textColor(ui.color565(210, 210, 210), _color_home);
	txt.u8g2_setup();
	txt.u8g2_get_wh(date_w, date_h);
	if (wifi_sta_connected) xDate = tft.width() - 105 - date_w;
	else 					xDate = tft.width() - 15 - 	date_w;
	txt.textPos(xDate, 	30);
	txt.u8g2_draw();

	if (!wifi_sta_connected) {
		tft.drawRect(5,5, tft.width()-10, 105, _color_bg_3);
		#ifdef ILI9341_USETOUCH
		ui_menuicon_instance()->footer_display(init, _name, _color_home);
		ui_menuicon_instance()->left_display(init, _name, _color_home);		
		button_create(_name);	
		#endif

		return;
	}

	String temp 	= httpGetJsonReader_getKey(openWeatherMapList_key, "temp",			openWeatherMapList_keyCount, "openweather") ;
	String tempDesc = httpGetJsonReader_getKey(openWeatherMapList_key, "description", 	openWeatherMapList_keyCount, "openweather") ;
	String iconName = httpGetJsonReader_getKey(openWeatherMapList_key, "icon", 			openWeatherMapList_keyCount, "openweather") ;
	String picPath = "/bmp_meteo/" + getMeteoconIcon_3(iconName) + ".bmp";
	ui.drawBmp(picPath, 220, 3);
	tft.drawRect(5,5, tft.width()-10, 105, _color_bg_3);

	int tempD_w, tempD_h;
	int temp_w, temp_h;
	int xTempDesc = tft.width() - 105;

	txt.u8g2_font(font_default);
	txt.u8g2_mod(0);
	txt.u8g2_dir(0);
	txt.textPos(xTempDesc, 	55);
	txt.text(tempDesc);
	txt.textColor(ui.color565(210, 210, 210), _color_home);
	txt.u8g2_setup();
	txt.u8g2_get_wh(tempD_w, tempD_h);
	xTempDesc = tft.width() - 105 - tempD_w;
	txt.textPos(xTempDesc, 	55);
	txt.u8g2_draw();

	// txt.u8g2_draw 	(xTempDesc, 	40, 	tempDesc,	ui.color565(210, 210, 160), font_default);
	txt.u8g2_get_wh(tempD_w, tempD_h);
	txt.text(temp+"°");
	txt.u8g2_get_wh(temp_w, temp_h);
	int xTemp = tft.width() - 105 - (temp_w);
	txt.u8g2_draw 	(xTemp-1,	80, 	temp+"°",	ui.color565(210, 210, 210), _color_home, font_default);
	


	// int sX = 30, sY = 120;

	// tft.drawBitmap(sX, 	sY, bulbBitmap, 	40, 40, ui.color565(255, 255, 0));
	// _txtBox_scroll->textPos(sX + 50, sY + 40);
	// _txtBox_scroll->u8g2_draw();

	// int id;
	// _adriiot->_moduleManagment->getIdByPos(0, id);
	// String dName;
	// _adriiot->_moduleManagment->module(id)->username_get(dName);

	// _txtBox_scroll->u8g2_draw(dName);



	// ui_menuicon_instance()->footer_display(init, _name, _color_home);
	// ui_menuicon_instance()->left_display(init, _name, _color_home);
	#ifdef ILI9341_USETOUCH
		button_create(_name);	
	#endif	
}


int 	screen_alarmClock_clock_sec =-1;
void screen_alarmClock_loop(){
	int x = 25;
	int y = 71;
	int w = 1;
	int sep = 32;

	int16_t bc = _color_bg_7seg;
	int16_t c = _color_bg_7segMin;

	time_t ntp_prevDisplay = adri_timeNtp_instance()->timeget();

	if (screen_alarmClock_clock_sec != 	second(ntp_prevDisplay)){
		screen_alarmClock_clock_sec 	= second(ntp_prevDisplay);
		// String str_1 	= timer_toString(ntp_prevDisplay);
		// screen_alarmClock_clock->text(str_1);
		// screen_alarmClock_clock->canvas_display();
		// draw_aiguille();
		draw7Number(&tft, hour(ntp_prevDisplay), 	x, 					y, w, c , bc, 2);	
		draw7Number(&tft, minute(ntp_prevDisplay), 	x+sep, 				y, w, c , bc, 2);
		draw7Number(&tft, second(ntp_prevDisplay), 	x+(sep*2), 			y, w, c , bc, 2);	
	}
}

// adri_timeNtp_instance()
void uiScreen_home::loop(){

			// draw_7digit(30, 120, 60, 2);
			screen_alarmClock_loop();

}
void uiScreen_home::loadValue(){

}