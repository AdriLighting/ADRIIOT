#ifndef HOME_H
	#define HOME_H
	
	#include <arduino.h>
	#include <TimeLib.h>
	#include <calendar_date.h>
	#include <adri_timeNtp.h>

	#include "../tft_ui.h"
	#include "../ui_screen.h"
	#include "../tft_init.h"
	#include "../ui_colors.h"
	#include "../../tft_lib.h"
	#include "../../json/htttpget_jsonreader.h"


	class uiScreen_home : public ui_screen 
	{
	public:
		char 				_name[80];
		adriTFTscreen 		* _screen;
		adriTFTUI_lblValue 	* _screen_device_infos;

		explicit uiScreen_home(const String &id);
		~uiScreen_home(){};

		void main(boolean init) override;
		void loop()				override;
		void loadValue() 		override;		
		
	};
#endif