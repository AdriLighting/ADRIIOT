#include "tft_init.h"
#include "../tft_lib.h"



// INITIALISATION TFT
Adafruit_ILI9341  		tft = Adafruit_ILI9341(15, 2);
#ifdef ILI9341_USETOUCH
	XPT2046 				touch(/*cs=*/ 4, /*irq=*/ 5);
#endif
adriTFTUI 				ui 	= adriTFTUI(&tft);
U8G2_FOR_ADAFRUIT_GFX 	u8g2;
adriTFTUI_button * myBtn;


