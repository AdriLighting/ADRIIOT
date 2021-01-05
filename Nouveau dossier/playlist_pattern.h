#ifndef PLAYLIST_PATTERN_H
	#define PLAYLIST_PATTERN_H 

	#define COMPOSTIONS_MAX 15

	#include <Arduino.h>

	class playlist_pattern
	{

	public:
		playlist_pattern();
		~playlist_pattern(){delete this;};

		void setup();
		
	};


		class compositions {
			public:
				// int compositions_size = 0;
				String pattern_name;
				String name;
				int prog_pos;
				String pattern_config;

				compositions();
				String dump(String header);

				// void compoName_toArray(String path, String * array, int mod);
				// void compoName_createarray(String path, String * array);
				// void compoName_edit(String filename, String pos, String vName, String vLbl, String vPos);
		};
		

		extern compositions compositions_txt[];

		bool 	compositions_setup();
		void 	compositions_pattern_next();
		void 	compositions_pattern_previous();
		void 	compositions_pattern_random();
		void 	compositions_pattern_set_postion();
		int 	compositions_getCompoByName(String search);
		String 	compositions_getCompoName(String search);
		String  compositions_getCompoNameByFileName(String search);
		String  compositions_list();
		String 	compositions_listPattern();
		String 	compositions_listName();
		void 	compositions_print();
		boolean compositions_restore(String FILE_NAME);   
		void 	compositions_remove_to_txt(String FILE_NAME, int remove);  
		bool 	compositions_isPlaying();   
		void 	compositions_sav_to_array(int s_pos, String s_patterName, String s_pattern_config) ;   

		void 	compoName_edit(String path, String pos, String vName, String vLbl, String vPos);
		String 	compoName_getCurrentName(String search);

		extern int      compositions_current_count;
		extern int      compositions_current_pos;
		extern bool     compositions_debug; 
		extern bool     compositions_statu; 
		extern String   compositions_compoName;

		void 	compositions_autoPaly();
		void 	compositions_autoPaly_2();
		// String compositions_listNamePrint();
		void 	compositions_listNamePrint();
		int 	compositions_check(String FILE_NAME) ;
#endif