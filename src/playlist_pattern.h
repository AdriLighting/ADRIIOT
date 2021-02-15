#ifndef PLAYLIST_PATTERN_H
	#define PLAYLIST_PATTERN_H 

	#define COMPOSTIONS_MAX 	10
	#define EFFECTS_MAX 		15
	#define COMPOSTIONS_FILENAME String("/compoName.txt")

	#include <Arduino.h>
	#include <adri_timer.h>

	#include "patterns.h"


// #include <vector>

// using namespace std;

/*
 *
	
	 	name 	= 	/compo_0.tx
	 				/compo_0.txt = sauvegarde des patterns

*/
	class playlist_management
	{
		adri_timer * _item_loop_timer;

		int 	_item_max	= 0;
		int 	_item_pos 	= 0;

		bool 	_list_statu		= false; 
		String 	_list_name 		= "compoName_0";
		int 	_list_pos 		= 0;

	public:

		playlist_management();
		~playlist_management(){delete this;};

		void print();

		void jsonKey_object(JsonObject & root);
		void json_object(JsonObject & root);
		void item_jsonObject(JsonObject & root);
		void json_objectName(JsonObject & object);

		void 	item_print();
		void 	item_toArray(int s_pos, String s_patterName, String s_pattern_config);
		boolean item_restore() ;
		void 	item_remove(int remove) ;

		void 	item_patternName(String & ret);
		void 	item_patternConfig(String & ret);

		void 	item_pos(int & ret);
		void 	item_pos_set(int ret);
		void 	item_max(int & ret);

		void item_loop(pattern_loop * ptr, mod_pattern_loop & mod, String & v1);
		void item_loop_next(pattern_loop * ptr);
		void item_rnd();
		void item_next();

		void  	list_statu(boolean & ret);
		void  	list_statu_set(boolean ret);
		void  	list_print();
		void  	list_pos(int pos);
		void  	list_lbl(String pos);
		void	list_initialize();
		boolean	list_fromSpiff();
		boolean	list_toSpiff();

	private:
		void item_toTxt();


	};	

	playlist_management * playlist_instance();

	void playlist_statu(boolean & ret);
	void playlist_play();
	void playlist_stop();



	class playlist_item
	{


	public:
		String 	_filename;
		int 	_pos;
		String 	_pattern_name;
		String 	_pattern_config;

		playlist_item();
		~playlist_item(){delete this;};
		void print(int cnt);
		
	};	



	class playlist_list
	{
	public:
		// playlist_patternItem ** _item = nullptr;
		// String json[EFFECTS_MAX];
		String _name;
		String _lbl;
		String _pos;

		playlist_list();
		~playlist_list(){delete this;};

		void setup();
		void print(int cnt);
		void printItems();
	};

	void playlist_pattern_print();
#endif