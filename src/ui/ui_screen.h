

#ifndef UI_SCREEN_H
#define UI_SCREEN_H 

	#include <arduino.h>

	class ui_screen
	{
		String _id;
	public:
		ui_screen(const String &id);

		virtual ~ui_screen();

		virtual void main(boolean init)	{}
		virtual void loop()				{}
		virtual void loadValue()		{}
	};


#endif
