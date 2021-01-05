#include "playlist_pattern.h"

#include <adri_tools.h>
#include <adri_spiff.h>


playlist_pattern::playlist_pattern(){}

void playlist_pattern::setup(){

}

123456


int 	compositions_current_count 	= 0;
int 	compositions_current_pos 	= 0;
bool 	compositions_debug 			= false; 
bool 	compositions_statu 			= false; 
String 	compositions_compoName 		="compoName_0";
int 	compositions_compoName_pos 	= 0;

compositions::compositions() {}
compositions compositions_txt[COMPOSTIONS_MAX];


String string_split(String A_readString) {


	String  ret = "";
	String  s_command;
	String  s_readString = A_readString;
	char    inputChar[s_readString.length() + 1] ;
			s_readString.toCharArray(inputChar, s_readString.length() + 1);
	char    * Rcommand  = strtok(inputChar, "_");

	while (Rcommand != 0){          
			s_command = String(Rcommand);
			if (s_command != "compoName") ret = s_command;
			Rcommand = strtok(0, "_"); 
	}
	return ret;
} 




bool compositions_setup() {
	String 	filename 	= "/compoName.txt"; 
	File 	f 			= SPIFFS.open(filename,"r");
	if (!f){ 
		f = SPIFFS.open(filename,"w");
		if (f){
			#ifdef DEBUG
				if (compositions_debug) fsprintf("\n[compositionSetup] Start\n");
			#endif
			String line;
			for (int i=0; i < COMPOSTIONS_MAX; i++) {
				String cName 	= literal_item("name", "compoName_" + String(i));
				String clbl 	= literal_item("lbl", 	"compoName_" + String(i));
				String cPos 	= literal_item("pos", 	String(i));
				line += cName ;
				line += cPos ;
				line += clbl + "\n";
			} 
			f.print(line);
			f.close();
			#ifdef DEBUG
				if (compositions_debug) fsprintf("[composition setup] Done\n");
			#endif
		}
	}    
}
int compositions_check(String FILE_NAME) {
		
	int count = 0;

	File f=SPIFFS.open(FILE_NAME,"r");
	if (!f) {
		return count;
	}

	String xml;
	while (f.position()<f.size()) {
		xml = f.readStringUntil('\n');
		if (literal_value("filename", xml) != "") {
			if (count >= COMPOSTIONS_MAX) {
				break;
			} else {
				count++;
			}   
		}   
	}
	f.close();
	return count;
}
String compositions_listName() {
	String 	filename 	= "/compoName.txt";        
	File 	f 			= SPIFFS.open(filename, "r");
	String 	line 		= "";
	String 	ret 		= "";
	int 	count 		= 0;
	if (f) {
		 while (f.available()) {
				line = f.readStringUntil('\n');
				if (line != "" ) ret += literal_value("lbl", line) + ";"  ;
		 }
		 f.close();
	} else return "";
	return ret;
} 
boolean compositions_listGetCnt(int & count) {
	String filename = "/compoName.txt";        
	File 	f 		= SPIFFS.open(filename, "r");
	String 	line 	= "";
	 		count 	= 0;
	if (f) {
		 while (f.available()) {
				line = f.readStringUntil('\n');
				if (line != "" ) {
 					count++;
				}
		 }
		 f.close();

	} else return false;
	return true;
} 
void compositions_listNamePrint() {
	String filename = "/compoName.txt";        
	File 	f 		= SPIFFS.open(filename, "r");
	String 	line 	= "";
	String 	ret 	= "";
	int 	count 	= 0;
	char 	buf[200];
	String 	pRet 	= "";

	compositions_listGetCnt(count);

	fsprintf("\n[compositions_listNamePrint print] Printing %d compositions in memory\n", count);

	if (f) {
		 while (f.available()) {
				line = f.readStringUntil('\n');
				if (line != "" ) {

					String 	name 	= literal_value("name", line);
					int 	statu 	= compositions_check("/" + name + ".txt");
					sprintf(buf, "#%-3d\tpos: %-5s name: %-15s lbl: %-15s statu: %d", 
						count,
						literal_value("pos", 	line).c_str(), 
						literal_value("name", 	line).c_str(), 
						literal_value("lbl", 	line).c_str(),
						statu
					);
					fsprintf("%s\n", buf);

					if (statu>0) {
						String pat;
						readFile(SPIFFS, "/" + name + ".txt" , &pat);
						pRet = "/" + name + ".txt=" + pat + "\n";
						fsprintf("%10s\n", pRet.c_str());
					}
 					count++;
				}
		 }
		 f.close();


	};
} 
String compositions_getCompoName(String search) {
	String 	filename 	= "/compoName.txt";        
	File 	f 			= SPIFFS.open(filename, "r");
	String 	line 		= "";
	String 	ret 		= "";
	int 	count 		= 0;
	if (f) {
		 while (f.available()) {
				line = f.readStringUntil('\n');
				if (line != "" ) {
					 if (literal_value("lbl", line) == search) {
							ret = literal_value("name", line) ;
							break;
					 }
				}
		 }
		 f.close();
	} else return "";
	return ret;
} 
String compositions_getCompoNameByFileName(String search) {
	String 	filename 	= "/compoName.txt";        
	File 	f 			= SPIFFS.open(filename, "r");
	String 	line 		= "";
	String 	ret 		= "";
	if (f) {
		 while (f.available()) {
				line = f.readStringUntil('\n');
				if (line != "" ) {
					 if (literal_value("name", line) == search) {
							ret = literal_value("lbl", line) ;
							break;
					 }
				}
		 }
		 f.close();
	} else return "";
	return ret;
} 
String compoName_getCurrentName(String search) {
	String 	filename 	= "/compoName.txt";        
	File 	f 			= SPIFFS.open(filename, "r");
	String 	line 		= "";
	String 	ret 		= "";
	if (f) {
		while (f.available()) {
			line = f.readStringUntil('\n');
			if (line != "" ) {
				if (literal_value("name", line) == search) {
					ret = literal_value("lbl", line) ;
					break;
				}
			}
		}
		f.close();
	} else return "";
	return ret;
} 
void compoName_createarray(String path, String * array) {
	File file = SPIFFS.open(path, "r");
	if (!file) {
		if (compositions_debug) {
			fsprint("[compositions compoName_createarray] Error writing "); 
			Serial.println(path);
		}
		return;
	}
	#ifdef DEBUG
		if (compositions_debug) fsprintf("[compositions compoName_createarray] File read succes : %s\n", path.c_str());
	#endif
	int i = 0;
	while (file.position()<file.size()) {
		String xml = file.readStringUntil('\n');
		if (xml != "") {
			array[i] = xml;
			i++;
		}
	}
	file.close();
}
void compoName_edit(String path, String pos, String vName, String vLbl, String vPos) {
	String array[30];
	compoName_createarray(path, array);
	File f = SPIFFS.open(path,"w");
	if (f){
		#ifdef DEBUG
			if (compositions_debug) fsprintf("\n[compositions compoName_edit] Start\n");
		#endif
		String line;
		String cName;
		String clbl;
		String cPos;
		for (int i=0; i < COMPOSTIONS_MAX; i++) {
			cName   = literal_value("name", array[i]);
			clbl    = literal_value("lbl",  array[i]);
			cPos    = literal_value("pos",  array[i]);            
			if (pos == cName) {
				if (vName   != "") cName = vName;
				if (vLbl    != "") clbl  = vLbl;
				if (vPos    != "") cPos  = vPos;
			} 
			line += literal_item("name",  cName);
			line += literal_item("lbl",   clbl);
			line += literal_item("pos",   cPos);
			f.println(line);
			line = "";
		} 
		f.close();
		#ifdef DEBUG
			if (compositions_debug) fsprintf("[compositions compoName_edit] Done\n");
		#endif
	}
}

