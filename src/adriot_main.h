
#ifndef ADRIOT_MAIN_H
#define ADRIOT_MAIN_H
	#include <Arduino.h>
	#include "adriot_lib.h"

	class adriot_main
	{

	public:
		relayManagement * _relayManagment;
		
		adriot_main();
		~adriot_main(){};
		
	};
#endif // ADRIOT_MAIN_H