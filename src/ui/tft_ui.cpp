#include "tft_ui.h"
#include <adri_tools_v2.h>
#include "tft_touch.h"

#include "screen/home.h"
#include "screen/wifi.h"
#include "screen/devices.h"

ui_screen * ui_screenArray[6];

tft_ui * tft_ui_ptr;
tft_ui * tft_ui_instance(){
	return tft_ui_ptr;
}
tft_ui::tft_ui(){
	tft_ui_ptr = this;

	#ifdef ILI9341_USETOUCH
		tft_setup(&tft, &touch);
	#else
		tft_setup(&tft);	
	#endif
		
	u8g2.begin(tft); 	

	_menuIcon = new ui_menuicon();

	registerScreen();

    #ifdef ILI9341_USETOUCH
    	button_init();	
    #endif

	adriTFTscreen_set_pos(0);
	adriTFTscreen_display();	
}

template <typename T>
void _registerScreen(const String &id, int pos)
{
    ui_screenArray[pos] = new T(id);
}

void registerScreen_home   	(const char * name, int pos) {_registerScreen<uiScreen_home>  	(adri_toolsv2Ptr_get()->ch_toString(name), pos);}
void registerScreen_wifi   	(const char * name, int pos) {_registerScreen<uiScreen_wifi>  	(adri_toolsv2Ptr_get()->ch_toString(name), pos);}
void registerScreen_device	(const char * name, int pos) {_registerScreen<uiScreen_device>	(adri_toolsv2Ptr_get()->ch_toString(name), pos);}

PROGMEM uiScreenList myUiScreenList [] = { 
    {"home",	1,		registerScreen_home		},
    {"device",	1,		registerScreen_device	},
    // {"wifi",	1,		registerScreen_wifi		},
};


uint8_t myUiScreenListCount = ARRAY_SIZE(myUiScreenList);
void tft_ui::screen_create(){


}
void tft_ui::registerScreen(){
    #ifdef DEBUG
        fsprintf("\n[effect_manager::instance]\n");
    #endif

    for (int i = 0; i < myUiScreenListCount; ++i) {
        
		myUiScreenList[i].registerScreen(myUiScreenList[i].name, i); 
       
    } 
}
void tft_ui_loadValueScreen(){
    #ifdef DEBUG
        fsprintf("\n[effect_manager::instance]\n");
    #endif

    for (int i = 0; i < myUiScreenListCount; ++i) {
        
		ui_screenArray[i]->loadValue();
       
    } 
}

void tft_ui::mainLoop(){
	#ifdef ILI9341_USETOUCH
		button_loop();	
	#endif
	adriTFTscreen_loop();
}



void tft_ui::main(boolean init){
	// ui_screenArray[0]->main(init);
}

void tft_ui::loop(){
	// ui_screenArray[0]->loop();
}
void tft_ui::loadValue(){
	// ui_screenArray[0]->loop();
}



void sreen_next(){
	adriTFTscreen_next(1);	
	// screen_footer_display();
}
void sreen_prev(){
	adriTFTscreen_next(-1);	
	// screen_footer_display();
}
void sreen_go_home(){
	adriTFTscreen_set_pos(0);
	adriTFTscreen_display();
	// screen_footer_display();
}
void sreen_go_wifi(){
	adriTFTscreen_set_pos(2);
	adriTFTscreen_display();
	// screen_footer_display();
}
void sreen_go_device(){
	adriTFTscreen_set_pos(1);
	adriTFTscreen_display();
	// screen_footer_display();
}
void sreen_go_alarmClock(){
	adriTFTscreen_set_pos(4);
	adriTFTscreen_display();
	// screen_footer_display();
}
