#include "playlist_pattern.h"


#include <ArduinoJson.h>
#include <LittleFS.h>


String playlist_management_folder = "/playlist/";

bool compositions_debug = false; 

playlist_item 		playlist_itemArray[EFFECTS_MAX];
playlist_list		* playlist_listArray[COMPOSTIONS_MAX];
playlist_management * playlist_manage;

namespace  {
	String literal_value(String name, String xml){
	   String open,close;
	   String value = "";
	   int start, end;
	   open="<"+name+">";
	   close="</"+name+">";
	   start=xml.indexOf(open);
	   if (start!=-1) {
	      start+=name.length()+2;
	      end=xml.indexOf(close);
	      value=xml.substring(start,end);
	   }
	   return value;
	}
	String literal_item(String name, String value) {
	   String x="<"+name+">"+value+"</"+name+">";
	   return x;
	}
} // name

playlist_management * playlist_instance(){
	return playlist_manage;
}
playlist_management::playlist_management(){
	playlist_manage = this;
	_item_loop_timer = new adri_timer(0,"",true);
	list_fromSpiff() ;
	item_restore();
	// list_print();
	// item_print();
	
}

void playlist_management::print(){
	arp_fsprintf("\n[playlist_management::print]\n\tname: %s\n\tpos: %d\n\titemMax: %d\n\titemPos: %d\n\titemStatu: %d\n", 
		_list_name.c_str(),
		_list_pos,
		_item_max,
		_item_pos,
		_list_statu
	);	
}

void playlist_management::jsonKey_object(JsonObject & object){
        object[F("item_max")] 		= "0";
        object[F("item_pos")] 		= "1";
        object[F("list_statu")] 	= "2";
        object[F("list_name")] 		= "3";
        object[F("list_pos")] 		= "4";
}
void playlist_management::json_object(JsonObject & object){
        object[F("0")] = String(_item_max);
        object[F("1")] = String(_item_pos);
        object[F("2")] = String(_list_statu);
        object[F("3")] = _list_name;
        object[F("4")] = String(_list_pos);
}
void playlist_management::json_objectName(JsonObject & object){
        object[F("item_max")] 		= String(_item_max);
        object[F("item_pos")] 		= String(_item_pos);
        object[F("list_statu")] 	= String(_list_statu);
        object[F("list_name")] 		= _list_name;
        object[F("list_pos")] 		= String(_list_pos);
}

