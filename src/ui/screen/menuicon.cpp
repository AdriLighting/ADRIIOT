#include "menuicon.h"

#include <adri_tools_v2.h>
#include "icons.h"
#include "../ui_colors.h"
#include "../tft_init.h"
#include "../tft_ui.h"
#include "../../tft_lib.h"

ui_menuicon * ui_menuicon_ptr;
ui_menuicon * ui_menuicon_instance(){
	return ui_menuicon_ptr;
}
ui_menuicon::ui_menuicon(){
	ui_menuicon_ptr = this;
}
/*
	########################################### ALLSCREEN BOTTOM RIGHT ICON
*/
void ui_menuicon::footer_display(bool init, const char * screen) {
	int starty = tft.height() - 50;
	int wB = 40;
	int sep = 10;
	int xC = tft.width()/2;
	int wA = (wB*6)+(5*sep);
	int xL = xC - (wA/2);
	int x5 = xL+(wB*5)+(sep*5);
	if(init){
		myBtn = ui.button_int( x5,	starty, 40, 40, 0, 0, 0, 0, BTM_UNK, 	"",	screen);
		myBtn->button_changeBorderColor(0);	
		myBtn->attachFunc(sreen_go_home);		
	}
	tft.drawBitmap(x5, 	starty, accueilBitmap, 	40, 40, _color_ico_home);
}
void ui_menuicon::footer_display(bool init, const char * screen, uint16_t bc) {
	int starty = tft.height() - 50;
	int wB = 40;
	int sep = 10;
	int xC = tft.width()/2;
	int wA = (wB*6)+(5*sep);
	int xL = xC - (wA/2);
	int x5 = xL+(wB*5)+(sep*5);
	if(init){
		adriTFTUI_button * myBtn;
		myBtn = ui.button_int( x5,	starty, 40, 40, 0, 0, bc, 0, BTM_UNK, 	"",	screen);
		myBtn->button_changeBorderColor(bc);	
		myBtn->attachFunc(sreen_go_home);		
	}
	tft.drawBitmap(x5, 	starty, accueilBitmap, 	40, 40, _color_ico_home);
}

/*
	########################################### SELECTED SCREEN BOTTOM LEFT ICON
*/