String compositions::dump(String header) {
	String s;
	char buf[200];
	sprintf(buf," filename:%s position:%d pattern_name:%s",
		name.c_str(),
		prog_pos,
		pattern_name.c_str()
		// pattern_config.c_str()
	);  
	return header+String(buf);
}
void compositions_print() {
	// #ifdef DEBUG
		fsprintf("\n[composition print]\n%s - Printing %d compositions in memory\n", compositions_compoName.c_str(), compositions_current_count);
	// #endif

	if (compositions_current_count <= 0) return;

	for (int i=0; i<compositions_current_count; i++) {
		 Serial.println(compositions_txt[i].dump("#"+String(i)+" "));
	}
	// #ifdef DEBUG
		fsprintfs("[composition print] Done\n");
	// #endif

}
String compositions_list() {

	if (compositions_current_count <= 0) return "";
	String ret;
	for (int i=0; i<compositions_current_count; i++) {
		ret += compositions_txt[i].pattern_name + ";" + String(compositions_txt[i].prog_pos) + "\n" ;
	}
	return ret;
}
String compositions_listPattern() {

	if (compositions_current_count <= 0) return "";
	String ret;
	for (int i=0; i<compositions_current_count; i++) {
		ret += compositions_txt[i].pattern_name + ";"  ;
	}
	return ret;
}  
					 
int compositions_getCompoByName(String search) {
	if (search == "") return -1;
	int ret = -1;
	for (int i=0; i<compositions_current_count; i++) {
		if (search == compositions_txt[i].pattern_name){ ret = i; break;}
	}
	#ifdef DEBUG
		if (compositions_debug) {
			 fsprintfs("\n[compositions getCompoByName] search: %s ret: %d\n",search.c_str(), ret); 
		} 
	#endif
	return ret;
}