void playlist_management::item_jsonObject(JsonObject & object){
	// arp_fsprintf("\n[playlist_management::item_jsonObject]\n");
	for (int i = 0; i < _item_max; ++i)
	{
		// playlist_itemArray[i].print(i);
        object[String(i)] = playlist_itemArray[i]._pattern_name;

	}
}
void playlist_management::item_print(){
	arp_fsprintf("\n[playlist_management::item_print]\n");
	for (int i = 0; i < _item_max; ++i)
	{
		playlist_itemArray[i].print(i);
			delay(100);

	}

}
void playlist_management::item_toTxt() {
	String xml;
	File f=LittleFS.open(playlist_management_folder + _list_name + ".txt","w");
	// if (compositions_debug) arp_fsprintfs("save_to_txt: %s\n", playlist_management_folder + _name + ".txt".c_str());
	if (!f) {Serial.print(F("Error writing ")); Serial.println(playlist_management_folder + _list_name + ".txt"); return;}
	for (int i=0; i < _item_max; i++) {
		xml="";
		xml+=literal_item("filename",          String(playlist_itemArray[i]._filename));
		xml+=literal_item("position",          String(playlist_itemArray[i]._pos));
		xml+=literal_item("pattern_name",      String(playlist_itemArray[i]._pattern_name));
		xml+=literal_item("pattern_config",    String(playlist_itemArray[i]._pattern_config));
		f.println(xml);
	}
	f.close();
}
void playlist_management::item_toArray(int s_pos, String s_patterName, String s_pattern_config) {
	bool newSav = false;
	if (s_pos > _item_max) {
		if ((_item_max) >= COMPOSTIONS_MAX) {
			#ifdef DEBUG
				if (compositions_debug) {arp_fsprintf("\n[playlist_management::item_toArray] LIMITE MAXIMUM ATTEINTE\n");}
			#endif
			return;
		}  	
		if (_item_max < 0) _item_max = 0;
		#ifdef DEBUG
			if (compositions_debug)  arp_fsprintf("[playlist_management::item_toArray]newSav\n");
		#endif
		s_pos = _item_max;
		_item_max++;
		newSav=true;
		#ifdef DEBUG
			if (compositions_debug) arp_fsprintf("\tnewSav\n");
		#endif
	}

	String val = "compo_" +  String(s_pos);

	int newNbr = s_pos;
	if (newSav){
		 bool find = true;
		 while (find) {
				for (int i=0; i < _item_max; i++) {
					 if (playlist_itemArray[i]._pos == newNbr) {
							newNbr = random(0,255);
							#ifdef DEBUG
								if (compositions_debug)  arp_fsprintfs("\tnew position: %d\n", newNbr);
							#endif
					 }  
					 else find = false;
				}
		 }
	}

	if (newSav) playlist_itemArray[s_pos]._filename 		= val;
	if (newSav) playlist_itemArray[s_pos]._pos 				= newNbr;
	if (newSav) playlist_itemArray[s_pos]._pattern_name 	= s_patterName;
				playlist_itemArray[s_pos]._pattern_config 	= s_pattern_config;
	#ifdef DEBUG
	if (compositions_debug) {
		 // arp_fsprintfs("\tname:%s position:%d pattern_name:%s _item_max:%d p: %s",
			// 	val.c_str(),
			// 	playlist_itemArray[s_pos].prog_pos,
			// 	pattern.getName().c_str(),
			// 	_item_max,
			// 	s_pattern_config.c_str()
		 // ); 
		 // arp_fsprintfs("\nsav: %s\n----\n",
		 //    playlist_itemArray[s_pos].name.c_str()
		 // ); 
	}

	if (compositions_debug) compositions_print();
	#endif
	
	item_toTxt(); 

	#ifdef DEBUG
		if (compositions_debug) arp_fsprintf("[composition sav_to_array] Done\n");
	#endif
}
boolean playlist_management::item_restore() {
	#ifdef DEBUG
		if (compositions_debug) arp_fsprintf("\n[compositions restore]\n");   
	#endif
	_item_pos = 0;	
	_item_max = 0;
	for (int i=0; i< COMPOSTIONS_MAX; i++) {
		playlist_itemArray[i]._filename 		= "";
		playlist_itemArray[i]._pattern_config 	= "";
	}

	File f=LittleFS.open(playlist_management_folder + _list_name + ".txt","r");
	if (!f) {
		#ifdef DEBUG
			if (compositions_debug) {
				Serial.print(F("[compositions restore] Error reading ")); 
				Serial.println(playlist_management_folder + _list_name + ".txt"); 				
			}
		#endif	
		return false;
	}


	String xml;
	while (f.position()<f.size()) {
		xml = f.readStringUntil('\n');
		if (literal_value("filename", xml) != "") {
			if (_item_max >= COMPOSTIONS_MAX) {
				#ifdef DEBUG
					if (compositions_debug) {arp_fsprintf("\tLIMITE MAXIMUM ATTEINTE\n");}
				#endif
				break;
			} else {
				playlist_itemArray[_item_max]._filename 		= literal_value("filename",xml);
				playlist_itemArray[_item_max]._pos           	= literal_value("position",xml).toInt();
				playlist_itemArray[_item_max]._pattern_name 	= literal_value("pattern_name",xml);
				playlist_itemArray[_item_max]._pattern_config 	= literal_value("pattern_config",xml);          
				_item_max++;
			}   
		}   
	}
	f.close();
	#ifdef DEBUG
		if (compositions_debug) arp_fsprintf("[compositions restore]\n");  
	#endif
	// if (compositions_debug) compositions_print();
	return true;
}
void playlist_management::item_remove(int remove) {
	String xml;
	File f=LittleFS.open(playlist_management_folder + _list_name + ".txt","w");
	if (!f) {Serial.print(F("\n[compositions remove_to_txt] Error writing ")); Serial.println(playlist_management_folder + _list_name + ".txt"); return;}
	int count =0;
	#ifdef DEBUG
		if (compositions_debug) arp_fsprintf("[compositions remove_to_txt]\n");
	#endif
	for (int i=0; i < COMPOSTIONS_MAX; i++) {
		if ((playlist_itemArray[i]._filename != "") && (playlist_itemArray[i]._filename != playlist_itemArray[remove]._filename )) {
			xml="";
			if (count == _item_max - 1) break;
			if (compositions_debug) {
			}        
			String val = "compo_" +  String(count);
			xml+=literal_item("filename",          String(val));
			xml+=literal_item("position",          String(playlist_itemArray[i]._pos));
			xml+=literal_item("pattern_name",      String(playlist_itemArray[i]._pattern_name));
			xml+=literal_item("pattern_config",    String(playlist_itemArray[i]._pattern_config));
			count++;
			f.println(xml);
		} 
	}
	f.close();
	#ifdef DEBUG
		if (compositions_debug) arp_fsprintf("[composition remove_to_txt] Done\n");
	#endif

	item_restore();
}
void playlist_management::item_patternName(String & ret) 	{ret 		= playlist_itemArray[_item_pos]._pattern_name;}
void playlist_management::item_patternConfig(String & ret) 	{ret 		= playlist_itemArray[_item_pos]._pattern_config;}
void playlist_management::item_pos(int & ret) 				{ret 		= _item_pos;}
void playlist_management::item_pos_set(int ret) 			{_item_pos 	= ret;}
void playlist_management::item_max(int & ret) 				{ret 		= _item_max;}
void playlist_management::item_loop(pattern_loop * ptr, mod_pattern_loop & mod, String & v1){
	String name;


	if ( !ptr->isPlaying() ) {
		return;
	} 
	uint32_t delay;
	ptr->delayCurrent_get(delay);
	if (_item_loop_timer->loop(delay)) {

		// #ifdef PATHEAPSTATS
		// 	heap_pass++;

		// 	heap_lastPos = _pos;
		// #endif

		item_next();

		// #ifdef PATHEAPSTATS
		// 	heap_newPos = _pos;
		// #endif

		item_patternName(name);

		// // arp_fsprintf("\n[pattern_loop::loop] : next item set to : [%d] - %s\n", _pos, name.c_str());


		mod		= mpl_next;
		v1 		= name;		
	}
}
void playlist_management::item_loop_next(pattern_loop * ptr){
	if (ptr->isRndPlaying()) 	item_rnd();
	else 						item_next();
}
void playlist_management::item_next(){
	_item_pos++;
	if (_item_pos > _item_max) _item_pos = 0;
}
void playlist_management::item_rnd(){
	_item_pos = random(0, _item_max);
	if (_item_pos > _item_max) _item_pos = 0;
}
void playlist_statu(boolean & ret)		{playlist_instance()->list_statu(ret);}
void playlist_play() 					{playlist_instance()->list_statu_set(true);}
void playlist_stop() 					{playlist_instance()->list_statu_set(false);}

