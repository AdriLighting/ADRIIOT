#ifndef PROGRAMME_PATTERN_H
	#define PROGRAMME_PATTERN_H

	#include <Arduino.h>
	#include <ArduinoJson.h>

	#include "patterns.h"
	#include "playlist_pattern.h"



	class programme_loop {
		pattern_loop 	* _patterns;
		pattern_list 	* _patterns_list;
	public:
		programme_loop();
		~programme_loop(){delete this;};

		
		void loop(mod_pattern_loop & mod, String & v1, boolean & playlist);

		void patternList_initialize(uint8_t maxCnt);
		void patternList_item_add(String value);
		void patternList_randomEffect(String & ret);
		void patternList_item_getName(String & value, uint8_t pos);
		boolean patternList_itemGetPosByName(String search, int & result);
		boolean pattern_list_changeEffect(String search, int & result);
		void patternList_print();
		void patternList_jsonObject(JsonObject & root);
		boolean pattern_list_changeEffect(boolean dir, String & ret);

		void patternLoop_pos_set(uint8_t pos);
		void patternLoop_pos_get(uint8_t & pos);

		void patternLoop_delay_get(uint32_t & value);
		void patternLoop_delayCurrent_get(uint32_t & value);
		void patternLoop_delayManual_get(boolean & value);

		void patternLoop_posMin_get(uint8_t & value);
		void patternLoop_posMax_get(uint8_t & value);

		mod_pattern_loop patternLoop_statuDefault();
		mod_pattern_loop patternLoop_statuNext();
		boolean patternLoop_isPlaying();
		boolean patternLoop_isRndPlaying();

		void patternLoop_play_set			(boolean pos);
		void patternLoop_autoPlay 			();
		void patternLoop_playRnd_set		(boolean pos);
		void patternLoop_delay_set 			(int pos);
		void patternLoop_delayCurrent_set	(int pos);
		void patternLoop_delayManual_set	(boolean pos);
		void patternLoop_autoPlayRnd 		();

	};

	programme_loop * programmeLoop_instance();
#endif


/*

		unsigned long 		_timer_cyclePattern_lastChange;
		unsigned long 		_timer_cyclePatternFunc_lastChange;

		unsigned long   	_timer_cyclePalette_lastChange;

		unsigned long   	_timer_cycleColor_lastChange;

		unsigned long   	_timer_cycleHue_lastChange;

		unsigned long   	_timer_cycleReverse_lastChange;

*/	