void attF(){
	fsprintf("\n[atf]\n");
}
void ui_menuicon::light_display(bool init, const char * screen, uint16_t bc){
	int starty = tft.height() - 50;
	int wB = 40;
	int sep = 10;
	int xC = tft.width()/2;
	int wA = (wB*6)+(5*sep);
	int xL = xC - (wA/2);
	int x1 = xL;
	int x2 = xL+wB+sep;
	int x3 = xL+(wB*2)+(sep*2);
	int x4 = xL+(wB*3)+(sep*3);
	int x5 = xL+(wB*4)+(sep*4);
	if (init) {

		adriTFTUI_button * myBtn;

		myBtn = ui.button_int( x1,	starty, 40, 40, 0, 0, 0, 0, BTM_UNK, 	"",	screen);
		myBtn->button_changeBorderColor(bc);	
		// myBtn->attachFunc(_uiScreenLight_mainColor);

		myBtn = ui.button_int( x2,	starty, 40, 40, 0, 0, 0, 0, BTM_UNK, 	"",	screen);
		myBtn->button_changeBorderColor(bc);	
		// myBtn->attachFunc(_uiScreenLight_mainTw);

		// // myBtn = ui.button_int( 110,	starty, 0, 0, 0, 0, 0, _color_ico_1, BTM_FTEXTUTF8, 	"",	screen);
		// myBtn = ui.button_int( x3,	starty, 40, 40, 0, 0, 0, 0, BTM_UNK, 	"",	screen);
		// // myBtn->button_changeText("\u0051");
		// // myBtn->button_changeTextUtf8Font(u8g2_font_open_iconic_www_4x_t);
		// myBtn->button_changeBorderColor(bc);	
		// myBtn->attachFunc(attF);

		// myBtn = ui.button_int( x4,	starty, 40, 40, 0, 0, 0, 0, BTM_UNK, 	"",	screen);
		// // myBtn->button_changeText("\u0051");
		// // myBtn->button_changeTextUtf8Font(u8g2_font_open_iconic_www_4x_t);
		// myBtn->button_changeBorderColor(bc);	

		// myBtn = ui.button_int( x5,	starty, 40, 40, 0, 0, 0, 0, BTM_UNK, 	"",	screen);
		// // myBtn->button_changeText("\u0051");
		// // myBtn->button_changeTextUtf8Font(u8g2_font_open_iconic_www_4x_t);
		// myBtn->button_changeBorderColor(bc);	
		// myBtn->attachFunc(sreen_go_wifi);
		
	} 	

		tft.drawBitmap(x1, starty, colorLensBitmap,		40, 40, _color_ico_mp3);
		tft.drawBitmap(x2, starty, bri_1Bitmap, 		40, 40, _color_ico_alarm);
		// tft.drawBitmap(x3, starty, sheduleBitmap,		40, 40, _color_ico_wifi);
		// tft.drawBitmap(x4, starty, settingsLightBitmap,	40, 40, _color_ico_light);		
		// tft.drawBitmap(x5, starty, wifi_icoBitmap, 		40, 40, _color_ico_settings);		
}
void ui_menuicon::left_display(bool init, const char * screen, uint16_t bc){
	int starty = tft.height() - 50;
	int wB = 40;
	int sep = 10;
	int xC = tft.width()/2;
	int wA = (wB*6)+(5*sep);
	int xL = xC - (wA/2);
	int x1 = xL;
	int x2 = xL+wB+sep;
	int x3 = xL+(wB*2)+(sep*2);
	int x4 = xL+(wB*3)+(sep*3);
	int x5 = xL+(wB*4)+(sep*4);
	if (init) {
		adriTFTUI_button * myBtn;
		// myBtn = ui.button_int( 10,	starty, 0, 0, 0, 0, 0, _color_ico_1, BTM_FTEXTUTF8, 	"",	screen);
		myBtn = ui.button_int( x1,	starty, 40, 40, 0, 0, 0, 0, BTM_UNK, 	"",	screen);

		// myBtn->button_changeText("\u0043");
		// myBtn->button_changeTextUtf8Font(u8g2_font_open_iconic_play_4x_t);
		myBtn->button_changeBorderColor(bc);	
		// myBtn->attachFunc(sreen_go_light);



		// myBtn = ui.button_int( 60,	starty, 0, 0, 0, 0, 0, _color_ico_1, BTM_FTEXTUTF8, 	"",	screen);
		myBtn = ui.button_int( x2,	starty, 40, 40, 0, 0, 0, 0, BTM_UNK, 	"",	screen);
		// myBtn->button_changeText("\u0045");
		// myBtn->button_changeTextUtf8Font(u8g2_font_open_iconic_app_4x_t);
		myBtn->button_changeBorderColor(bc);	
		// myBtn->attachFunc(sreen_go_effects);

		// myBtn = ui.button_int( 110,	starty, 0, 0, 0, 0, 0, _color_ico_1, BTM_FTEXTUTF8, 	"",	screen);
		myBtn = ui.button_int( x3,	starty, 40, 40, 0, 0, 0, 0, BTM_UNK, 	"",	screen);
		// myBtn->button_changeText("\u0051");
		// myBtn->button_changeTextUtf8Font(u8g2_font_open_iconic_www_4x_t);
		myBtn->button_changeBorderColor(bc);	
		myBtn->attachFunc(attF);

		myBtn = ui.button_int( x4,	starty, 40, 40, 0, 0, 0, 0, BTM_UNK, 	"",	screen);
		// myBtn->button_changeText("\u0051");
		// myBtn->button_changeTextUtf8Font(u8g2_font_open_iconic_www_4x_t);
		myBtn->button_changeBorderColor(bc);	

		myBtn = ui.button_int( x5,	starty, 40, 40, 0, 0, 0, 0, BTM_UNK, 	"",	screen);
		// myBtn->button_changeText("\u0051");
		// myBtn->button_changeTextUtf8Font(u8g2_font_open_iconic_www_4x_t);
		myBtn->button_changeBorderColor(bc);	
		myBtn->attachFunc(sreen_go_wifi);
		
	} 	

		tft.drawBitmap(x1, starty, lightBitmap, 		40, 40, _color_ico_mp3);
		tft.drawBitmap(x2, starty, playlistBitmap, 		40, 40, _color_ico_alarm);
		tft.drawBitmap(x3, starty, sheduleBitmap,		40, 40, _color_ico_wifi);
		tft.drawBitmap(x4, starty, settingsLightBitmap,	40, 40, _color_ico_light);		
		tft.drawBitmap(x5, starty, wifi_icoBitmap, 		40, 40, _color_ico_settings);		
}
void ui_menuicon::left_display(bool init, const char * screen){
	left_display(init, screen, 0);	
}