void playlist_management::list_statu_set(boolean ret) 	{playlist_instance()->_list_statu = ret;}
void playlist_management::list_statu(boolean & ret) 	{ret = playlist_instance()->_list_statu;}

void playlist_management::list_print(){
	arp_fsprintf("\n[playlist_management::list_print]\n");
	for (int i = 0; i < COMPOSTIONS_MAX; ++i) playlist_listArray[i]->print(i);
}
void playlist_management::list_pos(int pos){
	_list_pos 	= pos;
	_list_name 	= playlist_listArray[pos]->_name;
}
void playlist_management::list_lbl(String lbl){
 	playlist_listArray[_list_pos]->_lbl = lbl;
}
void playlist_management::list_initialize() {
	File f = LittleFS.open(COMPOSTIONS_FILENAME,"r");
	if (!f){ 
		f = LittleFS.open(COMPOSTIONS_FILENAME,"w");
		if (f){
			#ifdef DEBUG
				if (compositions_debug) arp_fsprintf("\n[compositionSetup] Start\n");
			#endif
			String line;
			for (int i=0; i < COMPOSTIONS_MAX; i++) {
				String cName 	= literal_item("name", 	"compoName_" + String(i));
				String clbl 	= literal_item("lbl", 	"compoName_" + String(i));
				String cPos 	= literal_item("pos", 	String(i));
				line += cName ;
				line += cPos ;
				line += clbl + "\n";
			} 
			f.print(line);
			f.close();
			#ifdef DEBUG
				if (compositions_debug) arp_fsprintf("[composition setup] Done\n");
			#endif
		}
	}    
}

