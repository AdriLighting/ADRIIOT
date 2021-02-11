#ifndef MENUICON_H
#define MENUICON_H 

	#include <arduino.h>



	class ui_menuicon
	{
	public:
		ui_menuicon();
		~ui_menuicon(){};
		void footer_display(bool init, const char * screen);
		void footer_display(bool init, const char * screen, uint16_t bc);
		void light_display(bool init, const char * screen, uint16_t bc);
		void left_display(bool init, const char * screen, uint16_t bc);
		void left_display(bool init, const char * screen);	
	};
	ui_menuicon * ui_menuicon_instance();

#endif