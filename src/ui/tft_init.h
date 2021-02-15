#ifndef TFT_INIT_H
	#define TFT_INIT_H 

	#include "../tft_lib.h"

	// INITIALISATION TFT
	extern Adafruit_ILI9341  		tft;
	#ifdef ILI9341_USETOUCH
		extern XPT2046 					touch;	
	#endif
	extern adriTFTUI 				ui;
	extern U8G2_FOR_ADAFRUIT_GFX 	u8g2;
	extern adriTFTUI_button * myBtn;



#endif