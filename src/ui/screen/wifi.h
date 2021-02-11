#ifndef WIFI_H
	#define WIFI_H
	
	#include <arduino.h>

	#include "../ui_screen.h"
	#include "../tft_init.h"
	#include "../../tft_lib.h"


	class uiScreen_wifi : public ui_screen 
	{
	public:
		adriTFTUI_lblValue * _screen_wifi_infos;

		char 			_name[80];
		adriTFTscreen 	* _screen;

		explicit uiScreen_wifi(const String &id);
		~uiScreen_wifi(){};

		void main(boolean init) override;
		void loop()				override;
		void loadValue() 		override;		
		
	};
#endif