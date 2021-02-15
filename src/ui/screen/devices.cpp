#include "devices.h"
#include "icons.h"
namespace {
	uiScreen_device * ptr;

	void _main(boolean init){
		ptr->main(init);
	}
	void _loop(){
		ptr->loop();
	}
}


uiScreen_device::uiScreen_device(const String &id) : ui_screen(id)  {
	ptr = this;
	sprintf(_name, "%s", id.c_str());
	_screen = new adriTFTscreen(_name,	_main, _loop);
}

void uiScreen_device::main(boolean init){

	adriTFTUI_txtBox txt(&tft, u8g2);

	_color_home = _color_home_1;

	tft.fillScreen(ILI9341_BLACK);

	// tft.drawRect(5, 		tft.height() - 65, 	tft.width()-10, 65, _color_bg_3);
	// tft.drawFastHLine(30, 	tft.height() - 65, 	tft.width()-60, 	_color_bg_3);
	// tft.drawFastHLine(30, 	tft.height() - 135,	tft.width()-150, 	_color_bg_3);
	tft.fillRect(5,5, tft.width()-10, tft.height()-10, _color_home_1_bgClock);
	tft.drawRect(5,5, tft.width()-10, tft.height()-10, _color_bg_3);
			


	// int sX = 15;
	// int sY = 12;
	// tft.fillRect(sX,sY, tft.width()-30, 50, _color_home_2);
	// tft.drawRect(sX,sY, tft.width()-30, 50, _color_bg_2);
	// tft.drawBitmap(sX+5, sY+5, thermometherbitmap, 40, 40, ui.color565(47, 74, 196));
	// sY+=55;
	// tft.fillRect(sX,sY, tft.width()-30, 50, _color_home_2);
	// tft.drawRect(sX,sY, tft.width()-30, 50, _color_bg_2);
	// tft.drawBitmap(sX+5, sY+5, bulbBitmap, 40, 40, ui.color565(47, 74, 196));
	// sY+=55;
	// tft.fillRect(sX,sY, tft.width()-30, 50, _color_home_2);
	// tft.drawRect(sX,sY, tft.width()-30, 50, _color_bg_2);
	// tft.drawBitmap(sX+5, sY+5, plugbitmap, 40, 40, ui.color565(47, 74, 196));
	// sY+=55;
	// tft.fillRect(sX,sY, tft.width()-30, 50, _color_home_2);
	// tft.drawRect(sX,sY, tft.width()-30, 50, _color_bg_2);
	// tft.drawBitmap(sX+5, sY+5, bulbBitmap, 40, 40, ui.color565(47, 74, 196));

	#ifdef ILI9341_USETOUCH
		button_create(_name);	
	#endif	
}



// adri_timeNtp_instance()
void uiScreen_device::loop(){


}
void uiScreen_device::loadValue(){

}