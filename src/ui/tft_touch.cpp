#include "tft_touch.h"
#ifdef ILI9341_USETOUCH

// TOUCH SCREEN 
static uint16_t touch_prev_x = 0xffff, touch_prev_y = 0xffff;
int 	touch_btn_interval = -1;
boolean touch_btn_resetBorder = false;

// GLOBAL TIMER
adri_timer * timer_1;
adri_timer * timer_5;
adri_timer * timer_6;

/*
	########################################### TOUCH LOOP
*/
void button_init(){
	timer_1 = new adri_timer(250, 	"touch_btn", 			true);
	timer_5 = new adri_timer(250, 	"touch_btn_intervall", 	true);
	timer_6 = new adri_timer(250, 	"", 					false);

}
bool _isTouched(XPT2046 * touchScreen) {
	return touchScreen->isTouching();
}

boolean button_loop_leav 	= false;
int button_loop_lock 		= -1;
void button_loop(){
	// char buffer[300];
	const char * curr_screen = adriTFTscreen_get_name();
	// char buffer[80];
	uint16_t x, y;
	if ( timer_1->loop_wait()) {
		if (_isTouched(&touch)) {
			touch.getPosition(x, y);
			touch_prev_x = x;
			touch_prev_y = y;
			
		} else touch_prev_x = touch_prev_y = 0xffff;	
			
		for (int i = 0; i < ui._buttonCnt; ++i) {
			if (curr_screen != ui.button_manage[i]->_screen) continue;

			ui.button[i]->press(ui.button[i]->contains(touch_prev_x, touch_prev_y));
			if (ui.button[i]->justPressed()) {

				timer_5->set_duration(millis());
				
				if (! timer_6->isActivate()) timer_6->activate();button_loop_lock=i;

				touch_btn_interval = i;
				ui.button[i]->button_borderColor(true, ILI9341_GREEN);	

			}	

			if (ui.button[i]->justReleased()) {
				if (touch_btn_interval >= 0 ){
					if (timer_5->loop()) {

						// sprintf(buffer, "\n[button_loop] [%d] - %s - %s", i, ui.button_manage[i]->_screen, curr_screen);
						// Serial.println(buffer);

						ui.button[i]->button_borderColor(false, 0);

						int eventPos = ui.button_manage[i]->_eventPos;
						if (eventPos == -1) 	ui.button[i]->_func();
						else  					ui.button[i]->_funParm(eventPos);
						timer_6->activate(false);
						
					}else {
						touch_btn_resetBorder = true;
					}
					touch_btn_interval = -1;
				}

				timer_1->activate();
				break;
			}	
		}			
	}	

	if (timer_6->isActivate()) {
		if (timer_6->loop(2500)) {
			if ((touch_btn_interval >= 0 ) && (button_loop_lock==touch_btn_interval)){

				// sprintf(buffer, "\n[button_loop] [%d] - %s - %s", touch_btn_interval, ui.button_manage[touch_btn_interval]->_screen, curr_screen);
				// Serial.println(buffer);
										
				ui.button[touch_btn_interval]->button_borderColor(false, 0);

				int eventPos = ui.button_manage[touch_btn_interval]->_eventPos;
				if (eventPos == -1) 	ui.button[touch_btn_interval]->_func();
				else  					ui.button[touch_btn_interval]->_funParm(eventPos);

				button_loop_lock 	= -1;
				touch_btn_interval 	= -1;

				timer_1->activate();
				timer_6->activate(false);
			}	
		}	
	}


	if (touch_btn_resetBorder) {
		timer_6->activate(false);
		for (int i = 0; i < ui._buttonCnt; ++i)	{
			touch_btn_resetBorder = false;
			if (curr_screen != ui.button_manage[i]->_screen) continue;
			ui.button[i]->button_borderColor(false, 0);

		}
	}
}
void button_create(const char * screen){
	for (int i = 0; i < ui._buttonCnt; ++i) {
		if (ui.button_manage[i]->_screen == screen) ui.button[i]->button_create_fromLoop();
	}		
}	
#endif