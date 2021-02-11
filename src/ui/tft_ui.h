

#ifndef TFT_UI_H
	#define TFT_UI_H

	#include <arduino.h>

	#include "tft_init.h"
	#include "../tft_lib.h"

	#include "screen/menuicon.h"

	#include "ui_screen.h"



	struct uiScreenList {
		const char 	* name;
		int 		addEffect;
		void 		(* registerScreen)(const char * name, int pos);
		
	};	

	class ui_screen;
	class tft_ui
	{
		ui_menuicon * _menuIcon;
	public:
		tft_ui();
		~tft_ui(){};
		void screen_create();
		void registerScreen();
		void mainLoop();
		// void loop() override;
		virtual void main(boolean init);
		virtual void loop();	
		virtual void loadValue();	
	};


	void sreen_next();
	void sreen_prev();
	void sreen_go_home();
	void sreen_go_wifi();
	void sreen_go_device();
	void sreen_go_alarmClock();	

	void tft_ui_loadValueScreen();
	
	tft_ui * tft_ui_instance();
#endif