boolean playlist_management::list_fromSpiff(){
	list_initialize();

	File f=LittleFS.open(COMPOSTIONS_FILENAME,"r");
	if (!f) {
		// #ifdef DEBUG
			// if (compositions_debug) {
				Serial.print(F("[playlist_management::list_fromSpiff] Error reading ")); 
				Serial.println(COMPOSTIONS_FILENAME); 				
			// }
		// #endif	
		return false;
	}

	int i = 0;
	String xml;
	while (f.position()<f.size()) {
		xml = f.readStringUntil('\n');

			if (i >= COMPOSTIONS_MAX) {
				#ifdef DEBUG
					if (compositions_debug) {arp_fsprintf("\tLIMITE MAXIMUM ATTEINTE\n");}
				#endif
				break;
			} else {
				playlist_listArray[i] 		= new playlist_list();
				// playlist_listArray[i]->_item 	= new playlist_patternItem*[EFFECTS_MAX];
				// playlist_patternItem_initialize(playlist_listArray[i]->_item);
				playlist_listArray[i]->_name 	= literal_value("name", xml);
				playlist_listArray[i]->_lbl 	= literal_value("lbl", 	xml);
				playlist_listArray[i]->_pos 	= literal_value("pos", 	xml);
				i++;
			}   
	}
	f.close();	
	return true;
}

boolean playlist_management::list_toSpiff(){ 
	File f = LittleFS.open(COMPOSTIONS_FILENAME,"w");

	if (!f) return false; 	

	String line;
	for (int i = 0; i < COMPOSTIONS_MAX; ++i){
		line += literal_item("name", 	playlist_listArray[i]->_name) 			;
		line += literal_item("lbl", 	playlist_listArray[i]->_lbl) 			;
		line += literal_item("pos", 	playlist_listArray[i]->_pos) 	+ "\n"	;
	}

	f.print(line);
	f.close();	

	return true;

}




playlist_item::playlist_item(){
}

void playlist_item::print(int cnt){
	Serial.printf("\t[%3d] [pos: %5d] [name: %-15s] [pattern: %-15s] [param: %-15s]\n", 
		cnt,
		_pos,
		_filename.c_str(),
		_pattern_name.c_str(),
		_pattern_config.c_str()
	);
}
// void playlist_patternItem_initialize(playlist_patternItem ** array){
// 	for (int i = 0; i < EFFECTS_MAX; ++i) array[i] = new playlist_patternItem();
// }
// 






playlist_list::playlist_list(){}

void playlist_list::setup(){

}
void playlist_list::print(int cnt){
	arp_fsprintf("[%3d] [pos: %5s] [name: %-15s] [lbl: %-15s]\n", 
		cnt,
		_pos.c_str(),
		_name.c_str(),
		_lbl.c_str()
	);
}
void playlist_list::printItems(){
	// for (int i = 0; i < EFFECTS_MAX; ++i) _item[i]->print(i);
}




