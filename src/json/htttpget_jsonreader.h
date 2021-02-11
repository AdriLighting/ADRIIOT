
#ifndef HTTTPGET_JSONREADER_H
	#define HTTTPGET_JSONREADER_H

	#include <JsonStreamingParser.h>
	#include <Arduino.h>


enum API_MOD { 
	API_MOD_COVID19, 
	API_MOD_WEATHERBIT,
	API_MOD_OPENWATHERMAP,
	API_MOD_RASPBERRYADRI
}; 
extern API_MOD apiMod;

struct httpGetJsonReaderList {
    const char * key;
    const char * desc;
    // boolean	enable;
    // String	data;
} ;


class httpGetJsonReaderCurrent: public JsonListener {
	private:
		String currentKey;
		String currentParent;
		uint8_t weatherItemCounter = 0;
		
		void doUpdate(String url);
		String buildUrl(String url) ;

	public:
		httpGetJsonReaderCurrent();
		void 	updateCurrentById(String url);

		virtual void whitespace(char c);

		virtual void startDocument();

		virtual void key(String key);

		virtual void value(String value);

		virtual void endArray();

		virtual void endObject();

		virtual void endDocument();

		virtual void startArray();

		virtual void startObject();
};
extern PROGMEM httpGetJsonReaderList covid19List_key [] ;
extern PROGMEM httpGetJsonReaderList weatherbitList_key [] ;
extern PROGMEM httpGetJsonReaderList openWeatherMapList_key [] ;
extern uint8_t covid19List_keyCount;
extern uint8_t weatherbitList_keyCount;
extern uint8_t openWeatherMapList_keyCount;
void 	httpGetJsonReader_print(httpGetJsonReaderList * list, int count, String header, int space, String apiName) ;
String 	httpGetJsonReader_getKey(httpGetJsonReaderList * list, const char * value, int count, String apiName) ;
#endif
