#ifndef PATTERNS
#define PATTERNS

	#include "Arduino.h"
	#include <ArduinoJson.h>

	#include <adri_timer.h>

	#include "config.h"

		extern uint32_t pInitHeap;

	#ifdef PATHEAPSTATS


		class heap_stats{
			public:
			String 			_name;
			uint32_t 		_initial 			=0;
			uint32_t 		_heap_befor 		=0;
			uint32_t 		_heap_after 		=0;
			unsigned int 	_heap_last 			=0;
			unsigned int 	_heap_last_diff 	=0;
			unsigned int 	_heap_moy 			=0;
			unsigned int 	_heap_min 			=0;
			unsigned int 	_heap_max 			=0;
			unsigned int 	_heap_total 		=0;
			unsigned int 	_timer_total 		=0;
			unsigned long 	_timer_befor 		=0;
			unsigned long 	_timer_duration 	=0;
			int 			_iteration 			=0;
			heap_stats(String name);
			void start();
			void end();
		};
		void heap_stats_get(heap_stats * heap_stat, String name, String & value);

		extern heap_stats * heapStatArray[];
		extern int heap_lastPos;
		extern int heap_newPos;
		extern int heap_pass;		
	#else
		void heapStatsPatternLoop_print(String & ret);
	#endif
		void heapStats_print();




	class pattern_list
	{
		
		String 		* _listName		= nullptr;
		int 		_initialize_cnt = 0;
		int 		_maxcnt 		= 0;
	public:
		pattern_list(uint8_t maxCnt);
		~pattern_list(){delete[] _listName;};
		uint8_t item_add(String value);
		void 	item_getRandomName(String & value);
		void 	item_getName(String & value, uint8_t pos);
		int 	item_getPosByName(String search);
		boolean item_getPosByName(String search, int & result);
		void 	print();
		void 	heapStats_print();
		void 	jsonObject(JsonObject & root);

	};

	pattern_list * 	patternList_instance();
	int 			patternList_itemGetPosByName(pattern_list * ptr, String search);
	void 			patternList_setPtr(pattern_list * ptr);






	enum mod_pattern_loop { 
		mpl_next,
		mpl_off
	};

	class pattern_loop {
		// unsigned long 		_programm_timer_cyclePattern_lastChange;

		// unsigned long 		_programm_timer_cyclePatternFunc_lastChange;

		// uint16_t 			_programm_timer_cyclePattern 		= 25;
		// uint16_t 			_programm_timer_cyclePattern_curr 	= 20;
		// boolean         	_programm_timer_cyclePattern_manual = true;

		// boolean         	_programm_pattern_play 				= true;
		// boolean         	_programm_pattern_autoPlay 			= false;;
		// boolean         	_programm_pattern_autoPlayRandom 	= false;;	
		adri_timer 		* _timer;

		uint32_t 		_delay 			= 10;
		uint32_t		_delayCurrent 	= 20;

		boolean 		_delayManual 	= true;
		
		boolean 		_play 			= true;
		boolean 		_random 		= false;

		int 			_pos 			= 0;
		uint8_t 		_posMin 		= 0;
		uint8_t 		_posMax 		= 0;

		pattern_list 	* _patterns_list;

	public:


		pattern_loop(pattern_list * ptr);
		~pattern_loop(){};

		// 1 play effect + set next effect
		// 2 play effect
		// 3 stop play effect
		void loop(mod_pattern_loop & mod, String & v1);

		void loop_next();
		void next();
		void prev();
		void rnd();
		void pattern_set(boolean dir = true);

		void pos_set 	(uint8_t value);
		void posMin_set (uint8_t value);
		void posMax_set (uint8_t value);

		void play_set (boolean value);
		void playRnd_set (boolean value);

		void delay_set 			(uint32_t 	value);
		void delayCurrent_set 	(uint32_t 	value);
		void delayManual_set 	(boolean 	value);

		void pos_get 	(uint8_t & value);
		void posMin_get (uint8_t & value);
		void posMax_get (uint8_t & value);	

		void delay_get 			(uint32_t 	& value);
		void delayCurrent_get 	(uint32_t 	& value);
		void delayManual_get 	(boolean 	& value);

		boolean isPlaying();
		boolean isRndPlaying();

		mod_pattern_loop statuDefault();
		mod_pattern_loop statuNext();

	};
	pattern_loop 	* patternLoop_instance() ;
	void 			patternLoop_setPtr(pattern_loop * ptr);

#endif