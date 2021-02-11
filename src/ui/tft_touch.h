#ifndef TFT_TOUCH_H
	#define TFT_TOUCH_H
	#include "../tft_lib.h"

	#ifdef ILI9341_USETOUCH
		#include <adri_timer.h>
		#include "tft_init.h"


		extern adri_timer * timer_5;
		extern adri_timer * timer_1;
		void button_loop();	
		void button_init();
		void button_create(const char * screen);
		bool _isTouched(XPT2046 * touchScreen);	
	#endif
#endif