#include "ui_colors.h"
#include "tft_init.h"

// TRY TO MAK A COOLOR THEME FOR ALL SCREEN
/*
uint16_t colorLightGray = ui.color565(192,192,192);
uint16_t colorGray = ui.color565(127,127,127);
uint16_t colorDarkGray = ui.color565(64,64,64);
*/
// uint16_t _color_7seg_h 			= ui.color565(255, 205, 0);
// uint16_t _color_7seg_m 			= ui.color565(255, 170, 0);
// uint16_t _color_7seg_s 			= ui.color565(255, 135, 0);

// uint16_t _color_7seg_h 			= ui.color565(195, 170, 115);
// uint16_t _color_7seg_m 			= ui.color565(195, 145, 90);
// uint16_t _color_7seg_s 			= ui.color565(195, 120, 65);

// uint16_t _color_7seg_h 			= ui.color565(115, 170, 195);
// uint16_t _color_7seg_m 			= ui.color565(90, 145, 195);
// uint16_t _color_7seg_s 			= ui.color565(65, 120, 195);

uint16_t _color_home 			= ui.color565(0, 0, 0);
uint16_t _color_home_1 			= ui.color565(0, 0, 0);
uint16_t _color_home_2 			= ui.color565(15, 15, 15);
uint16_t _color_home_3 			= ui.color565(20, 20, 20);
uint16_t _color_home_1_bgClock 	= ui.color565(30, 30, 30);

uint16_t _color_7seg_h 			= ui.color565(175, 185, 195);
uint16_t _color_7seg_m 			= ui.color565(165, 175, 195);
uint16_t _color_7seg_s 			= ui.color565(155, 165, 195);

uint16_t _color_1 			= ui.color565(30, 30, 160);

uint16_t _color_bg_1 		= ui.color565(80, 	80, 80); 	// mp3 	- bg: lbls + bt  | 
// mp3 	- bg: progressbar  | home - rect  | wificonect - ball  | clockRound bgBack
uint16_t _color_bg_2		= ui.color565(50,	50, 50);	
uint16_t _color_bg_3		= ui.color565(150, 150, 150);	// clockRound 	- time

uint16_t _color_bg_7seg_1	= ui.color565(50, 50, 50);	
uint16_t _color_bg_7seg		= ui.color565(35, 35, 35);	
uint16_t _color_bg_7segMin 	= ui.color565(160, 200, 200); 	
uint16_t _color_clockDigit 	= ui.color565(160, 200, 200); 	 

uint16_t _color_ico_mp3			= ui.color565(30, 70, 90); 	// main - ico 				| footer 	- ico
uint16_t _color_ico_alarm		= ui.color565(35, 60, 105); // main - ico 				| footer 	- ico
uint16_t _color_ico_wifi		= ui.color565(40, 50, 115); // main - ico 				| footer 	- ico
uint16_t _color_ico_light		= ui.color565(40, 50, 115); // main - ico 				| footer 	- ico
uint16_t _color_ico_settings 	= ui.color565(35, 60, 105);	
uint16_t _color_ico_home		= ui.color565(30, 70, 90);	

uint16_t _color_lblName_1	= ui.color565(200, 200, 200);	// mp3 	- lbls name - eq	| wifi  	- ""
uint16_t _color_lblValue_1	= ui.color565(255, 255, 255); 	// mp3 	- lbls value 		| wifi  	- ""
uint16_t _color_lblSep_1 	= ui.color565(255, 255, 0); 	// mp3 	- lbls value 		| wifi  	- ""
uint16_t _color_bt_1		= _color_1; 					// mp3 	- bt grp 1 c
uint16_t _color_bt_2		= _color_bg_1; 					// mp3 	- bt grp 1 bg
uint16_t _color_bt_bc_1		= 0; 							// mp3 	- bt grp 2 c
uint16_t _color_bt_bc_2		= ui.color565(30, 30, 30); 		// mp3 	- bt grp 2 bg

uint16_t _color_bt_3		= C_WHITE; 						// alarm- bt text
uint16_t _color_bt_bc_3		= ui.color565(30, 160, 160); 		// alarm - bt border color
uint16_t _color_sep			= ui.color565(30, 80, 80); 		// alarm - bt border color
uint16_t _color_bg_alarm	= ui.color565(60, 60, 60);		// allarm bt bg	

const uint8_t * font_default = u8g2_font_helvR12_tf;
// const uint8_t * font_default = nullptr;
